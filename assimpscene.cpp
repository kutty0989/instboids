//========================================================
//assimpscene.cpp
//			アシンプの読み込みのためのクラス
//========================================================
#include	<assimp/cimport.h>
#include	<assimp\postprocess.h>
#include	<assimp/cimport.h>
#include	<assimp\scene.h>
#include	"Assimpscene.h"

/// <summary>
/// アシンプの初期化
/// </summary>
/// <param name="filename">モデルのファイル名</param>
/// <returns></returns>
bool AssimpScene::Init(std::string filename) {

	m_Scene = aiImportFile(filename.c_str(),
		aiProcess_ConvertToLeftHanded |
		aiProcessPreset_TargetRealtime_MaxQuality);

	if (m_Scene == nullptr) {
		return false;
	}

	CreateBoneIndexMap(m_Scene->mRootNode);

	return true;
}

/// <summary>
/// 終了処理
/// </summary>
void AssimpScene::Exit() {
	aiReleaseImport(m_Scene);
}

/// <summary>
/// シーン取得
/// </summary>
/// <returns>成否</returns>
const aiScene* AssimpScene::GetScene() const {
	return m_Scene;
}


/// <summary>
/// アニメーションを持っているか
/// </summary>
/// <returns>成否</returns>
bool AssimpScene::HasAnimation() {
	return m_Scene->HasAnimations();
}

/// <summary>
/// アニメーション番号を返す
/// </summary>
/// <returns>アニメーション番号</returns>
unsigned int AssimpScene::GetAnimationsNum() const
{
	return m_Scene->mNumAnimations;
}

/// <summary>
/// ボーンの名前から番号を返す
/// </summary>
/// <param name="name">ボーンの名前</param>
/// <returns></returns>
int AssimpScene::GetBoneIndexByName(std::string name) const
{
	if (this->m_boneIndexMap.find(name) != this->m_boneIndexMap.end())
		return m_boneIndexMap.at(name);

	else
		return -1;
}

/// <summary>
/// ボーンの数
/// </summary>
/// <returns></returns>
unsigned int AssimpScene::GetBoneNum() const
{
	return this->m_boneIndexMap.size();
}

/// <summary>
/// ボーンの挙動を作る
/// </summary>
/// <param name="node"></param>
void AssimpScene::CreateBoneIndexMap(aiNode* node)
{
	if (this->m_boneIndexMap.find(node->mName.C_Str()) != this->m_boneIndexMap.end())
		return;

	int index = this->m_boneIndexMap.size();
	this->m_boneIndexMap.emplace(node->mName.C_Str(), index);

	const unsigned int childCount = node->mNumChildren;
	for (int i = 0; i < childCount; i++)
	{
		aiNode* child = node->mChildren[i];
		CreateBoneIndexMap(child);
	}
}