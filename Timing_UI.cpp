#include"Timing_UI.h"
#include<memory>
#include"CTexMgr.h"
#include"Scean.h"
#include"Application.h"
void Timing_UI::Init()
{
	//m_texture = new CTex();
	//Timing_UI::SetTexture(CTexMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_texlist[static_cast<int>(Scean::CGID::NOTES_FRAME)].cgname));
	//m_texture->Init(Application::CLIENT_WIDTH*0.5f, Application::CLIENT_HEIGHT*0.5f, XMFLOAT3(1.0f, 1.0f, 1.0f));
	////ロングノーツの先頭テクスチャをセット
	//m_texture->SetPosition(0.0f, 0.85f, 0.0f);
	//m_texture->SetScale(2.0f, 1.0f, 1.0f);
}

void Timing_UI::Update()
{

}

void Timing_UI::Draw()
{
//	m_texture->Draw();
}

void Timing_UI::Finish()
{
	//m_texture->UnInit();
    //delete m_texture;

}
