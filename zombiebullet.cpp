#include "zombiebullet.h"
#include"CModel.h"
bool ZombieBullet::Init()
{
	bool sts = true;

	//行列の初期化
	DX11MtxIdentity(m_mtx);
	m_life = 0;
	//cpu_time = clock();
	//sec = (double)cpu_time / CLOCKS_PER_SEC;*/
	m_sts = ZOMBIEBSTS::DEAD;

	XMFLOAT4X4 s_mtx;//スケール

	SetScale(3.1f, 3.1f, 3.1f);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);//スケール行列
	//DX11MtxIdentity(m_mtx);
	DX11MtxMultiply(m_mtx, m_mtx, s_mtx);//スケール
	return sts;
}

void ZombieBullet::Remake(XMFLOAT3 pos)
{

	m_life = 100;
	m_sts = ZOMBIEBSTS::LIVE;
	m_mtx._41 = pos.x;
	m_mtx._42 = pos.y;
	m_mtx._43 = pos.z;
}

void ZombieBullet::Draw()
{
	if (m_sts == ZOMBIEBSTS::LIVE) {
		m_pmodel->Draw(m_mtx);
	
	}
}

void ZombieBullet::Update()
{
	if (m_sts == ZOMBIEBSTS::LIVE) {
		m_life--;

		m_pos.x += m_mtx._31 * m_bulletspeed;
		m_pos.y += m_mtx._32 * m_bulletspeed;
		m_pos.z += m_mtx._33 * m_bulletspeed;
	}
	if (m_life < 0)
	{
		m_sts = ZOMBIEBSTS::DEAD;
	}

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;
}

void ZombieBullet::BillBoardExplosion()
{
}
