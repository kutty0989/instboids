//=============================================================================
//
// プレイヤーのHPクラス [BombHp.cpp]
//
//=============================================================================

#include "BoidsHp.h"
#include"CBillboardMgr.h"
#include"Scean.h"
#include"BoidsAIMgr.h"
#include"Application.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"
#include"CCamera.h"
#include"CTexInstance.h"


void BoidsHp::Init()
{


	XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };
	//
	hpout = new CBillBoard();
	BoidsHp::Sethpout(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPOUT)].cgname));
	hpout->Init(BoidsAI::GetInstance()->GetPos().x, 500.0f, BoidsAI::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	XMFLOAT2 fireUV[] =
	{
		{0,1},
		{0,0},
		{1,1},
		{1,0}
	};


	hpout->SetUV(fireUV);
	hpout->SetPosiotion(BoidsAI::GetInstance()->GetPos().x, BoidsAI::GetInstance()->GetPos().y, BoidsAI::GetInstance()->GetPos().z + 30.0f);
	hpout->SetScale(2.0f, 1.5f, 1.5f);
	hpout->angle = 90.0f;


	XMFLOAT2 inUV[] =
	{
		{1,1},
		{0,1},
		{1,0},
		{0,0}
	};
	hpin = new CBillBoard();
	BoidsHp::Sethpin(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPIN)].cgname));
	hpin->Init(BoidsAI::GetInstance()->GetPos().x, 500.0f, BoidsAI::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	//hpin->LoadTexTure("assets/UI/circle.png");

	hpin->PartMax(2,3);
	hpin->SetUV(inUV);
	hpin->SetPosiotion(BoidsAI::GetInstance()->GetPos().x, BoidsAI::GetInstance()->GetPos().y, BoidsAI::GetInstance()->GetPos().z + 30.0f);
	hpin->SetScale(2.0f, 1.5f, 1.5f);
	hpin->angle = 90.0f;


}

void BoidsHp::Update(XMFLOAT3 pos)
{
	hpout->SetPosiotion(pos.x,pos.y, pos.z +25.0f);
	hpin->SetPosiotion(pos.x,pos.y, pos.z +25.f);

}

void BoidsHp::UpdateHp(int hp)
{
	XMFLOAT2 inUV[] =
	{
		{0,0},
		{1,0},
		{0,1},
		{1,1}
	};

	XMFLOAT3 col = { 1.0f,1.0f,1.0f};
	m_texture->Update(col, inUV);
	switch (hp)
	{
	case 5:
	{
		hpin->Part(0, 2);
		break;
	}
	case 4:
	{
		hpin->Part(1, 2);
		break;
	}
	case 3:
	{
		hpin->Part(0, 1);
		break;
	}
	case 2:
	{
		hpin->Part(1, 1);
		break;
	case 1:
	{
		hpin->Part(0, 0);
		break;
	}
	case 0:
	{
		hpin->Part(1, 0);
		break;

	}
	}
	default:
		break;
	}
}

void BoidsHp::Draw()
{
	//m_texture->RenderInstancing(hpinmat);
//	ctexinstance_hpin.RenderInstancing();
//	m_texture->Draw();
	hpout->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
	hpin->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
	
}




void BoidsHp::Finish()
{


}
