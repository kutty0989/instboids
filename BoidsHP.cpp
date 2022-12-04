#include "BoidsHp.h"
#include"CBillboardMgr.h"
#include"Scean.h"
#include"PlayerMgr.h"
#include"Application.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"
#include"CCamera.h"


void BoidsHp::Init()
{
	XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };
	

	m_bill = new CBillBoard();
	BoidsHp::SetTexture(CBillBoardMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_btexlist[static_cast<int>(Scean::BCGID::HPBER)].cgname));
	m_bill->Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 50.0f, 50.0f, firecol);

	//m_bill->LoadTexTure("assets/UI/circle.png");
	XMFLOAT2 fireUV[] =
	{
		{0,0},
		{0,1},
		{1,0},
		{1,1}
	};
	m_bill->PartMax(4,4);
	m_bill->SetUV(fireUV);
	m_bill->SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);
	m_bill->SetScale(1.0f,1.0f,1.0f);
	m_bill->angle = 90.0f;
}

void BoidsHp::Update(XMFLOAT3 pos)
{
	m_bill->SetPosiotion(pos.x,pos.y, pos.z +25.0f);

}

void BoidsHp::Draw()
{
	//m_texture->Draw();
	m_bill->DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
}

void BoidsHp::Finish()
{


}
