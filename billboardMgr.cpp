#include"BillBoardMgr.h"
#include"ModelMgr.h"
#include"Scean.h"
#include"CBillboardMgr.h"

void BillBoardMgr::Init()
{
	for (int i = 0; i < 10; i++)
	{
		BGranateCreate();
		
	}

	for (int i = 0; i < 15; i++)
	{
		BExplsionCreate();
		
	}
}



void BillBoardMgr::Update()
{
	//�S�e�X�V
	for (auto& b : g_granatelist) {
		if (b->isLive())
		{
			b->Update();
		}
	}
	for (int i = 0; i < g_explsionlist.size(); i++)
	{
		if (g_explsionlist.at(i)->isLive())
		{
			g_explsionlist.at(i)->Update();
		}
	}

}

void BillBoardMgr::Draw()
{
	//�S�e�`��
	for (auto& b : g_granatelist) {
		if (b->isLive())
		{
			b->Draw();
		}
	}
	for (int i = 0; i < g_explsionlist.size(); i++)
	{
		if (g_explsionlist.at(i)->isLive())
		{
			g_explsionlist.at(i)->Update();
			g_explsionlist.at(i)->Draw();
		}
	}
	
}

void BillBoardMgr::Finalize()
{
	for (auto& b : g_granatelist) {
		b->Finish();
	}
	for (auto& b : g_explsionlist) {
		b->Finish();
	}
}

void BillBoardMgr::GranateCreate(XMFLOAT3 pos)
{
	auto it = g_granatelist.begin();
	while (it != g_granatelist.end()) {

		if ((*it)->isLive() == false) {
			(*it)->Create(pos);
			break;
		}
		else ++it;
	}
}

void BillBoardMgr::ExplsionCreate(XMFLOAT3 pos)
{
	auto it = g_explsionlist.begin();
	while (it != g_explsionlist.end()) {

		if ((*it)->isLive() == false) {
			(*it)->Create(pos);
			break;
		}
		else ++it;
	}
}

void BillBoardMgr::BGranateCreate()
{
	std::unique_ptr<Granate> p;
	p = std::make_unique<Granate>();
	//�e�̏�����
//	p->SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::EXPLSION)].cgname));
	p->Init();

	//�Ō���ɋ���ǉ�
	//�x�N�^�[�R���e�i�Ƀ��j�[�N�|�C���^���Z�b�g
	g_granatelist.emplace_back(std::move(p));
}

void BillBoardMgr::BExplsionCreate()
{
	std::unique_ptr<Explsion> p;
	p = std::make_unique<Explsion>();
	p->Init();

	//�Ō���ɋ���ǉ�
	//�x�N�^�[�R���e�i�Ƀ��j�[�N�|�C���^���Z�b�g
	g_explsionlist.emplace_back(std::move(p));
}
