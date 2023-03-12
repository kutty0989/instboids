#pragma once
//========================================================
//AnimationDataAssimp.h
//			�A�V���v���̃A�j���[�V�������s���N���X
//========================================================
#include "assimpscene.h"

class AnimationDataAssimp {
private:
	AssimpScene		m_assimpscene;
public:
	//�A�V���v�̓ǂݎq��
	bool Init(std::string filename);
	//�V�[���̎擾
	const aiScene* GetScene() {
		return m_assimpscene.GetScene();
	}
	//�I������
	void Exit();
};