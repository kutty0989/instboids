#include"CHeight_Map.h"
#include"Application.h"
#include"Seiha.h"
#include"noise.h"
#include"player.h"
#define debuglog(a) std::cout<<a<<std::endl;

float CHeight_Map::g_hight;
float CHeight_Map::g_tesselationamount;
float CHeight_Map::g_col;
bool CHeight_Map::mapsave = false;
bool CHeight_Map::mapload = false;
float CHeight_Map::ScaleMap = 2.0f;
std::vector<std::vector<double> > CHeight_Map::vData;
std::vector<std::vector<double> > CHeight_Map::gData;
std::vector<byte> CHeight_Map::bufsrc;
// comptr
using Microsoft::WRL::ComPtr;


// 使用する頂点シェーダー名
const char* vsfilename[] = {
	"shader/VSTess+Disp.hlsl"
};

// 使用するピクセルシェーダー名
const char* psfilename[] = {
	"shader/psheight.hlsl"
};

// 使用するハルシェーダー名
const char* hullfilename[] = {
	"shader/HSTess+Disp.hlsl"
};
// 使用するドメインシェーダー名
const char* dsfilename[] = {
	"shader/DSTess+Disp.hlsl"
};

//float cosC;
//float sinC;

// 矩形の初期化
bool CHeight_Map::Init(DirectX::XMFLOAT3 color) {


	bool sts;

	DX11MtxIdentity(m_worldmtx);// 初期姿勢

	// デバイスを取得
	ID3D11Device* device;
	device = GetDX11Device();


	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};


	// エレメント数
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーを生成
	sts = ShaderHashmap::GetInstance()->SetVertexShader(
		vsfilename[0],			// 頂点シェーダーファイル名
		layout,					// 頂点レイアウト
		numElements);			// エレメント数
	if (!sts) {
		MessageBox(nullptr, "SetVertexShader error", "error", MB_OK);
		return false;
	}

	// ピクセルシェーダーを生成
	sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error", "error", MB_OK);
		return false;
	}

	// ハルシェーダーを生成
	sts = ShaderHashmap::GetInstance()->SetHullShader(hullfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetHullShader error", "error", MB_OK);
		return false;
	}

	// ドメインシェーダーを生成
	sts = ShaderHashmap::GetInstance()->SetDomainShader(dsfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetDomainShader error", "error", MB_OK);
		return false;
	}

	// 頂点バッファを生成
	sts = CreateVertexBufferWrite(
		device,						// デバイスオブジェクト
		sizeof(CHeight_Map::Vertex),		// １頂点当たりバイト数
		4,							// 頂点数
		m_vertex,					// 頂点データ格納メモリ先頭アドレス
		&m_vertexbuffer				// 頂点バッファ
	);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return false;
	}


	// インデックスバッファを生成
	uint32_t index[6] = { 0,1,2,
						 2,1,3 };

	sts = CreateIndexBuffer(
		device,						// デバイスオブジェクト
		6,							// インデックス数
		index,						// インデックス格納メモリ先頭アドレス
		m_indexbuffer.GetAddressOf()				// インデックスバッファ
	);
	if (!sts) {
		MessageBox(nullptr, "CreateIndexBuffer error", "error", MB_OK);
		return false;
	}

	// 定数バッファ生成
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer), &g_pConstantBuffer);
	if (!sts) {
		MessageBox(nullptr, "CreateConstantBuffer error", "error", MB_OK);
		return false;
	}

	// 定数バッファ生成
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer2), &g_pConstantBuffer2);
	if (!sts) {
		MessageBox(nullptr, "CreateConstantBuffer2 error", "error", MB_OK);
		return false;
	}
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(BlendBuffer), &g_pConstantBlendBuffer);
	if (!sts) {
		MessageBox(nullptr, "BlendBuffer error", "error", MB_OK);
		return false;
	}

	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	g_tesselationamount = 64;
	ConstantBuffer cb;
	cb.tessellationAmount = g_tesselationamount;//分割数を渡す
	devcontext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);	// コンスタントバッファ更新
	devcontext->HSSetConstantBuffers(7, 1, &g_pConstantBuffer);				// HULLシェーダーへコンスタントバッファをb0レジスタへセット
	
	g_hight = 500.0f;
	ConstantBuffer2 cb2;
	cb2.hight = g_hight;//高さ変数を渡す
	devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// コンスタントバッファ更新
	devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DSへコンスタントバッファをb0レジスタへセット


	///////////////２D画像の生成///////////////////
	//テクスチャの作成
	D3D11_TEXTURE2D_DESC td;
	td.Width = iPixSize;
	td.Height = iPixSize;
	td.MipLevels = 1;//元となるテクスチャのサイズを半分に縮小したもの　メモリ量は増えるがテクスチャを縮小してサンプリングする再自然に　使わないので１
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DYNAMIC;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	td.MiscFlags = 0;
	HRESULT hr = device->CreateTexture2D(&td, nullptr, &D3DTexture);
	if (FAILED(hr))
		return hr;

	//テクスチャ書き替え
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//パーリンノイズ計算
	Noise perlin;
	std::vector<std::vector<double> > vecData(iPixSize, std::vector<double>(iPixSize));//vecData[iPixSize][iPixSize];
	double dFrequencyX = iPixSize / dFrequency;
	double dFrequencyY = dFrequencyX;
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			vecData[x][y] = perlin.Octave(x / dFrequencyX, y / dFrequencyY, 0.0, iOctaves);
			
		}
	}
	gData = vecData;
	//パーリンノイズ計算結果をテクスチャに反映
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//ビットマップを黒で初期化
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			gData[x][y] = 0.0f;
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(vecData[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(vecData[x][y] * 255);//Green
			//srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(vecData[x][y] * 255);//Blue
		}
	}


	
	vData = vecData;//ピクセル情報保存
	//gData = vData;
	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);

	//シェーダリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	sts = device->CreateShaderResourceView(D3DTexture.Get(), &srv, &D3DShaderResourceView);
	if (FAILED(sts))
		return sts;

	///////画像生成終了
	
	// ビューポートサイズセット
	SetViewPortSize(DX11GetScreenWidth(), DX11GetScreenHeight());

	// 頂点初期化
	updateVertex(color);
	return true;
}
static int blendtex = 0;
static bool noiseCreateflg = false;

