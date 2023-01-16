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
			//�����ʒu�Z�b�g
			(*it)->SetInitialPos(mtx._41, mtx._42, mtx._43);
			//���˕������Z�b�g
			(*it)->SetDirection(mtx);
			(*it)->Remake(pos);
			break;
		}
		else ++it;
	}

}


void BulletMgr::Update()
{
	//�S�e�X�V
	for (auto& b : g_bullets) {
		b->Update();
	}

	////�S�e�X�V
	//for (auto& b : g_zombiebullets) {
	//	b->Update();
	//}
	////����ł���e�폜
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
	//�S�e�`��
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
	//�e�̏�����
	p->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::MISSILE)].modelname));
	p->Init();
	
	//�Ō���ɋ���ǉ�
	//�x�N�^�[�R���e�i�Ƀ��j�[�N�|�C���^���Z�b�g
	g_bullets.emplace_back(std::move(p));
}

