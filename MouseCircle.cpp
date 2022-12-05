#include "MouseCircle.h"
#include"CTexMgr.h"
#include"Scean.h"
#include"PlayerMgr.h"
#include"Application.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"

void MouseCircle::Init()
{
	m_texture = new DXManager();
	m_texture->LoadTexture("assets/UI/glow.jpg");
	//m_model = new InstanceModel();
	//m_model->Init("assets/f1/f1.x", "assets/f1/");
	//
	//m_texture->Init(50,50, XMFLOAT3(1.0f, 1.0f, 1.0f));
	////ロングノーツの先頭テクスチャをセット
	//m_texture->SetScale(1.0, 1.0, 1.0f);
}

void MouseCircle::Update()
{
	mousepos.x = CDirectInput::GetInstance().GetMousePosX();
	mousepos.y = CDirectInput::GetInstance().GetMousePosY();
	mousepos.x -= Application::CLIENT_WIDTH / 2 * 1.0f;
	mousepos.y -= Application::CLIENT_HEIGHT / 2 * 1.0f;
	mousepos.x = mousepos.x / Application::CLIENT_WIDTH;
	mousepos.y = mousepos.y / Application::CLIENT_HEIGHT;

	//m_texture->Update();
}

void MouseCircle::Draw()
{
	
	/*if (CDirectInput::GetInstance().GetMouseLButtonCheck())
	{
		m_texture->SetPosition(mousepos.x*2.0f, mousepos.y*2.0f, 1.0f);
		
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_SPACE))
	{
		mIsInstancing ^= 1;
	}*/

	//if (mIsInstancing) 
	//m_model->RenderInstancing();
	m_texture->RenderInstancing();
}

void MouseCircle::Finish()
{
	//m_texture->UnInit();
	delete m_texture;

}