// 描画
void CHeight_Map::Draw() {

	if (noiseCreateflg)
	{
		NoiseCreate();
		noiseCreateflg = false;
	}
	TurnOffZbuffer();
	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("Ground");
		ImGui::SetNextWindowSize(ImVec2(300, 300));
	
		ImGui::SliderFloat("Height", &g_hight, 0.0f, 1000.0f);
		ImGui::SliderFloat("tesslation", &g_tesselationamount, 0.0f, 64.0f);

		ImGui::InputDouble("Frequency", &dFrequency);
		ImGui::DragInt("iOctaves", &iOctaves);
		ImGui::DragFloat("scale", &ScaleMap);
		
		if (ImGui::Button("RandomCreate"))
		{
			noiseCreateflg = true;
		}
		if (ImGui::Button("MapSave"))
		{
			mapsave = true;
		}

		if (ImGui::Button("MapLoad"))
		{
			mapload = true;
		}

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);
	DX11MtxTranslation(m_pos, p_mtx);
	DX11MtxRotationX(m_angle.x, o_mtx);//回転行列
	//DX11MtxRotationY(m_angle.y, o_mtx);//回転行列
	//DX11MtxRotationZ(m_angle.z, o_mtx);//回転行列
	DirectX::XMFLOAT4X4 mtx;
	DX11MtxMultiply(mtx, s_mtx, o_mtx);
	DX11MtxMultiply(m_worldmtx, mtx, p_mtx);//スケール　＊　回転　＊　移動

	//// 座標変換用の行列をセット
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, m_worldmtx);

	unsigned int stride = sizeof(CHeight_Map::Vertex);	// ストライドをセット（１頂点当たりのバイト数）
	unsigned  offset = 0;						// オフセット値をセット


	// 頂点バッファをデバイスコンテキストへセット
	devcontext->IASetVertexBuffers(
		0,									// スタートスロット
		1,									// 頂点バッファ個数
		m_vertexbuffer.GetAddressOf(),		// 頂点バッファの先頭アドレス
		&stride,							// ストライド
		&offset);							// オフセット

	// インデックスバッファをデバイスコンテキストへセット
	devcontext->IASetIndexBuffer(
		m_indexbuffer.Get(),				// インデックスバッファ
		DXGI_FORMAT_R32_UINT,				// フォーマット
		0);									// オフセット

	//プリミティブトポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	// 頂点レイアウト取得
	ID3D11InputLayout* layout;
	layout = ShaderHashmap::GetInstance()->GetVertexLayout(vsfilename[0]);

	// 頂点フォーマットをセット
	devcontext->IASetInputLayout(layout);

	//ピクセルシェーダーにTXTUREE　SRVをセット	

	SetTexture();

	devcontext->PSSetShaderResources(0, 1, D3DShaderResourceView.GetAddressOf());///画像１ををPSセット　描画する

	//devcontext->PSSetShaderResources(4, 1, m_srv[3].GetAddressOf());///パーリーノイズをPSセット　描画する
	//ドメインシェーダーにTXTUREE　SRVをセット
	devcontext->DSSetShaderResources(0, 1, D3DShaderResourceView.GetAddressOf());//パーリノイズをDSにセット高さを作る

	// 頂点シェーダー、ピクセルシェーダー取得
	ID3D11VertexShader* vs;
	vs = ShaderHashmap::GetInstance()->GetVertexShader(vsfilename[0]);
	ID3D11PixelShader* ps;
	ps = ShaderHashmap::GetInstance()->GetPixelShader(psfilename[0]);

	//ハルシェーダー
	ID3D11HullShader* hull;
	hull = ShaderHashmap::GetInstance()->GetHullShader(hullfilename[0]);
	//ドメインシェーダー登録
	ID3D11DomainShader* ds;
	ds = ShaderHashmap::GetInstance()->GetDomainShader(dsfilename[0]);

	//テクスチャーをドメインシェーダーに渡す
	devcontext->DSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());
	//テクスチャーをピクセルシェーダーに渡す
	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());


	ConstantBuffer cb;
	cb.tessellationAmount = g_tesselationamount;//分割数を渡す
	cb.gcol = g_col;//分割数を渡す
	devcontext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);	// コンスタントバッファ更新
	devcontext->HSSetConstantBuffers(7, 1, &g_pConstantBuffer);				// HULLシェーダーへコンスタントバッファをb0レジスタへセット
	devcontext->PSSetConstantBuffers(7, 1, &g_pConstantBuffer);				// HULLシェーダーへコンスタントバッファをb0レジスタへセット


	ConstantBuffer2 cb2;
	cb2.hight = g_hight;
	devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// コンスタントバッファ更新
	devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DSへコンスタントバッファをb0レジスタへセット


	//4角形描画
	devcontext->VSSetShader(vs, nullptr, 0);
	devcontext->GSSetShader(nullptr, nullptr, 0);
	devcontext->HSSetShader(hull, nullptr, 0);
	devcontext->DSSetShader(ds, nullptr, 0);
	devcontext->PSSetShader(ps, nullptr, 0);


	//// ドローコール発行
	devcontext->DrawIndexed(
		6,						// インデックス数
		0,						// 開始インデックス
		0);						// 基準頂点インデックス
	TurnOnZbuffer();
}

