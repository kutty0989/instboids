#include "Particle.h"
#include"Shader.h"
#include"dx11mathutil.h"
#include"DX11Settransform.h"
#include"DX11util.h"


bool Particle::Init(float x, float y, float z, float xsize, float ysize, DirectX::XMFLOAT4 color)
{
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// デバイスを取得
	ID3D11Device* dev;
	dev = GetDX11Device();


	//// シェーダの設定
	//ID3DBlob* pCompileVS = NULL;
	//ID3DBlob* pCompilePS = NULL;
	//D3DCompileFromFile(L"shader/instancevs.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	//dev->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &m_pVertexShader);
	//D3DCompileFromFile(L"shader/instancevs.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	//dev->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &m_pPixelShader);



	//m_x = x;
	//m_y = y;
	//m_z = z;
	//m_XSize = xsize;
	//m_YSize = ysize;
	//m_Color = color;
	////デバイス取得
	//ID3D11Device* dev = GetDX11Device();
	////デバイスコンテキスト取得
	//ID3D11DeviceContext* devcontext = GetDX11DeviceContext();

	//頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{	"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		};
	unsigned int numElements = ARRAYSIZE(layout);
	//頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	bool sts = CreateVertexShader(dev,
		"shader/vsbillboard.hlsl",
		"main",
		"vs_5_0",
		layout,
		numElements,
		&m_pVertexShader,
		&m_pVertexLayout);

	if (!sts)
	{
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}
	//ピクセルシェーダーを生成
	sts = CreatePixelShader(
		dev, "shader/psbillboard.hlsl",
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts)
	{
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}
	//ジオメトリーシェーダを作成
	sts = CreateGeometryShader(
		dev, "shader/psbillboard.hlsl",
		"main",
		"ps_5_0",
		&m_pGeometryShader);
	if (!sts)
	{
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	MyVertex vertices[] =
	{
		-0.5f, 0.5f, 0.0f,
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MyVertex) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	//頂点バッファをセット
	unsigned int stride = sizeof(MyVertex);
	unsigned offset = 0;


	//頂点バッファをセット
	devcontext->IASetVertexBuffers(0, 1, &m_vbuffer, &stride, &offset);


	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	dev->CreateBuffer(&bd, &InitData, &m_vbuffer);
	
	////バーテックスバッファーをセット
	//UINT stride = sizeof(SimpleVertex);
	//UINT offset = 0;
	//m_pDeviceContext->IASetVertexBuffers(0, 1, &m_vbuffer, &stride, &offset);


//	CalcVertex();//ビルボード用の頂点データを作成

	CreateBlendStateSrcAlpha();//アルファブレンディング用のブレンドステートを生成
	CreateBlendStateOne();//加算合成用ブレンドステート生成
	CreateBelndStateDefault();//でファルとのブレンドステート生成

	// 定数バッファ生成
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer2), &g_pConstantBuffer2);
	if (!sts) {
		MessageBox(nullptr, "CreateConstantBuffer2 error", "error", MB_OK);
		return false;
	}


	hp = 1.0f;
	ConstantBuffer2 cb2;
	cb2.hp = hp;//高さ変数を渡す
	devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// コンスタントバッファ更新
	devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DSへコンスタントバッファをb0レジスタへセット


	return true;
}


