//=============================================================================
//
// �e�N�X�`���[�Ǘ��N���X [TexMgr.cpp]
//
//=============================================================================

#include "TexMgr.h"
#include"ModelMgr.h"
#include"Scean.h"
#include"CTexMgr.h"
#include"BoidsAIMgr.h"

/// <summary>
/// /�X�R�A��5������
/// </summary>
void TexMgr::Init()
{
	for (int i = 0; i < 5; i++)
	{
		XMFLOAT3 pos;
		pos.x = -0.8+i*0.05;
		pos.y = -0.8;
		pos.z = 0;
		ScoreCreate(pos);
	}
}



/// <summary>
/// �X�R�A�̈ʂ𒲐�
/// </summary>
void TexMgr::Update()
{
	//�X�R�A������Ă���
	int aa = BoidsAIMgr::GetInstance()->ScoreNum;

	//�i�[���Ă���
	g_scorevector.at(0)->drawnum = aa * 0.0001;
	g_scorevector.at(1)->drawnum = aa * 0.001 - g_scorevector.at(0)->drawnum * 10;
	g_scorevector.at(2)->drawnum = aa * 0.01 - g_scorevector.at(0)->drawnum * 100 - g_scorevector.at(1)->drawnum * 10;
	g_scorevector.at(3)->drawnum = aa * 0.1 - g_scorevector.at(0)->drawnum * 1000 - g_scorevector.at(1)->drawnum * 100 - g_scorevector.at(2)->drawnum * 10;
	g_scorevector.at(4)->drawnum = aa - g_scorevector.at(0)->drawnum * 10000 - g_scorevector.at(1)->drawnum * 1000 - g_scorevector.at(2)->drawnum * 100 - g_scorevector.at(3)->drawnum * 10;

	//����X�V
	for (int i = 0; i < g_scorevector.size(); i++)
	{
		g_scorevector.at(i)->Update(g_scorevector.at(i)->drawnum, i);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void TexMgr::Draw()
{
	//�S�X�R�A�`��
	for (auto& b : g_scorevector) {
			b->Draw();	
	}
}

/// <summary>
/// �I������
/// </summary>
void TexMgr::Finalize()
{
	for (auto& b : g_scorevector) {
		b->Finish();
	}

	//�z����N���A
	g_scorevector.clear();
	g_scorevector.resize(0);
}



void TexMgr::ScoreCreate(XMFLOAT3 pos)
{
	std::unique_ptr<Score> p;
	p = std::make_unique<Score>();
	//�e�̏�����
	p->Init(pos);
	//�Ō���ɋ���ǉ�
	//�x�N�^�[�R���e�i�Ƀ��j�[�N�|�C���^���Z�b�g
	g_scorevector.emplace_back(std::move(p));
}
