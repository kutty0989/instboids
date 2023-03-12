//========================================================
//assimpscene.cpp
//			�A�V���v�̓ǂݍ��݂̂��߂̃N���X
//========================================================
#include	<assimp/cimport.h>
#include	<assimp\postprocess.h>
#include	<assimp/cimport.h>
#include	<assimp\scene.h>
#include	"Assimpscene.h"

/// <summary>
/// �A�V���v�̏�����
/// </summary>
/// <param name="filename">���f���̃t�@�C����</param>
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
/// �I������
/// </summary>
void AssimpScene::Exit() {
	aiReleaseImport(m_Scene);
}

/// <summary>
/// �V�[���擾
/// </summary>
/// <returns>����</returns>
const aiScene* AssimpScene::GetScene() const {
	return m_Scene;
}


/// <summary>
/// �A�j���[�V�����������Ă��邩
/// </summary>
/// <returns>����</returns>
bool AssimpScene::HasAnimation() {
	return m_Scene->HasAnimations();
}

/// <summary>
/// �A�j���[�V�����ԍ���Ԃ�
/// </summary>
/// <returns>�A�j���[�V�����ԍ�</returns>
unsigned int AssimpScene::GetAnimationsNum() const
{
	return m_Scene->mNumAnimations;
}

/// <summary>
/// �{�[���̖��O����ԍ���Ԃ�
/// </summary>
/// <param name="name">�{�[���̖��O</param>
/// <returns></returns>
int AssimpScene::GetBoneIndexByName(std::string name) const
{
	if (this->m_boneIndexMap.find(name) != this->m_boneIndexMap.end())
		return m_boneIndexMap.at(name);

	else
		return -1;
}

/// <summary>
/// �{�[���̐�
/// </summary>
/// <returns></returns>
unsigned int AssimpScene::GetBoneNum() const
{
	return this->m_boneIndexMap.size();
}

/// <summary>
/// �{�[���̋��������
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