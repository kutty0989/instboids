//=============================================================================
//
// ”š’e¶¬ƒNƒ‰ƒX [granate.cpp]
//
//=============================================================================
#include "Granate.h"
#include"CBillboardMgr.h"
#include"Scean.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"
#include"CCamera.h"
#include"bullet.h"

void Granate::Init()
{
	XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };


	m_bill = new CBillBoard();
	SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::EXPLSION)].cgname));
	m_bill->Init(0, 0, 0, 300.0f, 300.0f, firecol);
	m_bill->angle = -90.0f;
	//m_bill->LoadTexTure("assets/UI/circle.png");
	//XMFLOAT2 fireUV[] =
	//{
	//	{0,0},
	//	{0,1},
	//	{1,0},
	//	{1,1}
	//};
	m_bill->PartMax(5, 4);
	//m_bill->SetUV(fireUV);
	
}
//
void Granate::Create(XMFLOAT3 pos)
{
	b_sts = Granate_Sts::LIVE;
	m_bill->SetPosiotion(pos.x, pos.y, pos.z);
	m_pos = pos;
	effectcnt = 0;
	part = { 0,0 };
}

void Granate::Update()
{

	//m_bill->SetPosiotion(pos.x, pos.y, pos.z);
	if (b_sts == Granate_Sts::LIVE)
	{

		m_bill->Part(part.x, part.y);
		
		effectcnt++;
		if (effectcnt%3 == 0)
		{
			part.x++;
			
		}
		if (part.x == m_bill->PMaxX-1)
		{
			part.x = 0;
			part.y++;
		}
		if (part.y == m_bill->PMaxY)
		{
			b_sts = Granate_Sts::DEAD;
		}

	}
}

void Granate::Draw()
{
	//m_texture->Draw();
	m_bill->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
}

void Granate::Finish()
{
	m_bill->Dispose();

}
