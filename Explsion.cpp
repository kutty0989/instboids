//=============================================================================
//
// ”š’e¶¬ƒNƒ‰ƒX [Explsion.cpp]
//
//=============================================================================

#include "Explsion.h"
#include"CBillboardMgr.h"
#include"Scean.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"
#include"CCamera.h"
#include"bullet.h"

void Explsion::Init()
{
	XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };


	m_bill = new CBillBoard();
	SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::EXPLSION)].cgname));
	m_bill->Init(0, 0, 0, 300.0f, 300.0f, firecol);
	m_bill->angle = -90.0f;

	m_bill->PartMax(5, 4);
	//m_bill->SetUV(fireUV);

}
//
void Explsion::Create(XMFLOAT3 pos)
{
	b_sts = Explsion_Sts::LIVE;
	m_bill->SetPosiotion(pos.x, pos.y, pos.z);
	m_pos = pos;
	effectcnt = 0;
	part = { 0,0 };
}

void Explsion::Update()
{

	//m_bill->SetPosiotion(pos.x, pos.y, pos.z);
	if (b_sts == Explsion_Sts::LIVE)
	{


		m_bill->Part(part.x, part.y);

		effectcnt++;
		if (effectcnt % 3 == 0)
		{
			part.x++;

		}
		if (part.x == m_bill->PMaxX - 1)
		{
			part.x = 0;
			part.y++;
		}
		if ((part.y == m_bill->PMaxY - 1) && (part.x == m_bill->PMaxX - 2))
		{
			b_sts = Explsion_Sts::DEAD;

		}
		m_bill->SetPosiotion(m_pos.x,m_pos.y,m_pos.z);
		
	}
	else
	{
		m_bill->SetPosiotion(0,-1000,0);
		part = { 0,0 };
	}

	
}

void Explsion::Draw()
{
	//m_texture->Draw();
	m_bill->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
}

void Explsion::Finish()
{
	m_bill->Dispose();

}
