#include "Score.h"
#include"CTexMgr.h"
#include"Scean.h"
#include"PlayerMgr.h"
#include"Application.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"


void Score::Init(XMFLOAT3 pos)
{
	m_texture = new CTex();
	
	//SetTexture(CTexMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_texlist[static_cast<int>(Scean::CGID::NUM)].cgname));

	m_texture->LoadTexture("assets/UI/suuzi.png");

	m_texture->Init(50, 50, XMFLOAT3(1.0f, 1.0f, 1.0f));
	////ロングノーツの先頭テクスチャをセット
	m_texture->SetScale(1.0, 1.0, 1.0f);
	
	
	m_texture->PartMax(5, 5);
	m_texture->SetPosition(pos.x, pos.y, pos.z);
	
}

void Score::Update(int num)
{
	XMFLOAT2 c_uv[4] =
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};	
	m_texture->SetUV(c_uv);


	switch (num)
	{
	case 0:
	{
		m_texture->Part(0, 0);
		break;
	}
	case 1:
	{
		m_texture->Part(1, 0);
		break;
	}
	case 2:
	{
		m_texture->Part(2, 0);
		break;
	}
	case 3:
	{
		m_texture->Part(3, 0);
		break;
	}
	case 4:
	{
		m_texture->Part(0, 1);
		break;
	}

	case 5:
	{
		m_texture->Part(1, 1);
		break;
	}

	case 6:
	{
		m_texture->Part(2, 1);
		break;
	}
	case 7:
	{
		m_texture->Part(0, 2);
		break;
	}
	case 8:
	{
		m_texture->Part(1, 2);
		break;
	}
	case 9:
	{
		m_texture->Part(2, 2);
		break;
	}

	default:
		break;
	}


}

void Score::Draw()
{
	
	m_texture->updateVertex(50,50,XMFLOAT3(1.0f,1.0f,1.0f));
	m_texture->updateVbuffer();

	m_texture->Draw();
}

void Score::Finish()
{
	m_texture->UnInit();
	delete m_texture;

}