//ビルボードの頂点座標を計算
//void Particle::CalcVertex()
//{
//	m_Vertex[0].x = -m_XSize / 2;
//	m_Vertex[0].y = m_YSize / 2;
//	m_Vertex->z = 0.0f;
//	m_Vertex[0].color = m_Color;
//	m_Vertex[0].tu = m_uv[0].x;
//	m_Vertex[0].tv = m_uv[0].y;
//
//	m_Vertex[1].x = m_XSize / 2;
//	m_Vertex[1].y = m_YSize / 2;
//	m_Vertex->z = 0.0f;
//	m_Vertex[1].color = m_Color;
//	m_Vertex[1].tu = m_uv[1].x;
//	m_Vertex[1].tv = m_uv[1].y;
//
//	m_Vertex[2].x = -m_XSize / 2;
//	m_Vertex[2].y = -m_YSize / 2;
//	m_Vertex->z = 0.0f;
//	m_Vertex[2].color = m_Color;
//	m_Vertex[2].tu = m_uv[2].x;
//	m_Vertex[2].tv = m_uv[2].y;
//
//	m_Vertex[3].x = m_XSize / 2;
//	m_Vertex[3].y = -m_YSize / 2;
//	m_Vertex->z = 0.0f;
//	m_Vertex[3].color = m_Color;
//	m_Vertex[3].tu = m_uv[3].x;
//	m_Vertex[3].tv = m_uv[3].y;
//
//	if (m_vbuffer == nullptr) {
//		ID3D11Device* dev;
//		dev = GetDX11Device();
//
//		//頂点バッファ作成（後で変更可能な）
//		bool sts = CreateVertexBufferWrite(dev, sizeof(MyVertex), 4, m_Vertex, &m_vbuffer);
//		if (!sts) {
//			MessageBox(nullptr, "create vertex buffer erro(Particle)", "error", MB_OK);
//		}
//	}
//	else {
//		//作成済みなら内容を書き換える
//		D3D11_MAPPED_SUBRESOURCE pData;
//		ID3D11DeviceContext* devcontext;
//		devcontext = GetDX11DeviceContext();
//		HRESULT hr = devcontext->Map(m_vbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
//		if (SUCCEEDED(hr)) {
//			memcpy_s(pData.pData, pData.RowPitch, (void*)(m_Vertex), sizeof(MyVertex) * 4);
//			devcontext->Unmap(m_vbuffer, 0);
//		}
//	}
//}

//サイズをセット
void Particle::SetSize(float x, float y)
{
	m_XSize = x;
	m_YSize = y;
//	CalcVertex();
}



//位置をセット
void Particle::SetPosiotion(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Particle::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

//ビルボード用の行列を生成
void Particle::CalParticleMatrix(const DirectX::XMFLOAT4X4& cameramat)
{
	m_mtx._11 = cameramat._11;
	m_mtx._12 = cameramat._21;
	m_mtx._13 = cameramat._31;

	m_mtx._21 = cameramat._12;
	m_mtx._22 = cameramat._22;
	m_mtx._23 = cameramat._32;

	m_mtx._31 = cameramat._13;
	m_mtx._32 = cameramat._23;
	m_mtx._33 = cameramat._33;

	m_mtx._41 = m_x;
	m_mtx._42 = m_y;
	m_mtx._43 = m_z;

	m_mtx._14 = 0;
	m_mtx._24 = 0;
	m_mtx._34 = 0;
	m_mtx._44 = 1;
}

//描画
void Particle::Draw()
{
	//Zバッファ無効化
  //  TurnOnAlphablend();
	TurnOffZbuffer();

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//シェーダーリソースビューをピクセルシェーダーへセット
	devcontext->PSSetShaderResources(5, 1, &m_srv);
	DX11MtxIdentity(t_mtx);
	DX11MtxIdentity(s_mtx);
	DX11MtxTranslation(XMFLOAT3(m_x, m_y, m_z), t_mtx);
	DX11MtxScale(scale.x, scale.y, scale.z, s_mtx);
	DX11MtxIdentity(o_mtx);

	DX11MtxRotationZ(angle, o_mtx);//回転行列
	DirectX::XMFLOAT4X4 mtx;

	DX11MtxMultiply(mtx, s_mtx, o_mtx);
	DX11MtxMultiply(m_mtx, mtx, m_mtx);
	//DX11MtxMultiply(m_mtx,mtx, m_mtx);

	//ワールド変換行列
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, m_mtx);

	//インデックスバッファをセット
	//m_devcontext->IASetIndexBuffers(nullptr,DXGI_FORMAT_R32_UINT,0);
	//とぽろーじーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点フォーマットをセット
	devcontext->IASetInputLayout(m_pVertexLayout);

	//4角形描画
	devcontext->VSSetShader(m_pVertexShader, nullptr, 0);//頂点シェーダーをセット
	devcontext->GSSetShader(m_pGeometryShader, nullptr, 0);
	devcontext->HSSetShader(nullptr, nullptr, 0);
	devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(m_pPixelShader, nullptr, 0);//ピクセルシェーダーをせっと
	devcontext->Draw(4, 0);

	TurnOnZbuffer();
	//TurnOffAlphablend();
	//Zバッファを有効か
	//TurnOnZbuffer();

}

