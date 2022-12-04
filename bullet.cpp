#include  <memory>
#include  "bullet.h"
#include  "dx11mathutil.h"
#include  "CModel.h"
#include  "CDirectInput.h"
#include  "ModelMgr.h"
#include <time.h>
#include "DX11Settransform.h"
#include<iostream>
#include"CCamera.h"
#include"billboardMgr.h"
constexpr float BULLETSPEED = 15.0f;
constexpr uint32_t BULLETLIFE = 60;
#define debuglog(a) std::cout<<a<<std::endl;
time_t t;
time_t ta;
long cpu_time;
double sec;
double asec;
bool Bullet::Init() {
	bool sts = true;

	//�s��̏�����
	DX11MtxIdentity(m_mtx);
	m_life = 0;
	//cpu_time = clock();
	//sec = (double)cpu_time / CLOCKS_PER_SEC;*/
	m_sts = BULLETSTATUS::DEAD;

	XMFLOAT4X4 s_mtx;//�X�P�[��

	SetScale(3.1f, 3.1f, 3.1f);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);//�X�P�[���s��
	//DX11MtxIdentity(m_mtx);
	DX11MtxMultiply(m_mtx, m_mtx, s_mtx);//�X�P�[��
	return sts;


}

void Bullet::Remake(XMFLOAT3 pos)
{
	m_life = 60;
	m_sts = BULLETSTATUS::LIVE;
	enemypos = pos;
	nowpos = m_pos;
}

void Bullet::Draw() {
	//���f���`��
	if (m_sts == BULLETSTATUS::LIVE) {
		m_pmodel->Draw(m_mtx);
	}
}
//go ���̍��W�l
//to�@�s��̍��W�l
//ratio�@���݂̐i�s�����@0.0f�`1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

void Bullet::Update()
{
	BillBoardExplosion();
	explosion = false;
	if (m_sts == BULLETSTATUS::LIVE) {
		m_life--;
		explocnt -= 1;

		// debuglog(asec - sec);

		//SetScale(0.1f, 0.1f, 0.1f);
		if (m_life > 0) {
			//���˕����Ɍ����ăX�s�[�h���@�����^��

			float time = m_life / 60.0f;

			time = abs(1 - time);
			float posx = LeapID<float>(nowpos.x, enemypos.x, time);
			float posy = LeapID<float>(nowpos.y, enemypos.y, time);
			float posz = LeapID<float>(nowpos.z, enemypos.z, time);

			m_mtx._41 = posx;
			m_mtx._42 = posy;
			m_mtx._43 = posz;

			m_mtx._11 = m_scale.x;
			m_mtx._22 = m_scale.y;
			m_mtx._33 = m_scale.z;
		}
		if (m_life == 1)
		{
			explocnt = 100;
			goalpoint = true;
		}
		if (goalpoint)
		{
			if (explocnt < 0)
			{
				m_sts = BULLETSTATUS::DEAD;
				goalpoint = false;
				explosion = true;
			}
		}
	}
}

void Bullet::BillBoardExplosion()
{
	if (explosion)
	{
		CCamera::GetInstance()->blowflg = true;
		BillBoardMgr::GetInstance()->GranateCreate(XMFLOAT3(m_mtx._41,m_mtx._42,m_mtx._43));
		
	}
}

