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

	//行列の初期化
	DX11MtxIdentity(m_mtx);
	m_life = 0;
	//cpu_time = clock();
	//sec = (double)cpu_time / CLOCKS_PER_SEC;*/
	m_sts = BULLETSTATUS::DEAD;

	XMFLOAT4X4 s_mtx;//スケール

	SetScale(1.1f, 1.1f, 1.1f);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);//スケール行列
	//DX11MtxIdentity(m_mtx);
	DX11MtxMultiply(m_mtx, m_mtx, s_mtx);//スケール
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

	//モデル描画
	if (m_sts == BULLETSTATUS::LIVE) {
	
		m_pmodel->Draw(m_mtx);
	}
}
//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f
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

		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

	

		scale._11 = 2.2f;
		scale._22 = 2.2f;
		scale._33 = 2.2f;

		m_life--;
		explocnt -= 1;

		// debuglog(asec - sec);

		//SetScale(0.1f, 0.1f, 0.1f);
		if (m_life > 0) {
			//発射方向に向けてスピード分　等速運動

			float time = m_life / 60.0f;

			time = abs(1 - time);
			float posx = LeapID<float>(nowpos.x, enemypos.x, time);
			float posy = LeapID<float>(nowpos.y, enemypos.y, time);
			float posz = LeapID<float>(nowpos.z, enemypos.z, time);

			

			trans._41 = posx;
			trans._42 = posy + 4.0f;
			trans._43 = posz;

			XMFLOAT2 angley;
			angley.x = enemypos.x - nowpos.x;
			angley.y = enemypos.z - nowpos.z;

			angle.y = 0.0f;

			angle.y = -GetKakudo(angley.x, angley.y);
			angle.y -= 90.0f;

			float ang = angle.y;

			XMFLOAT4 qty = {};//クォータニオン
	
			XMFLOAT4 axisY;//Y軸
	

			//X軸を取り出す
			axisY.x = m_mtx._21;
			axisY.y = m_mtx._22;
			axisY.z = m_mtx._23;
			axisY.w = 0.0f;

			//DX11GetQtfromMatrix(m_mtx, qt);

			//指定軸回転のクォータニオンを生成
		
			DX11QtRotationAxis(qty, axisY, angle.y);
	

			//クォータニオンをノーマライズ
			DX11QtNormalize(qty, qty);

			SetRotation(qty);

			//クォータニオンから行列を作成
			DX11MtxFromQt(rot, qty);

			DX11MtxMultiply(world, scale, rot);



			world._41 = trans._41;
			world._42 = trans._42;
			world._43 = trans._43;


			m_mtx = world;


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