//ビルボードを描画
void Particle::DrawBillBoard(const XMFLOAT4X4& cameramat) {
	//カメラ行列からビルボード用のマトリックスを作成
	CalParticleMatrix(cameramat);

	//αブレンディングをセットする
//	SetBlendStrateAlpha();

	//描画
	Draw();

	//αブレンディングをセット
//SetBlendStrateDefault();
}

//ビルボードを描画
void Particle::DrawBillBoardAdd(const XMFLOAT4X4& cameramat) {
	//カメラ行列からビルボード用のマトリックスを作成
	CalParticleMatrix(cameramat);

	//描画
	//アルファブレンディングをセット
	SetBlendStateOne();
	//描画
	Draw();

	//アルファブレンディングをセット
	SetBlendStateDefault();
}
//

void Particle::SetBlendStateDefault()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	devcontext->OMSetBlendState(m_pBlendStateDefault, blendFactor, 0xffffffff);

}

void Particle::SetBlendStateSrcAlpha()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	devcontext->OMSetBlendState(m_pBlendStateSrcAlpha, blendFactor, 0xffffffff);
}


void Particle::SetBlendStateOne()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	devcontext->OMSetBlendState(m_pBlendStateOne, blendFactor, 0xffffffff);
}

void Particle::CreateBlendStateSrcAlpha() {
	D3D11_BLEND_DESC BlendDesc;

	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;//配列０番のみ仕様

	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11Device* dev;
	dev = GetDX11Device();

	dev->CreateBlendState(&BlendDesc, &m_pBlendStateSrcAlpha);

}

void Particle::CreateBlendStateOne() {
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;//配列０番目のみ使用

	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	ID3D11Device* dev;
	dev = GetDX11Device();

	dev->CreateBlendState(&BlendDesc, &m_pBlendStateOne);
}

void Particle::CreateBelndStateDefault() {

	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;//配列０番目のみ使用

	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	ID3D11Device* dev;
	dev = GetDX11Device();

	dev->CreateBlendState(&BlendDesc, &m_pBlendStateDefault);

}

void Particle::PartMax(float x, float y)
{
	PMaxX = x;
	PMaxY = y;
}

void Particle::Part(float x, float y)
{
	float px = 1 / PMaxX;
	float py = 1 / PMaxY;
	m_uv[0].x = x * px;
	m_uv[0].y = y * py;
	m_uv[1].x = x * px;
	m_uv[1].y = y * py + py;
	m_uv[2].x = x * px + px;
	m_uv[2].y = y * py;
	m_uv[3].x = x * px + px;
	m_uv[3].y = y * py + py;
	//CalcVertex();
}

//ビルボードを描画（Z軸で回転）
void Particle::DrawRotateBillBoard(const DirectX::XMFLOAT4X4& cameramat, float angle)
{
	//カメラ行列から　ビルボード用のマトリックスを作成
	CalParticleMatrix(cameramat);

	//Z軸回転行列を作成
	DirectX::XMFLOAT4X4 matRotZ;
	DirectX::XMFLOAT3 axisZ = { cameramat._13,cameramat._23,cameramat._33 };

	//指定軸回転の行列を作成
	DX11MtxRotationAxis(axisZ, angle, matRotZ);

	//行列を合成し、位置をセット
	DX11MtxMultiply(m_mtx, m_mtx, matRotZ);
	m_mtx._41 = m_x;
	m_mtx._42 = m_y;
	m_mtx._43 = m_z;

	//アルファブレンディングをセット
	//SetBlendStateSrcAlpha();

	//描画
	Draw();



}

//テクスチャを読み込む
bool Particle::LoadTexTure(const char* filename)
{
	//すでに読み込まれているテクスチャがあれば開放する
	if (m_srv != nullptr)
	{
		m_srv->Release();
		m_srv = nullptr;
	}

	ID3D11Device* dev = GetDX11Device();
	ID3D11DeviceContext* devcontext = GetDX11DeviceContext();

	bool sts = CreateSRVfromFile(filename,
		dev, devcontext, &m_res, &m_srv);

	if (sts == false)
	{
		MessageBox(nullptr, "textureload error(Particle LOADTEXTURE)", "error", MB_OK);
		return false;
	}

	return true;
}