void CHeight_Map::UnInit() {
	ID3D11VertexShader* vs;
	vs = ShaderHashmap::GetInstance()->GetVertexShader(vsfilename[0]);
	ID3D11PixelShader* ps;
	ps = ShaderHashmap::GetInstance()->GetPixelShader(psfilename[0]);
	ID3D11HullShader* hull;
	hull = ShaderHashmap::GetInstance()->GetHullShader(hullfilename[0]);
	ID3D11DomainShader* ds;
	ds = ShaderHashmap::GetInstance()->GetDomainShader(dsfilename[0]);
	// 頂点レイアウト取得
	ID3D11InputLayout* layout;
	layout = ShaderHashmap::GetInstance()->GetVertexLayout(vsfilename[0]);



	// 頂点シェーダー解放
	if (vs) {
		vs->Release();
		vs = nullptr;
	}

	// ピクセルシェーダー解放
	if (ps) {
		ps->Release();
		ps = nullptr;
	}
	// ハルシェーダー解放
	if (hull) {
		hull->Release();
		hull = nullptr;
	}
	// ピクセルシェーダー解放
	if (ds) {
		ds->Release();
		ds = nullptr;
	}

	// 頂点レイアウト解放
	if (layout) {
		layout->Release();
		layout = nullptr;
	}
}


