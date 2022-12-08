#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <assimp\scene.h>
#include <map>
#include <assimp\Importer.hpp>
#include "dx11mathutil.h"
#include "Mesh.h"
#include "CDirectxGraphics.h"
#include "animationdataassimp.h"



class ModelData
{
public:
	bool animationreset = false;


	ModelData();
	~ModelData();

	// コピー禁止
	ModelData(const ModelData&) = delete;
	ModelData& operator=(const ModelData&) = delete;

	// ムーブ禁止
	ModelData(ModelData&&) = delete;
	ModelData& operator=(ModelData&&) = delete;

	bool Load(std::string resourcefolder, std::string filename);

	void Draw(ID3D11DeviceContext* devcon, DirectX::XMFLOAT4X4& mtxworld);
	void Drawinstance(ID3D11DeviceContext* devcon);
	
	void Update(int m_Frame, int m_preFrame, float m_factor, int animecnt,
		const XMFLOAT4X4& mtxworld,
		unsigned int animfileno,
		std::vector<AnimationDataAssimp*>& animationcontainer);
	
	void Update2(int animecnt,
		const XMFLOAT4X4& mtxworld,
		unsigned int animfileno,
		std::vector<AnimationDataAssimp*>& animationcontainer);

	void DrawOBB();

	void Exit();

	const std::vector<Mesh>& GetMeshes()const {
		return m_meshes;
	}
	void UpdateOBB(const XMFLOAT4X4& mtxworld);

	void LoadMaterial();						// マテリアルを読み込む
private:


	AssimpScene m_assimpscene;					// assimp scene
	std::vector<Mesh> m_meshes;					// メッシュの集合がモデル
	std::string m_directory;					// テクスチャファイルの位置
	std::vector<Texture> m_texturesloaded;		// 既にロードされているテクスチャ
	std::vector<Material> m_materials;			// マテリアル群

	void processNode(aiNode* node, const aiScene* scene);				// ノードを解析
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, int meshidx);	// メッシュを解析
																																				// マテリアルに対応したテクスチャを取得する
	std::vector<Texture> loadMaterialTextures(
		aiMaterial* mat,
		aiTextureType type,
		std::string typeName,
		const aiScene* scene);


	int m_Frame = 0;								// フレーム番号
	std::vector<const aiScene*> m_sceneAnimContainer;	// アニメーションコンテナ

	int m_cnt = 0;								// キーフレーム補間用
	int m_preFrame = 0;							// キーフレーム補間用
	float m_factor = 0.0f;						// キーフレーム補間用
	std::map<std::string, BONE> m_Bone;			//ボーンデータ（ノードの名前で参照）
	ID3D11Buffer* m_constantbufferbonematrix;	// ボーン行列格納用定数バッファ	
	
	void CreateBone(aiNode* node);			// ボーン生成
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);	// ボーン行列更新
	void UpdateBoneMatrixConstantBuffer();	// ボーン行列を定数バッファに反映させる

};

