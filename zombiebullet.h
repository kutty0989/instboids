#pragma once
#include<DirectXMath.h>
#include<vector>
#include<memory>
#include"gameobject.h"

//前方宣言
class CModel;

//弾ステータス
enum class ZOMBIEBSTS {
	LIVE,
	DEAD
};

class ZombieBullet :public GameObject {
private:

	CModel* m_pmodel;//３Dモデル
	DirectX::XMFLOAT3 m_direction;//発射方向
	DirectX::XMFLOAT3 m_pos;
	float m_speed = 2.0f;
	float m_bulletspeed = 0.5f;

	DirectX::XMFLOAT3 m_scale;


public:
	XMFLOAT3 nowpos;
	bool explosion = false;
	ZOMBIEBSTS m_sts;//ステータス
	float m_life = 0;
	float explocnt = 0;

	bool Init();

	void Remake(XMFLOAT3 pos);

	void Draw();

	void Update();

	void Finalize() {};

	void SetModel(CModel* p) {
		m_pmodel = p;
	}
	CModel* GetModel() {
		return m_pmodel;
	}

	static ZombieBullet* GetInstance()
	{
		static ZombieBullet instance;
		return &instance;
	}

	void SetDirection(DirectX::XMFLOAT4X4 mtx) {
		m_mtx = mtx;
		m_direction = DirectX::XMFLOAT3(mtx._31, mtx._32, mtx._33);
	}

	bool isLive() {
		if (m_sts == ZOMBIEBSTS::LIVE) {
			return true;
		}
		else {
			return false;
		}
	}

	void SetInitialPos(float x, float y, float z)
	{
		m_pos = { x,y,z };
	}
	void SetScale(float x, float y, float z)
	{
		m_scale = { x,y,z };
	}

	void BillBoardExplosion();

};