//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}


// 拡大、縮小
void CHeight_Map::SetScale(XMFLOAT3 scale) {
	m_scale = scale;
}

// 位置をセット
void CHeight_Map::SetPosition(XMFLOAT3 pos) {
	m_pos = pos;
}

// Z軸回転
void CHeight_Map::SetRotation(float x,float y,float z) {
	m_angle.x= x;
	m_angle.y= y;
	m_angle.z= z;
}
void CHeight_Map::SetUV(XMFLOAT2* muv)
{
	c_uv[0] = muv[0];
	c_uv[1] = muv[1];
	c_uv[2] = muv[2];
	c_uv[3] = muv[3];

}

void CHeight_Map::SetAlpha(float a)
{
	m_Alpha = a;

}



// 頂点データ更新
void CHeight_Map::updateVertex(DirectX::XMFLOAT3 color) {

	

		CHeight_Map::Vertex	v[4] = {
			// 座標													// カラー	// UV	
			XMFLOAT3(-m_width / 2.0f,	 m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[0],
			XMFLOAT3(m_width / 2.0f,	 m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[1],
			XMFLOAT3(-m_width / 2.0f,	 -m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[2],
			XMFLOAT3(m_width / 2.0f,	 -m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[3],
		};
		for (int i = 0; i < 4; i++) {
			m_vertex[i] = v[i];
		}
		//}
	
}

// 頂点バッファ更新
void CHeight_Map::updateVbuffer() {
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetDX11DeviceContext()->Map(m_vertexbuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_vertex), sizeof(CHeight_Map::Vertex) * 4);
		GetDX11DeviceContext()->Unmap(m_vertexbuffer.Get(), 0);
	}
}


void CHeight_Map::NoiseCreate()
{
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//テクスチャ書き替え
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//パーリンノイズ計算
	Noise perlin;
	std::vector<std::vector<double> > vecData(iPixSize, std::vector<double>(iPixSize));//vecData[iPixSize][iPixSize];
	double dFrequencyX = iPixSize / dFrequency;
	double dFrequencyY = dFrequencyX;
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			vecData[x][y] = perlin.Octave(x / dFrequencyX, y / dFrequencyY, 0.0, iOctaves);


		}
	}
	
	//パーリンノイズ計算結果をテクスチャに反映
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//ビットマップを黒で初期化
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
	
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(vecData[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(vData[x][y] * 255);//Green
		//	srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(vecData[x][y] * 255);//Blue
		}
	}
	vData = vecData;
	//gData = vData;

	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);


}

