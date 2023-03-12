#pragma once
//=============================================================================
//
// ３Dモデル描画処理 [CModel.h]
//
//=============================================================================
#include"ModelData.h"
#include"uncopyable.h"
#include<d3d11.h>
#include<vector>
#include"animationdataassimp.h"
#include"obb.h"


using Microsoft::WRL::ComPtr;

class CModel : public Uncopyable {
private:
	//ファイル形式
	enum FILETYPE {
		eDATFILE,
		eASSIMPFILE
	};

	FILETYPE				m_filetype = eASSIMPFILE;		// ファイルタイプ
	std::vector<AnimationDataAssimp*> m_animationcontainer;
	ID3D11VertexShader* m_pVertexShader = nullptr;		// 頂点シェーダー入れ物
	ID3D11PixelShader* m_pPixelShader = nullptr;		// ピクセルシェーダー入れ物
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// 頂点フォーマット定義

	ID3D11ShaderResourceView* m_texSRV = nullptr;			// テクスチャＳＲＶ

	unsigned int	m_AnimFileIdx = 0;

public:

	ModelData				m_assimpfile;					// assimpfile
	//各シェーダー作成
	bool Init(const char* filename, const char* vsfile, const char* psfile, std::string texfolder);
	//シェーダー解放
	void Uninit();
	//頂点更新
	void Update(
		int m_Frame, int m_preFrame, float m_factor, int animecnt,
		const DirectX::XMFLOAT4X4& mtxworld);
	void Update2(
	 int animecnt,
		const DirectX::XMFLOAT4X4& mtxworld);
	void Draw(DirectX::XMFLOAT4X4& mtxworld);
	unsigned int GetAnimationNum() {	// アニメーション総数を取得

		return m_animationcontainer.size();//[m_AnimFileIdx]->GetScene()->mNumAnimations;
	}

	// アニメーションをロードする
	bool LoadAnimation(const char* filename) {
		AnimationDataAssimp* animdata;

		animdata = new AnimationDataAssimp();
		bool sts = animdata->Init(filename);
		if (sts) {
			m_animationcontainer.push_back(animdata);
			return true;
		}
		else {
			MessageBox(nullptr, "Load Animation error", "error", MB_OK);
			return false;
		}
	}

	//モデルのデータ取得
	const ModelData& GetModelData() {
		return m_assimpfile;
	}

	//ギズモ描画
	void DrawOBB() {
		m_assimpfile.DrawOBB();
	}

	
	const ModelData& GetModelData() const {
		return m_assimpfile;
	}

	
	void GetOBBList(std::vector<COBB*>& obblist) {

		// メッシュデータ取得
		const std::vector<Mesh>& meshes = m_assimpfile.GetMeshes();

		// OBB全件取得
		for (int i = 0; i < meshes.size(); i++) {
			const Mesh& m = meshes[i];
			for (auto data : m.m_obbvectorcontainer) {
				obblist.push_back(data);
			}
		}
	}
};