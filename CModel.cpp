//=============================================================================
//
//　3Dモデル描画処理 [CModel.cpp]
//
//=============================================================================
#define NOMINMAX
#include	<windows.h>
#include	"CModel.h"
#include	"Shader.h"
#include	"CDirectxGraphics.h"
#include	"DX11Settransform.h"
#include	"ModelData.h"
#include"UniqueEnemy.h"

/// <summary>
/// ３Dモデル初期化処理
/// </summary>
/// <param name="filename">モデルファイル名</param>
/// <param name="vsfile">vsファイル名</param>
/// <param name="psfile">psファイル名</param>
/// <param name="texfolder">テクスチャフォルダーの場所</param>
/// <returns></returns>
bool CModel::Init(const char* filename, const char* vsfile, const char* psfile,std::string texfolder) {

	bool sts;

	//ファイル名保存
	std::string fname(filename);

	sts = m_assimpfile.Load(texfolder,fname);
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}
	m_filetype = eASSIMPFILE;

	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
     	{ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	
	};
	unsigned int numElements = ARRAYSIZE(layout);

	ID3D11Device* device;
	device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	sts = CreateVertexShader(device,
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
		device,		// デバイスオブジェクト
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

/// <summary>
/// シェーダー解放
/// </summary>
void CModel::Uninit() {

	// アニメーションデータ解放
	for (auto sa : m_animationcontainer) {
		sa->Exit();
		delete sa;
	}

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
}

// アニメーション更新
void CModel::Update(
	int m_Frame, int m_preFrame, float m_factor, int animecnt,
	const XMFLOAT4X4& mtxworld) {

	
	// ワンスキンデータ更新
	//m_assimpfile. Update( m_Frame, m_preFrame, m_factor,  animecnt, mtxworld, m_AnimFileIdx, m_animationcontainer);
	
	// OBBを更新
	//m_assimpfile.UpdateOBB(mtxworld);
}

void CModel::Update2(int animecnt, const DirectX::XMFLOAT4X4& mtxworld)
{
	m_assimpfile.Update2(animecnt, mtxworld, m_AnimFileIdx, m_animationcontainer);

}

/// <summary>
/// モデル描画
/// </summary>
/// <param name="mtxworld">モデルの行列</param>
void CModel::Draw(XMFLOAT4X4& mtxworld) {

	ID3D11DeviceContext*	devcontext;			// デバイスコンテキスト
	devcontext = GetDX11DeviceContext();
	// 頂点フォーマットをセット
	devcontext->IASetInputLayout(m_pVertexLayout);
	// 頂点シェーダーをセット
	devcontext->VSSetShader(m_pVertexShader, nullptr, 0);
	devcontext->GSSetShader(nullptr, nullptr, 0);
	devcontext->HSSetShader(nullptr, nullptr, 0);
	devcontext->DSSetShader(nullptr, nullptr, 0);
	// ピクセルシェーダーをセット
	devcontext->PSSetShader(m_pPixelShader, nullptr, 0);

	// 描画
	m_assimpfile.Draw(devcontext,mtxworld);
}
