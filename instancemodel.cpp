//#include"instancemodel.h"
//#include"shaderhashmap.h"
//#include"CCamera.h"
//#include"Shader.h"
//#include<vector>
//using namespace DirectX;
//
//
//std::vector<Vertex> inst(PlayerMgr::GetInstance()->player_vector_num);
//
//
//InstanceModel::~InstanceModel() {}
//
//bool InstanceModel::Init(const char* filename,  std::string texfolder)
//{
//	ID3D11Device* device;
//	device = CDirectXGraphics::GetInstance()->GetDXDevice();
//	ID3D11DeviceContext* devcontext;
//	devcontext = GetDX11DeviceContext();
//	bool sts;
//	std::string fname(filename);
//
//
//
//	sts = m_assimpfile.Load(texfolder, fname);
//	if (!sts) {
//		char str[128];
//		sprintf_s(str, 128, "%s load ERROR!!", filename);
//		MessageBox(nullptr, str, "error", MB_OK);
//		return false;
//	}
//	m_filetype = eASSIMPFILE;
//	// ビューポートの設定
//	D3D11_VIEWPORT vp;
//	vp.Width = 1920;
//	vp.Height = 1080;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
//
//
//	// 頂点レイアウト
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "BONEWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//
//	};
//
//
//	// シェーダの設定
//	ID3DBlob* pCompileVS = NULL;
//	ID3DBlob* pCompilePS = NULL;
//	D3DCompileFromFile(L"shader/instancemodel.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
//	device->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, mVertexShader.GetAddressOf());
//	D3DCompileFromFile(L"shader/instancemodel.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
//	device->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, mPixelShader.GetAddressOf());
//
//
//	unsigned int numElements = ARRAYSIZE(layout);
//
//	device->CreateInputLayout(layout, numElements, pCompileVS->GetBufferPointer(),pCompileVS->GetBufferSize(), mInputLayout.GetAddressOf());
//	pCompileVS->Release();
//	pCompilePS->Release();
//
//
//	std::vector<Vertex> inst(PlayerMgr::GetInstance()->player_vector_num);
//
//
//
//	
//	//ポリゴンの頂点データの作成とそのバッファの設定
//
//
//	VERTEX	vertexes[4] = {
//		// 座標													// カラー	// UV	
//		XMFLOAT3(-0.5f ,0.5 , 0.0f),	XMFLOAT3(1.0f,1.0f,1.0f),	XMFLOAT2(0.0f,0.0f),
//		XMFLOAT3(-0.5 ,	-0.5, 0.0f),	XMFLOAT3(1.0f,1.0f,1.0f),	XMFLOAT2(1.0f,0.0f),
//		XMFLOAT3(0.5 ,0.5 , 0.0f),	XMFLOAT3(1.0f,1.0f,1.0f),		XMFLOAT2(0.0f,1.0f),
//		XMFLOAT3(0.5 ,-0.5 , 0.0f),	XMFLOAT3(1.0f,1.0f,1.0f),		XMFLOAT2(1.0f,1.0f),
//	};
//	mDrawNum = sizeof(vertexes) / sizeof(vertexes[0]);
//
//	D3D11_BUFFER_DESC bd;
//	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//	bd.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA vertexData;
//	vertexData.pSysMem = vertexes;
//	device->CreateBuffer(&bd, &vertexData, mVertexBuffer.GetAddressOf());
//
//	// インデックスデータ用バッファの設定
//	//ポリゴンの頂点データの作成とそのバッファの設定
//
//	int indexes[] =
//	{
//		0,2,1,
//		0,3,2,
//	};
//	mDrawNum = sizeof(inst) / sizeof(inst[0]);
//
//	D3D11_BUFFER_DESC bd_index;
//	bd_index.ByteWidth = sizeof(int) * mDrawNum;
//	bd_index.Usage = D3D11_USAGE_DEFAULT;
//	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	bd_index.CPUAccessFlags = 0;
//	bd_index.MiscFlags = 0;
//	bd_index.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA indexData;
//	indexData.pSysMem = indexes;
//	device->CreateBuffer(&bd_index, &indexData, mIndexBuffer.GetAddressOf());
//
//	CreateStructuredBuffer(device, sizeof(VERTEX), PlayerMgr::GetInstance()->player_vector_num, &inst[0], mPerInstanceBuffer.GetAddressOf());
//
//
//	//パイプラインの構築
//	ID3D11Buffer* bufs[] = { mVertexBuffer.Get() };
//	UINT stride[] = { sizeof(VERTEX) };
//	UINT offset[] = { 0 };
//	devcontext->IASetVertexBuffers(0, sizeof(bufs) / sizeof(bufs[0]), bufs, stride, offset);
//	devcontext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
//	devcontext->IASetInputLayout(mInputLayout.Get());
//	devcontext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), NULL);
//	devcontext->RSSetViewports(1, &vp);
//
//	auto camera = CCamera::GetInstance()->GetCameraMatrix();
//	mView = DirectX::XMLoadFloat4x4(&camera);
//	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
//	mProj = DirectX::XMLoadFloat4x4(&proj);
//	mScale = XMMatrixScalingFromVector(XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f));
//	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(90.0f);
//
//}
//
//void InstanceModel::Draw2(DirectX::XMFLOAT4X4& mtxworld)
//{
//	// デバイスコンテキストを取得
//	ID3D11DeviceContext* devcontext;
//	devcontext = GetDX11DeviceContext();
//	// デバイスを取得
//	ID3D11Device* device;
//	device = GetDX11Device();
//
//	for (int i = 0; i < PlayerMgr::GetInstance()->player_vector_num; i++)
//	{
//		temppos = XMVectorSet(PlayerMgr::GetInstance()->player_vector[i].get()->m_mtx._41, PlayerMgr::GetInstance()->player_vector[i].get()->m_mtx._42, PlayerMgr::GetInstance()->player_vector[i].get()->m_mtx._43, 0.0f);
//		XMStoreFloat3(&inst[i].m_Pos, temppos);
//	}
//
//	// 頂点フォーマットをセット
//	devcontext->IASetInputLayout(mInputLayout.Get());
//	// 頂点シェーダーをセット
//	devcontext->VSSetShader(mVertexShader.Get(), nullptr, 0);
//	devcontext->GSSetShader(nullptr, nullptr, 0);
//	devcontext->HSSetShader(nullptr, nullptr, 0);
//	devcontext->DSSetShader(nullptr, nullptr, 0);
//	// ピクセルシェーダーをセット
//	devcontext->PSSetShader(mPixelShader.Get(), nullptr, 0);
//
//	// 描画
//	m_assimpfile.Draw(devcontext, mtxworld);
//}
