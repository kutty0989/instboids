#include "zombiebullet.h"
#include"CModel.h"
#include"player.h"
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

	m_life = 30;
	m_sts = ZOMBIEBSTS::LIVE;
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z =  pos.z;
}

void ZombieBullet::Draw()
{
	if (m_sts == ZOMBIEBSTS::LIVE) {
		m_pmodel->Draw(m_mtx);
	
	}
}

float length = 100;

void ZombieBullet::Update(std::vector<Player*> playervec)
{
	if (m_sts == ZOMBIEBSTS::LIVE) {

		for (int i = 0; i < playervec.size(); i++)
		{
			float disx = this->GetMtx()._41 - playervec.at(i)->location.x;
			float disy = this->GetMtx()._43 - playervec.at(i)->location.y;
			float dist = disx * disx + disy * disy;
			if (length > dist)
			{
				m_sts = ZOMBIEBSTS::DEAD;
				playervec.at(i)->m_sts = Player::STATUS::DEAD;
				playervec.at(i)->hp = 0;
			}
		}



		m_life--;

		m_pos.x += m_direction.x * m_bulletspeed;
		m_pos.y += m_direction.y * m_bulletspeed;
		m_pos.z += m_direction.z * m_bulletspeed;
	}
	else
	{
		m_pos.x = 10000;
		
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
