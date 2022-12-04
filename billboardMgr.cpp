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
	//全弾更新
	for (auto& b : g_granatelist) {
		if (b->isLive())
		{
			b->Update();
		}
	}


}

void BillBoardMgr::Draw()
{
	//全弾描画
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
	//弾の初期化
//	p->SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::EXPLSION)].cgname));
	p->Init();

	//最後尾に球を追加
	//ベクターコンテナにユニークポインタをセット
	g_granatelist.emplace_back(std::move(p));
}
