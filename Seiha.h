#pragma once
#include"Scean.h"


//=============================================================================
//
// �Q�[���V�[������ [Seiha.h]
//
//=============================================================================
class Seiha :public Scean
{
public:
	void Initialize();//���f������x�����ǂݍ���
	void Reset();//�����̏�����
	void Release();//���f���̉������
	void Update(uint64_t dt);//�J�����⃂�f���A������ύX
	void Draw();//�v���C���[��n�ʂ�`��
	bool IsAbleChangeScean();//�V�[���J�ڏ����֐�

	
};