std::vector<std::vector<double>> CHeight_Map::CreateOnly()
{
	//パーリンノイズ計算
	Noise perlin;
	std::vector<std::vector<double> > vecData(iPixSize, std::vector<double>(iPixSize));//vecData[iPixSize][iPixSize];
	double dFrequencyX = iPixSize / dFrequency;
	double dFrequencyY = dFrequencyX;
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			vecData[x][y] = perlin.Octave(x / dFrequencyX, y / dFrequencyY, 0.0, iOctaves);
		}
	}
	vData = vecData;

	return vecData;
}

void CHeight_Map::LoadMap(std::vector<std::vector<double>> loadmap)
{

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//テクスチャ書き替え
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


	//パーリンノイズ計算結果をテクスチャに反映
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//ビットマップを黒で初期化
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(loadmap[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(loadmap[x][y] * 255);//Green
		//	srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(loadmap[x][y] * 255);//Blue
		}
	}

	vData = loadmap;
	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);

}

void CHeight_Map::BlendMap(std::vector<std::vector<double>> loadmap)
{
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//テクスチャ書き替え
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//ビットマップを黒で初期化
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			//2枚の地面の高さ情報を時間で線形補完
			auto blendcolor = LeapID<double>(static_cast<byte>(vData[x][y]*255), static_cast<byte>(loadmap[x][y]*255),Seiha::pertime);
			srcData[(x + y * iPixSize) * 4] = blendcolor;//Red
		
			gData[x][y] = blendcolor;
		}
	}


	if (Seiha::pertime == 0.0f)
	{
		vData = gData;
		
	}
	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);
}

void CHeight_Map::ChangeMap()
{

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//テクスチャ書き替え
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


	//パーリンノイズ計算結果をテクスチャに反映
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//ビットマップを黒で初期化
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(vData[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(gData[x][y] * 255);//Green
		//	srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(vData[x][y] * 255);//Blue
		}
	}
	vData = vData;

	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);

}





static int multitex = 0;
static bool soil = false;
static bool snow = false;
static bool grass = false;

int CHeight_Map::onetex = 0;
int CHeight_Map::twotex = 0;
int CHeight_Map::theretex = 0;

float CHeight_Map::blendone = 1.0f;
float CHeight_Map::blendtwo = 1.0f;
float CHeight_Map::blendthere = 1.0f;
float CHeight_Map::blendfour = 1.0f;


