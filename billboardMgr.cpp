#include"BillBoardMgr.h"
#include"ModelMgr.h"
#include"Scean.h"
#include"CBillboardMgr.h"

void BillBoardMgr::Init()
{
	for (int i = 0; i < 10; i++)
	{
		BGranateCreate();
		i++;
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
}

void BillBoardMgr::Finalize()
{
	for (auto& b : g_granatelist) {
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
