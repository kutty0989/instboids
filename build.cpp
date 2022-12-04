#include"Build.h"
#include"dx11mathutil.h"
#include"XIController.h"
#include"PlayerMgr.h"

#define debuglog(a) std::cout<<a<<std::endl;


bool Build::Init()
{
	return false;
}

bool Build::Init(XMFLOAT3 pos) {
	bool sts = true;
	//s—ñ‚Ì‰Šú‰»
	DX11MtxIdentity(m_mtx);
	m_scale.x = 2.0f;
	m_scale.y = 2.0f;
	m_scale.z = 2.0f;

	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z = pos.z;

	return sts;
}

void Build::Draw() {
	//ƒ‚ƒfƒ‹•`‰æ
	m_pmodel->Draw(m_mtx);	

}
void Build::Update(std::shared_ptr<Player>& ImPlayer, std::vector<shared_ptr<Player>>& in_player_vector)
{
	XMFLOAT3 ppos = ImPlayer->GetPos();

	dx = ppos.x - m_pos.x;
	dy = ppos.y - m_pos.y;

	if (nier * nier > dx * dx + dy * dy)
	{
		int psize = in_player_vector.size();

		if (PlayerMgr::GetInstance()->buildlv_flg)
		{
			buildup_cnt -= psize;
			PlayerMgr::GetInstance()->buildlv_flg = false;
		}
	}
	if (buildup_cnt < 0)
	{
		m_scale.x *= 3.0f;
		m_scale.y *= 3.0f;
		m_scale.z *= 3.0f;
		buildlevel += 10;
		buildup_cnt = buildlevel * 1000;
	}



	/*m_mtx._11 = m_scale.x;
	m_mtx._22 = m_scale.y;
	m_mtx._33 = m_scale.z;*/
	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;
}

bool Build::CreateBuildBoids()
{

	createcnt += buildlevel;

	if (createcnt > 400)
	{
		createcnt = 0;
	}
	if (createcnt == 0)
	{
		return true;
	}
	return false;
}

void Build::Finalize()
{
	m_pmodel->Uninit();
}


