//=============================================================================
//
// �]���r�̒e�̐����N���X [zombiebulet.cpp]
//
//=============================================================================

#include "zombiebullet.h"
#include"CModel.h"
#include"BoidsAI.h"
#include"BoidsAIMgr.h"
bool ZombieBullet::Init()
{
	bool sts = true;

	//�s��̏�����
	DX11MtxIdentity(m_mtx);
	m_life = 0;
	//cpu_time = clock();
	//sec = (double)cpu_time / CLOCKS_PER_SEC;*/
	m_sts = ZOMBIEBSTS::DEAD;

	XMFLOAT4X4 s_mtx;//�X�P�[��

	SetScale(3.1f, 3.1f, 3.1f);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);//�X�P�[���s��
	//DX11MtxIdentity(m_mtx);
	DX11MtxMultiply(m_mtx, m_mtx, s_mtx);//�X�P�[��
	return sts;
}

void ZombieBullet::Remake(XMFLOAT3 pos,XMFLOAT3 div)
{

	m_life = 30;
	m_sts = ZOMBIEBSTS::LIVE;
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z =  pos.z;

	m_mtx._31 = div.x;
	m_mtx._32 = div.y;
	m_mtx._33 = div.z;
}

void ZombieBullet::Draw()
{
	if (m_sts == ZOMBIEBSTS::LIVE) {
		m_pmodel->Draw(m_mtx);
	
	}
}



void ZombieBullet::Update(std::vector<BoidsAI*> BoidsAIvec)
{
	if (m_sts == ZOMBIEBSTS::LIVE) {

	/*	for (int i = 0; i < BoidsAIvec.size(); i++)
		{
			float disx = this->GetMtx()._41 - BoidsAIvec.at(i)->location.x;
			float disy = this->GetMtx()._43 - BoidsAIvec.at(i)->location.y;
			float dist = disx * disx + disy * disy;
			if (length > dist)
			{
				m_sts = ZOMBIEBSTS::DEAD;
				BoidsAIvec.at(i)->m_sts = BoidsAI::STATUS::DEAD;
				BoidsAIvec.at(i)->hp = 0;
			}
		}*/



		m_life--;

		m_pos.x -= m_mtx._31 * m_bulletspeed;
		m_pos.y -= m_mtx._32 * m_bulletspeed;
		m_pos.z -= m_mtx._33 * m_bulletspeed;

		if (m_pos.x < -BoidsAIMgr::GetInstance()->window_width * 0.5f)
		{
			m_pos.y = -1000;
			m_pos.x = 0;
			m_life = 0;
		}
		if (m_pos.z < -BoidsAIMgr::GetInstance()->window_width * 0.5f)
		{
			m_pos.y = -1000;
			m_life = 0;
			m_pos.z = 0;
		}
		if (m_pos.x > BoidsAIMgr::GetInstance()->window_height * 0.5f)
		{
			m_pos.y = -1000;
			m_life = 0;
			m_pos.x = 0;
		}
		if (m_pos.z > BoidsAIMgr::GetInstance()->window_height * 0.5f)
		{
			m_pos.y = -1000;
			m_pos.z = 0;
			m_life = 0;
		}
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
