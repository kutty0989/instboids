//========================================================
//AnimationDataAssimp.cpp
//			�A�V���v���̃A�j���[�V�������s���N���X
//========================================================
#include	<windows.h>
#include	"AnimationDataAssimp.h"

/// <summary>
/// �A�V���v�ǂݍ���
/// </summary>
/// <param name="filename">�t�@�C����</param>
/// <returns>����</returns>
bool AnimationDataAssimp::Init(std::string filename) {

	bool sts = m_assimpscene.Init(filename);
	if (!sts) {
		MessageBox(nullptr, "SkinAnimationDataAssimp load error", "error", MB_OK);
	}

	return true;
}

/// <summary>
/// �I������
/// </summary>
void AnimationDataAssimp::Exit() {
	m_assimpscene.Exit();
}