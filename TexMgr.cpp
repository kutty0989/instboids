#include "TexMgr.h"
#include"ModelMgr.h"
#include"Scean.h"
#include"CTexMgr.h"
#include"PlayerMgr.h"

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



void TexMgr::Update()
{
	int aa = PlayerMgr::GetInstance()->ScoreNum;
	g_scorevector.at(0)->drawnum = aa * 0.0001;
	g_scorevector.at(1)->drawnum = aa * 0.001 - g_scorevector.at(0)->drawnum*10;
	g_scorevector.at(2)->drawnum = aa * 0.01- g_scorevector.at(0)->drawnum*100 - g_scorevector.at(1)->drawnum*10;
	g_scorevector.at(3)->drawnum = aa * 0.1 - g_scorevector.at(0)->drawnum*1000 - g_scorevector.at(1)->drawnum*100 - g_scorevector.at(2)->drawnum*10;
	g_scorevector.at(4)->drawnum = aa - g_scorevector.at(0)->drawnum*10000 - g_scorevector.at(1)->drawnum*1000 - g_scorevector.at(2)->drawnum*100 - g_scorevector.at(3)->drawnum*10;
	//�S�e�X�V
	for (auto& b : g_scorevector) {
		
			b->Update(b->drawnum);
		
	}
	

}

void TexMgr::Draw()
{
	//�S�e�`��
	for (auto& b : g_scorevector) {
			b->Draw();	
	}
}

void TexMgr::Finalize()
{
	for (auto& b : g_scorevector) {
		b->Finish();
	}

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