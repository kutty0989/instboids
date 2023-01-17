#include "UniqueBombHp.h"
#include"CBillboardMgr.h"
#include"Scean.h"
#include"PlayerMgr.h"
#include"Application.h"
#include"IMgui/imgui.h"
#include"CCamera.h"

//
//CTexInstance ctexinstance_hpin;
//CTexInstance ctexinstance_hpout;

//static XMFLOAT4X4 hpinmat[ZOMBIEMAX];

void UniqueBombHp::Init()
{


	XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };
	//
	hpout = new CBillBoard();
	UniqueBombHp::Sethpout(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPUBOUT)].cgname));
	hpout->Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	XMFLOAT2 fireUV[] =
	{
		{0,1},
		{0,0},
		{1,1},
		{1,0}
	};


	hpout->SetUV(fireUV);
	hpout->SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);
	hpout->SetScale(1.3f, 1.3f, 1.0f);
	hpout->angle = 90.0f;


	XMFLOAT2 inUV[] =
	{
		{1,1},
		{0,1},
		{1,0},
		{0,0}
	};
	hpin = new CBillBoard();
	UniqueBombHp::Sethpin(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPUBIN)].cgname));
	hpin->Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	//hpin->LoadTexTure("assets/UI/circle.png");

	hpin->SetUV(inUV);
	hpin->SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);
	hpin->SetScale(0.1f, 1.62f, 1.5f);
	hpin->angle = 90.0f;


	//hpout = new CBillBoard();
	//UniqueBombHp::SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPBER)].cgname));
	//hpout->Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	////hpout->LoadTexTure("assets/UI/circle.png");
	//XMFLOAT2 fireUV[] =
	//{
	//	{0,0},
	//	{0,1},
	//	{1,0},
	//	{1,1}
	//};
	////hpout->PartMax(4,4);
	//hpout->SetUV(fireUV);
	//hpout->SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);
	//hpout->SetScale(1.0f,1.0f,1.0f);
	//hpout->angle = 90.0f;
}

void UniqueBombHp::Update(XMFLOAT3 pos, float hp)
{
	posision = pos;

	hpout->SetPosiotion(pos.x, pos.y, pos.z + 25.0f);
	//hpin->SetPosiotion(pos.x + 8.2f, pos.y, pos.z + 28.0f);

	float hpy = 1.62 * hp;

	hpin->SetScale(0.1f, hpy, 1.5f);
	hpin->SetPosiotion(posision.x-12.0f , posision.y, posision.z + 28.0f);

}

void UniqueBombHp::UpdateHp(float hp)
{
}

void UniqueBombHp::Draw()
{

	hpout->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
	hpin->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());

}




void UniqueBombHp::Finish()
{


}
