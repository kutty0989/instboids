#pragma once
#include<DirectXMath.h>
#include<vector>
#include<memory>
#include"gameobject.h"

//�O���錾
class CModel;

//�e�X�e�[�^�X
enum class BULLETSTATUS {
	LIVE,
	DEAD
};

class Bullet :public GameObject {
private:
	
	CModel* m_pmodel;//�RD���f��
	DirectX::XMFLOAT3 m_direction;//���˕���
	DirectX::XMFLOAT3 m_pos;
	float m_speed = 2.0f;

	DirectX::XMFLOAT3 m_scale;

	XMFLOAT3 enemypos;
	
	bool goalpoint = false;
	
public:
	XMFLOAT3 nowpos;
	bool explosion = false;
	BULLETSTATUS  m_sts;//�X�e�[�^�X
	float m_life = 0;
	float explocnt = 0;

	bool Init();

	void Remake(XMFLOAT3 pos);

	void Draw();

	void Update();

	void Finalize(){};

	void SetModel(CModel* p) {
		m_pmodel = p;
	}
	CModel* GetModel() {
		return m_pmodel;
	}

	void SetDirection(DirectX::XMFLOAT4X4 mtx) {
		m_mtx = mtx;
		m_direction = DirectX::XMFLOAT3(mtx._31, mtx._32, mtx._33);
	}

	bool isLive() {
		if (m_sts == BULLETSTATUS::LIVE) {
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