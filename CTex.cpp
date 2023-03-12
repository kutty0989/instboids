//=============================================================================
//
// テクスチャー生成クラス [CTex.h]
//
//=============================================================================

#include	"CTex.h"

// comptr
using Microsoft::WRL::ComPtr;

// 使用する頂点シェーダー名
const char* vstexfilename[] = {
	"shader/vsquad2d.hlsl"
};

// 使用するピクセルシェーダー名
const char* pstexfilename[] = {
	"shader/pstexcol.hlsl"
};

/// <summary>
/// 矩形の初期化
/// </summary>
/// <param name="width">横幅</param>
/// <param name="height">立幅</param>
/// <param name="color">色</param>
/// <returns></returns>
bool CTex::Init(uint32_t width,
	uint32_t height,
	DirectX::XMFLOAT3 color) {

	DX11MtxIdentity(m_worldmtx);	// 初期姿勢

	// ピクセルシェーダーを生成
	bool sts = ShaderHashmap::GetInstance()->SetPixelShader(pstexfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error", "error", MB_OK);
		return false;
	}

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
		vstexfilename[0],			// 頂点シェーダーファイル名
		layout,					// 頂点レイアウト
		numElements);			// エレメント数

	// 頂点初期化
	updateVertex(width, height, color);

	// デバイスを取得
	ID3D11Device* device;
	device = GetDX11Device();

	// 頂点バッファを生成
	sts = CreateVertexBufferWrite(
		device,						// デバイスオブジェクト
		sizeof(CTex::Vertex),		// １頂点当たりバイト数
		4,							// 頂点数
		m_vertex,					// 頂点データ格納メモリ先頭アドレス
		&m_vertexbuffer				// 頂点バッファ
	);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return false;
	}

	// インデックスバッファを生成
	uint32_t index[4] = { 0,1,2,3 };

	sts = CreateIndexBuffer(
		device,						// デバイスオブジェクト
		4,							// インデックス数
		index,						// インデックス格納メモリ先頭アドレス
		&m_indexbuffer				// インデックスバッファ
	);
	if (!sts) {
		MessageBox(nullptr, "CreateIndexBuffer error", "error", MB_OK);
		return false;
	}

	// ビューポートサイズセット
	SetViewPortSize(DX11GetScreenWidth(), DX11GetScreenHeight());

	return true;
}

/// <summary>
/// 描画処理
/// </summary>
void CTex::Draw() {

	TurnOffZbuffer();
	// デバイスコンテキストを取得
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	XMFLOAT4X4 vmtx;
	XMFLOAT4X4 pmtx;
	DX11MtxIdentity(pmtx);
	DX11MtxIdentity(vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, pmtx);

	// テクスチャをセット
	devcontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());

	//行列計算
	DX11MtxIdentity(p_mtx);
	DX11MtxIdentity(s_mtx);
	DX11MtxIdentity(o_mtx);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);
	DX11MtxTranslation(m_pos, p_mtx);
    DX11MtxRotationZ(m_angle, o_mtx);//回転行列
    DirectX::XMFLOAT4X4 mtx;
	DX11MtxIdentity(mtx);
	DX11MtxMultiply(mtx, s_mtx, o_mtx);
	DX11MtxMultiply(mtx, mtx, p_mtx);//スケール　＊　回転　＊　移動


	// 座標変換用の行列をセット
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtx);


	unsigned int stride = sizeof(CTex::Vertex);	// ストライドをセット（１頂点当たりのバイト数）
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

	// トポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 頂点シェーダー、ピクセルシェーダー取得
	ID3D11VertexShader* vs;
	vs = ShaderHashmap::GetInstance()->GetVertexShader(vstexfilename[0]);
	ID3D11PixelShader* ps;
	ps = ShaderHashmap::GetInstance()->GetPixelShader(pstexfilename[0]);

	// 頂点レイアウト取得
	ID3D11InputLayout* layout;
	layout = ShaderHashmap::GetInstance()->GetVertexLayout(vstexfilename[0]);

	//各シェーダーにセット
	devcontext->VSSetShader(vs, nullptr, 0);
	//devcontext->GSSetShader(nullptr, nullptr, 0);
	//devcontext->HSSetShader(nullptr, nullptr, 0);
	//devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(ps, nullptr, 0);

	// 頂点フォーマットをセット
	devcontext->IASetInputLayout(layout);


	// ドローコール発行
	devcontext->DrawIndexed(
		4,						// インデックス数
		0,						// 開始インデックス
		0);						// 基準頂点インデックス

	TurnOnZbuffer();

}

