#pragma once
#include"bullet.h"
#include<list>
#include<DirectXMath.h>

class BulletMgr
{
public:

	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx,XMFLOAT3 pos);

	void Update();

	void Draw();

	void Finalize();


	static BulletMgr* GetInstance()
	{
		static BulletMgr instance;
		return &instance;
	}


	void BulletCreate();

	std::list <std::unique_ptr<Bullet>> g_bullets;//’e‚Ì”z—ñ
private:

	
};
