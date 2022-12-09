#include	<windows.h>
#include	"CModelInstance.h"
#include	"Shader.h"

#include	"DX11util.h"
#include	"CCamera.h"
#include	"DX11Settransform.h"


bool CModelInstance::InitiInstancing(int num, const char* filename, const char* vsfile, const char* psfile, std::string texfoldername) {

	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// デバイスを取得
	ID3D11Device* device;
	device = GetDX11Device();

	bool sts;
	//// 飛行機のモデルデータを読み込み
	//sts = m_datfile.Load(filename, GetDX11Device(), GetDX11DeviceContext());
	//if (!sts) {
	//	char str[128];
	//	sprintf_s(str, 128, "%s load ERROR!!", filename);
	//	MessageBox(nullptr, str, "error", MB_OK);
	//	return false;
	//}

	std::string fname(filename);

	sts = m_assimpfile.Load(texfoldername, fname);
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}
	CreateSRVfromFile(texfoldername.c_str(),
		GetDX11Device(),
		GetDX11DeviceContext(),
		&m_tex, &m_srv);

	//全メッシュ頂点数、情報取得
	GetVertex();


	auto vdata = ver.begin()._Ptr;
	auto idata = ind.begin()._Ptr;

	// 頂点バッファ作成
	sts = CreateVertexBuffer(
		device,
		sizeof(Vertex),				// １頂点当たりバイト数
		ver.size(),			// 頂点数
		vdata,				// 頂点データ格納メモリ先頭アドレス
		&m_pVertexBuffer);				// 頂点バッファ
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}

	// インデックスバッファ作成
	sts = CreateIndexBuffer(
		device,
		ind.size(),				// 頂点数
		idata,				// 頂点データ格納メモリ先頭アドレス
		&m_pIndexBuffer);				// インデックスバッファ
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return false;
	}

	//// コンスタントバッファ作成
	//sts = CreateConstantBuffer(
	//	device,
	//	sizeof(X::ConstantBufferMaterial),
	//	&m_cb3);
	//if (!sts) {
	//	MessageBox(NULL, "CreateBuffer(constant buffer Material) error", "Error", MB_OK);
	//	return false;
	//}


	m_filetype = eASSIMPFILE;
	


	// インスタンシング数セット
	m_instancecount = num;

	m_initdata = _mm_malloc(sizeof(XMMATRIX) * num, 16);
	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	// インスタンスバッファの初期行列をセット
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMMatrixTranslation(0, 0, 0));
		pstart++;
	}
	//インスタンス用バッファ
	sts = CreateVertexBufferWrite(
		GetDX11Device(),		// device11
		sizeof(XMMATRIX),		// １頂点当たりバイト数
		num,					// 頂点数
		m_initdata,				// 初期化データ
		&m_pInstanceBuffer);	// 頂点バッファ
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBufferWrite(InstanceBuffer) error", "error", MB_OK);
		return false;
	}


	////インスタンスデータ用バッファの設定
	//D3D11_BUFFER_DESC bd_instance;
	//bd_instance.Usage = D3D11_USAGE_DYNAMIC;
	//bd_instance.ByteWidth = sizeof(PerInstanceData) * num;
	//bd_instance.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//bd_instance.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//bd_instance.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	//bd_instance.StructureByteStride = sizeof(PerInstanceData);
	//device->CreateBuffer(&bd_instance, NULL, mPerInstanceBuffer.GetAddressOf());

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// semantic name    index		format							slot	alignedbyteoffset				inputslotclass				instancedatasteprate
		{ "POSITION",		0,		DXGI_FORMAT_R32G32B32_FLOAT,		0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL",			0,		DXGI_FORMAT_R32G32B32_FLOAT,	    0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",		0,		DXGI_FORMAT_R32G32_FLOAT,			0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "LocalToWorld",	0,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		0,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	1,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		16,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	2,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		32,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	3,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		48,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	sts = CreateVertexinShader(device,
		vsfile,
		"main",
		"vs_5_0",
		layout,
		numElements,
		&m_pVertexShader,
		&m_pVertexLayout);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	// ピクセルシェーダーを生成
	sts = CreatePixelShader(			// ピクセルシェーダーオブジェクトを生成
		GetDX11Device(),		// デバイスオブジェクト
		psfile,
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}



	// 定数バッファの作成(パラメータ受け渡し用)
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	device->CreateBuffer(&cb, NULL, mConstantBuffer.GetAddressOf());

	//パイプラインの構築
	ID3D11Buffer* bufs[] = { m_pVertexBuffer};
	UINT stride[] = { sizeof(Vertex) };
	UINT offset[] = { 0 };
	devcontext->IASetVertexBuffers(0, sizeof(bufs) / sizeof(bufs[0]), bufs, stride, offset);
	devcontext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devcontext->IASetInputLayout(m_pVertexLayout);

	auto camera = CCamera::GetInstance()->GetCameraMatrix();

	mView = DirectX::XMLoadFloat4x4(&camera);

	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
	mProj = DirectX::XMLoadFloat4x4(&proj);
	mScale = XMMatrixScalingFromVector(XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f));
	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(90.0f);

	return true;
}

