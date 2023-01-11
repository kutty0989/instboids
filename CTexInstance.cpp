#include"CTexInstance.h"
#include"shaderhashmap.h"
#include"CCamera.h"
#include<DirectXMath.h>
using namespace DirectX;


// 使用する頂点シェーダー名
const char* vsfilenamein[] = {
	"shader/instancevs.hlsl"
};

// 使用するピクセルシェーダー名
const char* psfilenamein[] = {
	"shader/instanceps.hlsl"
};

CTexInstance::CTexInstance(int num)
{	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// デバイスを取得
	ID3D11Device* device;
	device = GetDX11Device();


	mInstanceNum = num;


	// ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = 1920;
	vp.Height = 1080;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	// シェーダの設定
	ID3DBlob* pCompileVS = NULL;
	ID3DBlob* pCompilePS = NULL;
	D3DCompileFromFile(L"shader/instancevs.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	device->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, mVertexShader.GetAddressOf());
	D3DCompileFromFile(L"shader/instancevs.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	device->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, mPixelShader.GetAddressOf());

	
	// 頂点レイアウト
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};

	device->CreateInputLayout(layout, _countof(layout), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), mInputLayout.GetAddressOf());
	pCompileVS->Release();
	pCompilePS->Release();



	//ポリゴンの頂点データの作成とそのバッファの設定
	

	VERTEX	v[4] = {
		// 座標													// カラー	// UV	
		XMFLOAT3(-1.0f ,-1.0 , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	XMFLOAT2(0.0f,0.0f),
		XMFLOAT3(1.0 ,-1.0f, 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(1.0f,0.0f),
		XMFLOAT3(-1.0 ,1.0 , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(0.0f,1.0f),
		XMFLOAT3(1.0 ,1.0 , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(1.0f,1.0f),
	};


	mDrawNum = sizeof(v) / sizeof(v[0]);

	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = v;
	device->CreateBuffer(&bd, &vertexData, mVertexBuffer.GetAddressOf());

	// インデックスデータ用バッファの設定
	int indexes[] =
	{
		0,1,2,
		1,3,2

	};
	mDrawNum = sizeof(indexes) / sizeof(indexes[0]);
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indexes;
	device->CreateBuffer(&bd_index, &indexData, mIndexBuffer.GetAddressOf());


	//インスタンスデータ用バッファの設定
	D3D11_BUFFER_DESC bd_instance;
	bd_instance.Usage = D3D11_USAGE_DYNAMIC;
	bd_instance.ByteWidth = sizeof(PerInstanceData) * mInstanceNum;
	bd_instance.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bd_instance.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd_instance.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd_instance.StructureByteStride = sizeof(PerInstanceData);
	device->CreateBuffer(&bd_instance, NULL, mPerInstanceBuffer.GetAddressOf());

	//インスタンス用のリソースビューを作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.BufferEx.NumElements = mInstanceNum;
	device->CreateShaderResourceView(mPerInstanceBuffer.Get(), &srvDesc, mShaderResourceView.GetAddressOf());

	// 定数バッファの作成(パラメータ受け渡し用)
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	device->CreateBuffer(&cb, NULL, mConstantBuffer.GetAddressOf());

	
	auto camera = CCamera::GetInstance()->GetCameraMatrix();
	
	mView = DirectX::XMLoadFloat4x4(&camera);

	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
	mProj = DirectX::XMLoadFloat4x4(&proj);
	mScale = XMMatrixScalingFromVector(XMVectorSet(40.1f, 40.1f, 10.1f, 0.0f));
	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(-1.57f);

}

bool CTexInstance::Update(
	DirectX::XMFLOAT3 color,XMFLOAT2 uv[4])
{


	//VERTEX v[4] = {
	//	// 座標													// カラー	// UV	
	//	XMFLOAT3(-1.0f ,	-1.0f , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(1.0f,1.0f),
	//	XMFLOAT3(1.0 ,	-1.0, 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		uv[1],
	//	XMFLOAT3(-m_width ,	 m_height , 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		uv[2],
	//	XMFLOAT3(m_width ,	 m_height, 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		uv[3]
	//};
	//for (int i = 0; i < 4; i++) {
	//	m_vertex[i] = v[i];
	//}

	/*D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetDX11DeviceContext()->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_vertex), sizeof(VERTEX) * 4);
		GetDX11DeviceContext()->Unmap(mVertexBuffer.Get(), 0);
	}
*/


//	ID3D11DeviceContext* devcontext;
//	devcontext = GetDX11DeviceContext();
//
//	// デバイスを取得
//	ID3D11Device* device;
//	device = GetDX11Device();
//
//	// パラメータの受け渡し
//	D3D11_MAPPED_SUBRESOURCE pdata;
//	devcontext->Map(mPerInstanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
//	PerInstanceData* instanceData = (PerInstanceData*)(pdata.pData);
//
//	//instanceData.tex = { 1.0f, 1.0f };
//	for (int i = 0; i < mInstanceNum; i++)
//	{
//		//とりあえずループ変数使って移動
//		float xPos = pos[i]._41;
//		float yPos = pos[i]._43;
//		XMMATRIX move = XMMatrixTranslation(xPos, yPos, 1.0f);
//		//行列情報をセット
//		instanceData[i].matrix = XMMatrixTranspose(mScale * mRotation * move);//*mView* mProj);
//		//色情報をセット
//		instanceData[i].color = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
//
//	}
//	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(instanceData), sizeof(XMMATRIX) * mInstanceNum);
//
//	devcontext->Unmap(mPerInstanceBuffer.Get(), 0);
//
////	mInput->SetPreBuffer();
	return true;
}

void CTexInstance::RenderInstancing(XMFLOAT4X4 pos[])
{

	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// デバイスを取得
	ID3D11Device* device;
	device = GetDX11Device();
	
	//パイプラインの構築
	ID3D11Buffer* bufs[] = { mVertexBuffer.Get() };
	UINT stride[] = { sizeof(VERTEX) };
	UINT offset[] = { 0 };
	devcontext->IASetVertexBuffers(0, sizeof(bufs) / sizeof(bufs[0]), bufs, stride, offset);
	devcontext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	devcontext->IASetInputLayout(mInputLayout.Get());


	//テクスチャーをピクセルシェーダーに渡す
	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());

	devcontext->VSSetShader(mVertexShader.Get(), NULL, 0);
	devcontext->GSSetShader(nullptr, nullptr, 0);
	devcontext->HSSetShader(nullptr, nullptr, 0);
	devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(mPixelShader.Get(), NULL, 0);
	// パラメータの受け渡し
	D3D11_MAPPED_SUBRESOURCE pdata;
	devcontext->Map(mPerInstanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	PerInstanceData* instanceData = (PerInstanceData*)(pdata.pData);
	
	//instanceData.tex = { 1.0f, 1.0f };
	for (int i = 0; i < mInstanceNum; i++)
	{
		//とりあえずループ変数使って移動
		float xPos = pos[i]._41;
		float yPos = pos[i]._43;
		float zPos = pos[i]._42;
		XMMATRIX move;// = XMMatrixTranslation(xPos, zPos, yPos);
		auto cameramat = CCamera::GetInstance()->GetCameraMatrix();
	
		XMFLOAT4X4 m_mtx;
		
		m_mtx._11 = cameramat._11;
		m_mtx._12 = cameramat._21;
		m_mtx._13 = cameramat._31;

		m_mtx._21 = cameramat._12;
		m_mtx._22 = cameramat._22;
		m_mtx._23 = cameramat._32;

		m_mtx._31 = cameramat._13;
		m_mtx._32 = cameramat._23;
		m_mtx._33 = cameramat._33;

		m_mtx._41 = xPos;
		m_mtx._42 = yPos+30.f;
		m_mtx._43 = zPos;

		m_mtx._14 = 0;
		m_mtx._24 = 0;
		m_mtx._34 = 0;
		m_mtx._44 = 1;

		move = XMLoadFloat4x4(&m_mtx);
		
		//行列情報をセット
		instanceData[i].matrix = XMMatrixTranspose(mScale * mRotation * move);//*mView* mProj);
		//色情報をセット
		instanceData[i].color = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
		
	}

	
	devcontext->Unmap(mPerInstanceBuffer.Get(), 0);

	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcontext->VSSetShaderResources(8, 1, mShaderResourceView.GetAddressOf());
	devcontext->PSSetShaderResources(8, 1, mShaderResourceView.GetAddressOf());
	devcontext->VSSetShaderResources(9, 1, m_srv.GetAddressOf());
	devcontext->PSSetShaderResources(9, 1, m_srv.GetAddressOf());
	// 描画実行
	devcontext->DrawIndexedInstanced(mDrawNum, mInstanceNum, 0, 0, 0);
}

CTexInstance::~CTexInstance() {}


