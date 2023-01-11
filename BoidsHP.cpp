#include "BoidsHp.h"
#include"CBillboardMgr.h"
#include"Scean.h"
#include"PlayerMgr.h"
#include"Application.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"
#include"CCamera.h"
#include"CTexInstance.h"

//
//CTexInstance ctexinstance_hpin;
//CTexInstance ctexinstance_hpout;

static XMFLOAT4X4 hpinmat[ZOMBIEMAX];

void BoidsHp::Init()
{
	int num = ZOMBIEMAX;
	m_texture = new CTexInstance(num);
	m_texture->LoadTexture("assets/UI/hpkara.png");
	//ctexinstance_hpin.Init(ZOMBIEMAX, "assets/UI/kusa.jpg");


	//XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };
	//
	//hpout = new CBillBoard();
	//BoidsHp::Sethpout(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPOUT)].cgname));
	//hpout->Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	////hpout->LoadTexTure("assets/UI/circle.png");
	//XMFLOAT2 fireUV[] =
	//{
	//	{0,1},
	//	{0,0},
	//	{1,1},
	//	{1,0}
	//};
	//XMFLOAT2 inUV[] =
	//{
	//	{1,1},
	//	{0,1},
	//	{1,0},
	//	{0,0}
	//};
	////hpout->PartMax(4,4);
	//hpout->SetUV(fireUV);
	//hpout->SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);
	//hpout->SetScale(1.0f, 1.0f, 1.0f);
	//hpout->angle = 90.0f;

	//hpin = new CBillBoard();
	//BoidsHp::Sethpin(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPIN)].cgname));
	//hpin->Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	////hpin->LoadTexTure("assets/UI/circle.png");

	//hpin->PartMax(2,3);
	//hpin->SetUV(inUV);
	//hpin->SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);
	//hpin->SetScale(1.0f, 1.0f, 1.0f);
	//hpin->angle = 90.0f;


	//hpout = new CBillBoard();
	//BoidsHp::SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPBER)].cgname));
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

void BoidsHp::Update(XMFLOAT4X4 zpos[])
{
	for (int i = 0; i < ZOMBIEMAX; i++)
	{
		hpinmat[i] = zpos[i];
	}
	
	//ctexinstance_hpin.Update(pos);
//	m_texture->Update(zpos);

	/*hpout->SetPosiotion(pos.x,pos.y, pos.z +25.0f);
	hpin->SetPosiotion(pos.x,pos.y, pos.z +25.f);*/

}

void BoidsHp::UpdateHp(int hp)
{
	XMFLOAT2 inUV[] =
	{
		{1,1},
		{0,1},
		{1,0},
		{0,0}
	};

	XMFLOAT3 col = { 1.0f,1.0f,1.0f};
	m_texture->Update(col, inUV);
	//switch (hp)
	//{
	//case 5:
	//{
	//	hpin->Part(0, 2);
	//	break;
	//}
	//case 4:
	//{
	//	hpin->Part(1, 2);
	//	break;
	//}
	//case 3:
	//{
	//	hpin->Part(0, 1);
	//	break;
	//}
	//case 2:
	//{
	//	hpin->Part(1, 1);
	//	break;
	//case 1:
	//{
	//	hpin->Part(0, 0);
	//	break;
	//}
	//case 0:
	//{
	//	hpin->Part(1, 0);
	//	break;

	//}
	//}
	//default:
	//	break;
	//}
}

void BoidsHp::Draw()
{
	m_texture->RenderInstancing(hpinmat);
//	ctexinstance_hpin.RenderInstancing();
//	m_texture->Draw();
	//hpout->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
//	//hpin->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
	
}




void BoidsHp::Finish()
{


}