bool CModelInstance::TestInstancing(int instancecnt, const char* filename, const char* vsfile, const char* psfile, std::string texfoldername)
{
	bool sts;

	// 飛行機のモデルデータを読み込み
	sts = m_datfile.Load(filename, GetDX11Device(), GetDX11DeviceContext());
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}

	// インスタンシング数セット
	m_instancecount = instancecnt;

	m_initdata = _mm_malloc(sizeof(XMMATRIX) * instancecnt, 16);
	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	// インスタンスバッファの初期行列をセット
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMMatrixTranslation(0, 0, 0));
		pstart++;
	}

	sts = CreateVertexBufferWrite(
		GetDX11Device(),		// device11
		sizeof(XMMATRIX),		// １頂点当たりバイト数
		instancecnt,					// 頂点数
		m_initdata,				// 初期化データ
		&m_pInstanceBuffer);	// 頂点バッファ
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBufferWrite(InstanceBuffer) error", "error", MB_OK);
		return false;
	}

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// semantic name    index		format							slot	alignedbyteoffset				inputslotclass				instancedatasteprate
		{ "POSITION",		0,		DXGI_FORMAT_R32G32B32_FLOAT,		0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL",			0,		DXGI_FORMAT_R32G32B32_FLOAT,	    0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",		0,		DXGI_FORMAT_R32G32_FLOAT,			0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "LocalToWorld",	0,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		0,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	1,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		16,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	2,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		32,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	3,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		48,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	sts = CreateVertexShader(GetDX11Device(),
		vsfile,
		"main",
		"vs_5_0",
		layout,
		numElements,
		&m_pVertexShader,
		&m_pVertexLayout);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	// ピクセルシェーダーを生成
	sts = CreatePixelShader(			// ピクセルシェーダーオブジェクトを生成
		GetDX11Device(),		// デバイスオブジェクト
		psfile,
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	return true;
}

bool CModelInstance::Init(const char* filename, const char* vsfile, const char* psfile) {

	bool sts;

	// 飛行機のモデルデータを読み込み
	sts = m_datfile.Load(filename, GetDX11Device(), GetDX11DeviceContext());
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}

	// 飛行機用の頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	sts = CreateVertexShader(GetDX11Device(),
		vsfile,
		"main",
		"vs_5_0",
		layout,
		numElements,
		&m_pVertexShader,
		&m_pVertexLayout);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	// ピクセルシェーダーを生成
	sts = CreatePixelShader(			// ピクセルシェーダーオブジェクトを生成
		GetDX11Device(),		// デバイスオブジェクト
		psfile,
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	return true;
}

void CModelInstance::Uninit() {
	// 頂点シェーダー解放
	if (m_pVertexShader) {
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}

	// ピクセルシェーダー解放
	if (m_pPixelShader) {
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	// 頂点レイアウト解放
	if (m_pVertexLayout) {
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}

	if (m_initdata) {
		// 解放
		_mm_free(m_initdata);
		m_initdata = nullptr;
	}
}

void CModelInstance::Update(XMFLOAT4X4 mat[]) {


	D3D11_MAPPED_SUBRESOURCE pData;

	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	 //インスタンスバッファの初期行列をセット
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMLoadFloat4x4(&mat[i]));
		pstart++;
	}

	HRESULT hr = GetDX11DeviceContext()->Map(m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_initdata), sizeof(XMMATRIX) * m_instancecount);

		GetDX11DeviceContext()->Unmap(m_pInstanceBuffer, 0);
	}
}

void CModelInstance::TestUpdate(XMFLOAT4X4 mat[])
{
	D3D11_MAPPED_SUBRESOURCE pData;

	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	// インスタンスバッファの初期行列をセット
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMLoadFloat4x4(&mat[i]));
		pstart++;
	}

	HRESULT hr = GetDX11DeviceContext()->Map(m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_initdata), sizeof(XMMATRIX) * m_instancecount);

		GetDX11DeviceContext()->Unmap(m_pInstanceBuffer, 0);
	}
}

