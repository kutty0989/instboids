//#include"instancemodel.h"
//#include"shaderhashmap.h"
//#include"CCamera.h"
//#include"shader.h"
//#include"PlayerMgr.h"
//
//using namespace DirectX;
//
//
//void InstanceModel::Init(const char* filename, std::string texfolder)
//{
//	DXGI_SWAP_CHAIN_DESC scd = { 0 };
//	// デバイスコンテキストを取得
//	ID3D11DeviceContext* devcontext;
//	devcontext = GetDX11DeviceContext();
//	// デバイスを取得
//	ID3D11Device* device;
//	device = GetDX11Device();
//
//	std::string fname(filename);
//
//	m_assimpfile.Load(texfolder, fname);
//	
//	m_filetype = eASSIMPFILE;
//
//	mInstanceNum = 4;
//
//		// ビューポートの設定
//	D3D11_VIEWPORT vp;
//	vp.Width = 1920;
//	vp.Height = 1080;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
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
//	// 頂点レイアウト
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//
//	};
//
//	device->CreateInputLayout(layout, _countof(layout), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), mInputLayout.GetAddressOf());
//	pCompileVS->Release();
//	pCompilePS->Release();
//
//	//ポリゴンの頂点データの作成とそのバッファの設定
//
//	m_assimpfile.GetMeshes().at(0).m_vertices;
//
//	//インスタンス行列バッファの作成
//	//Max値で作成する
//	vector<XMFLOAT4X4> matrices(mInstanceNum);
//	for (auto& m : matrices) {
//		m =XMFLOAT4X4();
//	}
//	D3D11_BUFFER_DESC bufferDesc;
//	bufferDesc.ByteWidth = sizeof(VERTEX) * mDrawNum;
//	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	bufferDesc.CPUAccessFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA dataDesc = { 0 };
//	dataDesc.pSysMem = &matrices.front();
//
//	D3D11_BUFFER_DESC bd;
//	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//	bd.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA vertexData;
//	vertexData.pSysMem = v;
//	device->CreateBuffer(&bd, &vertexData, mVertexBuffer.GetAddressOf());
//
//	// インデックスデータ用バッファの設定
//	int indexes[] =
//	{
//		0,1,2,
//		2,1,3,
//	};
//
//	mDrawNum = sizeof(indexes) / sizeof(indexes[0]);
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
//
//	mDrawNum = sizeof(v) / sizeof(v[0]);
//
//	CreateStructuredBuffer(device, mDrawNum, PlayerMgr::GetInstance()->player_vector_num, v, mStructerBuffer.GetAddressOf());
//
//
//	// 定数バッファの作成(パラメータ受け渡し用)
//	D3D11_BUFFER_DESC cb;
//	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//	device->CreateBuffer(&cb, NULL, mConstantBuffer.GetAddressOf());
//
//	//パイプラインの構築
//	ID3D11Buffer* bufs[] = { mVertexBuffer.Get() };
//	UINT stride[] = { sizeof(VERTEX) };
//	UINT offset[] = { 0 };
//	devcontext->IASetVertexBuffers(0, sizeof(bufs) / sizeof(bufs[0]), bufs, stride, offset);
//	devcontext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
//	devcontext->IASetInputLayout(mInputLayout.Get());
//
//	auto camera = CCamera::GetInstance()->GetCameraMatrix();
//
//	mView = DirectX::XMLoadFloat4x4(&camera);
//
//	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
//	mProj = DirectX::XMLoadFloat4x4(&proj);
//	mScale = XMMatrixScalingFromVector(XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f));
//	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(90.0f);
//
//}
//
//void InstanceModel::OnCreate(const char* filename, std::string texfolder)
//{
//	Init(filename, texfolder);
//
//	//インスタンス配列の作成
//	for (UINT count = 0; count < 500; count++) {
//		Player* Data;
//		Data->Init();
//		PlayerMgr::GetInstance()->instance_vector.push_back(Data);
//	}
//	auto camera = CCamera::GetInstance()->GetCameraMatrix();
//
//	mView = DirectX::XMLoadFloat4x4(&camera);
//
//	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
//	mProj = DirectX::XMLoadFloat4x4(&proj);
//	mScale = XMMatrixScalingFromVector(XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f));
//	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(90.0f);
//
//}
//
//bool InstanceModel::Update()
//{
//	// デバイスコンテキストを取得
//	ID3D11DeviceContext* devcontext;
//	devcontext = GetDX11DeviceContext();
//	// デバイスを取得
//	ID3D11Device* device;
//	device = GetDX11Device();
//
//	//インスタンスバッファにマップ
//	D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
//	D3D11_MAPPED_SUBRESOURCE mappedBuffer;
//
//	devcontext->Map(mVertexBuffer.Get(), 0, mapType, 0, &mappedBuffer);
//	
//	//行列の変更
//	auto* matrices = (XMFLOAT4X4*)mappedBuffer.pData;
//	XMFLOAT4X4 World;
//	for (size_t i = 0; i < PlayerMgr::GetInstance()->instance_vector.size(); i++) {
//		//ワールド行列の決定
//		
//		DX11MtxIdentity(World);
//		DX11MtxTranspose(World, World);
//	
//		matrices[i] = World;
//	}
//	//アンマップ
//	devcontext->Unmap(mVertexBuffer.Get(), 0);
//	return false;
//}
//
//
//void InstanceModel::RenderInstancing()
//{
//	// デバイスコンテキストを取得
//	ID3D11DeviceContext* devcontext;
//	devcontext = GetDX11DeviceContext();
//	// デバイスを取得
//	ID3D11Device* device;
//	device = GetDX11Device();
//
//	//ストライドとオフセット
//	//形状の頂点バッファと行列バッファを設定
//	UINT stride[2] = { sizeof(VERTEX), sizeof(XMFLOAT4X4) };
//	UINT offset[2] = { 0, 0 };
//	
//	ID3D11Buffer* pBuf[2] = { m_assimpfile.GetMeshes().at(0).m_VertexBuffer, mVertexBuffer.Get()};
//	devcontext->IASetVertexBuffers(0, 2, pBuf, stride, offset);
//	//インデックスバッファのセット
//	devcontext->IASetIndexBuffer(m_assimpfile.GetMeshes().at(0).m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
//
//	//描画方法（3角形）
//	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//
//	devcontext->VSSetShader(mVertexShader.Get(), NULL, 0);
//	devcontext->GSSetShader(nullptr, nullptr, 0);
//	devcontext->HSSetShader(nullptr, nullptr, 0);
//	devcontext->DSSetShader(nullptr, nullptr, 0);
//	devcontext->PSSetShader(mPixelShader.Get(), NULL, 0);
//	devcontext->IASetInputLayout(mInputLayout.Get());
//
//	//テクスチャとサンプラーの設定
//	ID3D11ShaderResourceView* pNull[1] = { 0 };
//	devcontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
//	//テクスチャーをピクセルシェーダーに渡す
//	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());
//
//
//	//コンスタントバッファの更新
//	//devcontext->UpdateSubresource(, 0, nullptr, &sb, 0, 0);
//
//	mDrawNum = sizeof(m_assimpfile.GetMeshes().at(0).m_indices * m_assimpfile.GetMeshes().size() / m_assimpfile.GetMeshes().at(0).m_indices);
//
//	// 描画実行
//	devcontext->DrawIndexedInstanced(, 0, 0, 0);
//}
//
//InstanceModel::~InstanceModel() {}
//
//
