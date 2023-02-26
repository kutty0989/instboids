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

	bscale = myscale;
	////ロングノーツの先頭テクスチャをセット
	m_texture->SetScale(1.0, 1.0, 1.0f);
	
	bpos = pos;
	mypos = pos;


	
	m_texture->PartMax(5, 5);
	m_texture->SetPosition(pos.x, pos.y, pos.z);
	b_num = 0;
}

void Score::Update(int num,int kurai)
{
	XMFLOAT2 c_uv[4] =
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};	
	m_texture->SetUV(c_uv);


	if (b_num != num)
	{
		bpos.y = mypos.y+0.01;
		bscale.x = 1.1f;
		bscale.y = 1.1f;
		if (kurai >= 2)
		{
			rotate = true;
		}

	}

	if (rotate)
	{
		angle += 5.0f;
	}
	if (angle >= 360)
	{
		rotate = false;
		angle = 0.0f;
	}
	if(bpos.y > mypos.y)
	{ 
		bscale.x -= 0.01f;
		bscale.y -= 0.01f;
		bpos.y -= 0.001f;
	}
	if (bpos.y >= mypos.y + 0.01)
	{
		bpos.y = bpos.y + 0.01f;
		bscale.x = bscale.x + 0.1f;
		bscale.y = bscale.y + 0.1f;
	}
	
	m_texture->SetPosition(bpos.x, bpos.y, bpos.z);
	m_texture->SetScale(bscale.x, bscale.y, bscale.z);
//	m_texture->SetRotation(angle);
	b_num = num;

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