void CModelInstance::Draw() {


	// 頂点フォーマットをセット
	GetDX11DeviceContext()->IASetInputLayout(m_pVertexLayout);

	// 頂点シェーダーをセット
	GetDX11DeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);

	// ピクセルシェーダーをセット
	GetDX11DeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);

	// モデル描画
	m_datfile.Draw(GetDX11DeviceContext());
}

void CModelInstance::DrawInstance() {
	
	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// デバイスを取得
	ID3D11Device* device;
	device = GetDX11Device();

	// 頂点フォーマットをセット
	GetDX11DeviceContext()->IASetInputLayout(m_pVertexLayout);

	// 頂点シェーダーをセット
	GetDX11DeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
	GetDX11DeviceContext()->GSSetShader(nullptr, nullptr, 0);
	GetDX11DeviceContext()->HSSetShader(nullptr, nullptr, 0);
	GetDX11DeviceContext()->DSSetShader(nullptr, nullptr, 0);
	// ピクセルシェーダーをセット
	GetDX11DeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);


	//// パラメータの受け渡し
	//D3D11_MAPPED_SUBRESOURCE pdata;
	//devcontext->Map(mPerInstanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	//PerInstanceData* instanceData = (PerInstanceData*)(pdata.pData);
	//float defaultYPos = 1.5f;
	//float offset = 1.31f;
	//int oneLineNum = 40;
	////instanceData.tex = { 1.0f, 1.0f };
	//for (int i = 0; i < 100; i++)
	//{
	//	//とりあえずループ変数使って移動
	//	float xPos = i % oneLineNum * offset - 2.0f;
	//	float yPos = defaultYPos - (i / oneLineNum * offset);
	//	XMMATRIX move = XMMatrixTranslation(xPos, yPos, 1.0f);
	//	//行列情報をセット
	//	instanceData[i].matrix = XMMatrixTranspose(mScale * mRotation * move);//*mView* mProj);
	//	//色情報をセット
	//	instanceData[i].color = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);

	//}
	//テクスチャーをピクセルシェーダーに渡す
	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());

	int indexnum = 0;
	int indexstart = 0;

	X::ConstantBufferMaterial		cb;					// コンスタントバッファ３用構造体（マテリアルの値）

														// 入力する頂点バッファとインスタンスバッファ
	ID3D11Buffer* vbuffer[2] = { m_pVertexBuffer ,m_pInstanceBuffer };
	// それぞれのストライドをセット
	unsigned int stride[2] = { sizeof(Vertex),sizeof(XMMATRIX) };
	// オフセットをセット
	unsigned  offset[2] = { 0,0 };

	// 頂点バッファをセット	
	devcontext->IASetVertexBuffers(0, 2, vbuffer, stride, offset);

	// インデックスバッファをセット
	devcontext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// トポロジーをセット（旧プリミティブタイプ）
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcontext->PSSetShaderResources(0, 1, &m_srv);			// debug ts

	//  sprintf_s(str, "m_Subset[0].m_VertexSuu %d mm_Subset[1].m_VertexSuu %d \0", m_xfile->m_Subset[0].m_VertexSuu, m_xfile->m_Subset[1].m_VertexSuu);
	//	MessageBox(nullptr, str, str, MB_OK);

	//sdevcontext->Unmap(mPerInstanceBuffer.Get(), 0);
	devcontext->DrawIndexedInstanced(ind.size(), m_instancecount, 0, 0, 0);
	//m_assimpfile.Drawinstance(devcontext);
	// モデルインスタンシング描画
	//m_datfile.DrawInstance(GetDX11DeviceContext(), m_pInstanceBuffer, m_instancecount);
}

void CModelInstance::TestInstance()
{
	// 頂点フォーマットをセット
	GetDX11DeviceContext()->IASetInputLayout(m_pVertexLayout);

	// 頂点シェーダーをセット
	GetDX11DeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
	GetDX11DeviceContext()->GSSetShader(nullptr, nullptr, 0);
	GetDX11DeviceContext()->HSSetShader(nullptr, nullptr, 0);
	GetDX11DeviceContext()->DSSetShader(nullptr, nullptr, 0);

	// ピクセルシェーダーをセット
	GetDX11DeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);

	// モデルインスタンシング描画
	m_datfile.DrawInstance(GetDX11DeviceContext(), m_pInstanceBuffer, m_instancecount);

}
