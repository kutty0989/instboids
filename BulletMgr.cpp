#include"BulletMgr.h"
#include"ModelMgr.h"
#include"Scean.h"


void BulletMgr::Init()
{
	for (int i = 0; i < 10; i++)
	{
		BulletCreate();
		i++;
	}

}

void BulletMgr::Remake(DirectX::XMFLOAT4X4 mtx,XMFLOAT3 pos)
{
	auto it = g_bullets.begin();
	while (it != g_bullets.end()) {

		if ((*it)->isLive() == false) {
			//初期位置セット
			(*it)->SetInitialPos(mtx._41, mtx._42, mtx._43);
			//発射方向をセット
			(*it)->SetDirection(mtx);
			(*it)->Remake(pos);
			break;
		}
		else ++it;
	}

}


void BulletMgr::Update()
{
	//全弾更新
	for (auto& b : g_bullets) {
		b->Update();
	}

	////全弾更新
	//for (auto& b : g_zombiebullets) {
	//	b->Update();
	//}
	////死んでいる弾削除
	//auto it = g_bullets.begin();
	//while (it != g_bullets.end()) {

	//	if ((*it)->isLive() == false) {
	//		it = g_bullets.erase(it);
	//	}
	//	else ++it;
	//}
}

void BulletMgr::Draw()
{
	//全弾描画
	for (auto& b : g_bullets) {
		b->Draw();
	}
	//for (auto& b : g_zombiebullets) {
	//	b->Draw();
	//}
}

void BulletMgr::Finalize()
{
	for (auto& b : g_bullets) {
		b->Finalize();
	}
	//for (auto& b : g_zombiebullets) {
	//	b->Finalize();
	//}
}

void BulletMgr::BulletCreate()
{
	std::unique_ptr<Bullet> p;
	p = std::make_unique<Bullet>();
	//弾の初期化
	p->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::MISSILE)].modelname));
	p->Init();
	
	//最後尾に球を追加
	//ベクターコンテナにユニークポインタをセット
	g_bullets.emplace_back(std::move(p));
}

