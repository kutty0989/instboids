#pragma once
#include"bullet.h"
#include<list>
#include<DirectXMath.h>
#include"zombiebullet.h"
class BulletMgr
{
public:

	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx,XMFLOAT3 pos);
	void zombiebulletRemake(DirectX::XMFLOAT4X4 mtx,XMFLOAT3 pos);

	void Update();

	void Draw();

	void Finalize();


	static BulletMgr* GetInstance()
	{
		static BulletMgr instance;
		return &instance;
	}


	void BulletCreate();
	void ZombbieBulletCreate();

	std::list <std::unique_ptr<Bullet>> g_bullets;//’e‚Ì”z—ñ
	std::vector <std::unique_ptr<ZombieBullet>> g_zombiebullets;//’e‚Ì”z—ñ
private:

	
};
