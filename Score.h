#pragma once
//=============================================================================
//
// �X�R�A���� [Score.h]
//
//=============================================================================
#include"CTex.h"


class Score {
private:

	int b_num = 0;//BoidsAI����n���ꂽ�X�R�A���i�[�p
	XMFLOAT3 mypos;//���݂̏ꏊ
	XMFLOAT3 bpos;//�A�j���[�V�����p�̏ꏊ

	XMFLOAT3 bscale;//�A�j���[�V�����p�̏ꏊ
	XMFLOAT3 myscale = {1.0f,1.0f,1.0f};//�����l

	bool rotate = false;//�񌅈ȏ��]
	int angle = 0;//�p�x
	CTex* m_texture;//�e�N�X�`��

	bool mIsInstancing = true;
public:
	int drawnum;//�`��̌���

	XMFLOAT2 mousepos;

	//����������
	void Init(XMFLOAT3 pos);

	//�X�R�A�X�V����
	void Update(int num,int kurai);

	//�X�R�A�`�揈��
	void Draw();

	//�X�R�A�I������
	void Finish();


	static Score* GetInstance()
	{
		static Score instance;
		return &instance;
	}



private:

	//�e�N�X�`�����Z�b�g
	void SetTexture(CTex* tex)
	{
		m_texture = tex;
	}
};


