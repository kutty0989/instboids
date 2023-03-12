#pragma once
//=============================================================================
//
// バレットマネージャー [BulletMgr.h]
//
//=============================================================================

#include"bullet.h"

class BulletMgr
{
public:

	void Init();//バレットの生成まとめ

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);//新しく弾を作り直す

	void Update();//場所を更新

	void Draw();//描画

	void Finalize();//終了処理


	static BulletMgr* GetInstance()
	{
		static BulletMgr instance;
		return &instance;
	}


	void BulletCreate();//バレットの生成

	std::list<std::unique_ptr<Bullet>> g_bullets;//弾の配列

private:


};