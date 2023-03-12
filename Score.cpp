
//=============================================================================
//
// �X�R�A���� [Score.cpp]
//
//=============================================================================
#include "Score.h"
#include"CTexMgr.h"
#include"Scean.h"
#include"BoidsAIMgr.h"
#include"Application.h"
#include"CDirectInput.h"
#include"IMgui/imgui.h"


/// <summary>
/// �X�R�A�̏���������
/// </summary>
/// <param name="pos">1���ڂ̃|�W�V����</param>
void Score::Init(XMFLOAT3 pos)
{
	
	m_texture = new CTex();
	
	//�e�N�X�`�����Z�b�g
	m_texture->LoadTexture("assets/UI/suuzi.png");

	//�����l�̑傫�����Z�b�g
	m_texture->Init(50, 50, XMFLOAT3(1.0f, 1.0f, 1.0f));

	//�傫�����Z�b�g
	bscale = myscale;
	////�����O�m�[�c�̐擪�e�N�X�`�����Z�b�g
	m_texture->SetScale(1.0, 1.0, 1.0f);
	
	//���݂̃|�W�V����
	bpos = pos;
	mypos = pos;
	
	//������
	m_texture->PartMax(5, 5);
	m_texture->SetPosition(pos.x, pos.y, pos.z);
	
	//�X�R�A�����l
	b_num = 0;
}

void Score::Update(int num,int kurai)
{
	//UV�A�j���[�V����
	XMFLOAT2 c_uv[4] =
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};	
	//�A�j���[�V����
	m_texture->SetUV(c_uv);

	//////////////////////////////////////////////
	//�������ύX���ꂽ��A�j���[�V����������
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
	////////////////////////////////////////////////////////



	//�ʒu�A�X�P�[������	
	m_texture->SetPosition(bpos.x, bpos.y, bpos.z);
	m_texture->SetScale(bscale.x, bscale.y, bscale.z);

	b_num = num;

	//�l�ɂ���Đ�����`��
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


/// <summary>
/// �`�揈��
/// </summary>
void Score::Draw()
{
	//���_�X�V
	m_texture->updateVertex(50,50,XMFLOAT3(1.0f,1.0f,1.0f));
	m_texture->updateVbuffer();

	//�e�N�X�`���`��
	m_texture->Draw();
}

/// <summary>
/// �I������
/// </summary>
void Score::Finish()
{
	m_texture->UnInit();
	delete m_texture;

}