/// <summary>
/// 終了処理
/// </summary>
void CTex::UnInit() {
	//ID3D11VertexShader* vs;
	//vs = ShaderHashmap::GetInstance()->GetVertexShader(vstexfilename[0]);
	//ID3D11PixelShader* ps;
	//ps = ShaderHashmap::GetInstance()->GetPixelShader(pstexfilename[0]);

	//// 頂点レイアウト取得
	//ID3D11InputLayout* layout;
	//layout = ShaderHashmap::GetInstance()->GetVertexLayout(vstexfilename[0]);

	//// 頂点シェーダー解放
	//if (vs) {
	//	vs->Release();
	//	vs = nullptr;
	//}

	//// ピクセルシェーダー解放
	//if (ps) {
	//	ps->Release();
	//	ps = nullptr;
	//}

	//// 頂点レイアウト解放
	//if (layout) {
	//	layout->Release();
	//	layout = nullptr;
	//}
}

// 拡大、縮小
void CTex::SetScale(float sx, float sy, float sz) {
	m_scale.x = sx;
	m_scale.y = sy;
	m_scale.z = sz;
}

// 位置をセット
void CTex::SetPosition(float x, float y, float z) {
	m_pos.x = Application::CLIENT_WIDTH * 0.5f + Application::CLIENT_WIDTH * 0.5f * x;
	m_pos.y = Application::CLIENT_HEIGHT * 0.5f + Application::CLIENT_HEIGHT * 0.5f * y;
	m_pos.z = z;
}

// Z軸回転
void CTex::SetRotation(float angle) {
	m_angle = angle;
}
void CTex::SetUV(XMFLOAT2* muv)
{
	c_uv[0] = muv[0];
	c_uv[1] = muv[1];
	c_uv[2] = muv[2];
	c_uv[3] = muv[3];

}

void CTex::SetAlpha(float a)
{
	m_Alpha = a;

}

void CTex::PartMax(float x, float y)
{
	PMaxX = x;
	PMaxY = y;
}

void CTex::Part(float x, float y)
{
	float px = 1 / PMaxX;
	float py = 1 / PMaxY;
	c_uv[0].x = x * px;
	c_uv[0].y = y * py;
	c_uv[1].x = x * px + px;
	c_uv[1].y = y * py;
	c_uv[2].x = x * px;
	c_uv[2].y = y * py+py;
	c_uv[3].x = x * px + px;
	c_uv[3].y = y * py + py;
	
}

// 頂点データ更新
void CTex::updateVertex(uint32_t width,
	uint32_t height,
	DirectX::XMFLOAT3 color) {

	m_width = static_cast<float>(width);
	m_height = static_cast<float>(height);


		CTex::Vertex	v[4] = {
			// 座標													// カラー	// UV	
			XMFLOAT3(-m_width ,	-m_height , 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[0],
			XMFLOAT3(m_width ,	-m_height, 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[1],
			XMFLOAT3(-m_width ,	 m_height , 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[2],
			XMFLOAT3(m_width ,	 m_height, 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[3]
		};
		for (int i = 0; i < 4; i++) {
			m_vertex[i] = v[i];
		}
}

// 頂点バッファ更新
void CTex::updateVbuffer() {
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetDX11DeviceContext()->Map(m_vertexbuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_vertex), sizeof(CTex::Vertex) * 4);
		GetDX11DeviceContext()->Unmap(m_vertexbuffer.Get(), 0);
	}
}