void CHeight_Map::SetTexture()
{


	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	if (g_col == 0)
	{
		{
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

			ImGui::Begin("BaseTex_One");
			ImGui::SetNextWindowSize(ImVec2(300, 400));
			//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

			ImGui::Checkbox("soil", &soil);
			ImGui::Checkbox("snow", &snow);
			ImGui::Checkbox("grass", &grass);
			ImGui::End();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		if (soil)
		{
			onetex = 1;
			g_col = 1;
		}
		else if (snow)
		{
			g_col = 1;
			onetex = 2;
		}
		else if (grass)
		{
			g_col = 1;
			onetex = 3;
		}
	}
	if (g_col >= 1)
	{
		devcontext->PSSetShaderResources(1, 1, m_srv[onetex - 1].GetAddressOf());///高さによって変える画像２をPSセット　描画する

		if (g_col == 1)
		{
			soil = false;
			snow = false;
			grass = false;

			{
				ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

				ImGui::Begin("BaseTex_One");
				ImGui::SetNextWindowSize(ImVec2(300, 400));
				//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

				ImGui::Checkbox("soil", &soil);
				ImGui::Checkbox("snow", &snow);
				ImGui::Checkbox("grass", &grass);
				ImGui::End();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			if (soil)
			{
				twotex = 1;
				g_col = 2;
			}
			else if (snow)
			{
				g_col = 2;
				twotex = 2;
			}
			else if (grass)
			{
				g_col = 2;
				twotex = 3;
			}
		}
	}
	if (g_col >= 2)
	{
		devcontext->PSSetShaderResources(2, 1, m_srv[twotex - 1].GetAddressOf());///高さによって変える画像２をPSセット　描画する

		if (g_col == 2)
		{
			soil = false;
			snow = false;
			grass = false;

			{
				ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

				ImGui::Begin("BaseTex_TWO");
				ImGui::SetNextWindowSize(ImVec2(300, 400));
				//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

				ImGui::Checkbox("soil", &soil);
				ImGui::Checkbox("snow", &snow);
				ImGui::Checkbox("grass", &grass);
				ImGui::End();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			if (soil)
			{
				theretex = 1;
				g_col = 3;
			}
			else if (snow)
			{
				g_col = 3;
				theretex = 2;
			}
			else if (grass)
			{
				g_col = 3;
				theretex = 3;
			}
		}
	}
	if (g_col >= 3)
	{
		soil = false;
		snow = false;
		grass = false;
		devcontext->PSSetShaderResources(3, 1, m_srv[theretex - 1].GetAddressOf());///高さによって変える画像２をPSセット　描画する

		g_col = 4;
	
	}
	if (g_col >= 4)
	{
		
		
		cb10.blendone = blendone;//高さ変数を渡す
		cb10.blendtwo = blendtwo;//高さ変数を渡す
		cb10.blendthere = blendthere;//高さ変数を渡す
		cb10.blendfour = blendfour;//高さ変数を渡す
		devcontext->UpdateSubresource(g_pConstantBlendBuffer, 0, nullptr, &cb10, 0, 0);		// コンスタントバッファ更新
		devcontext->PSSetConstantBuffers(10, 1, &g_pConstantBlendBuffer);					// DSへコンスタントバッファをb0レジスタへセット

	//	soil = false;
	//	snow = false;
	//	grass = false;
	//	devcontext->PSSetShaderResources(4, 1, m_srv[theretex - 1].GetAddressOf());///高さによって変える画像２をPSセット　描画する

		{
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

			ImGui::Begin("BlendTex");
			ImGui::SetNextWindowSize(ImVec2(300, 400));
			ImGui::DragFloat("one", &blendone);
			ImGui::DragFloat("two", &blendtwo);
	
			ImGui::End();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
	//	if (soil)
	//	{
	//		theretex = 1;
	//		g_col = 2;
	//	}
	//	else if (snow)
	//	{
	//		g_col = 2;
	//		theretex = 2;
	//	}
	//	else if (grass)
	//	{
	//		g_col = 2;
	//		theretex = 3;
	//	}
	//
	}

}

double CHeight_Map::GetHeightColor(XMFLOAT2 playerpos)
{
	int p_posx = (int)playerpos.x;//配列探索するためにキャストで桁を落とす
	int p_posy = (int)playerpos.y;

	double col = vData[p_posx][p_posy];//落とした値で見てくる
	double xcol = vData[p_posx+1][p_posy];//ｘ成分の１つ次
	double ycol = vData[p_posx][p_posy+1];//ｙ成分の１つ次
	
	float xf = playerpos.x;
	float yf = playerpos.y;

	float xx = xf - p_posx;//桁落ちした値を見てくる
	float yy = yf - p_posy;

	//桁落ちした分線形補完で高さを求める
	float xxcol = LeapID<float>(col, xcol, xx);
	float yycol = LeapID<float>(col, ycol, yy);

	col = (xxcol + yycol) / 2.0f;//ｘ成分とｙ成分を足して１点の（カラー）高さlar

	
	return col;
}


double CHeight_Map::GetGoHeightColor(XMFLOAT2 playerpos,float anglex, float angley)
{
	float to_pposx = playerpos.x + anglex;
	float to_pposy = playerpos.y - angley;
	double tocol =  GetHeightColor(XMFLOAT2(to_pposx,to_pposy));//行先のカラー　高さ

	return tocol;
}
