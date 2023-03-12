
//=============================================================================
//
// スコア処理 [Score.cpp]
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
/// スコアの初期化処理
/// </summary>
/// <param name="pos">1桁目のポジション</param>
void Score::Init(XMFLOAT3 pos)
{
	
	m_texture = new CTex();
	
	//テクスチャをセット
	m_texture->LoadTexture("assets/UI/suuzi.png");

	//初期値の大きさをセット
	m_texture->Init(50, 50, XMFLOAT3(1.0f, 1.0f, 1.0f));

	//大きさをセット
	bscale = myscale;
	////ロングノーツの先頭テクスチャをセット
	m_texture->SetScale(1.0, 1.0, 1.0f);
	
	//現在のポジション
	bpos = pos;
	mypos = pos;
	
	//分割数
	m_texture->PartMax(5, 5);
	m_texture->SetPosition(pos.x, pos.y, pos.z);
	
	//スコア初期値
	b_num = 0;
}

void Score::Update(int num,int kurai)
{
	//UVアニメーション
	XMFLOAT2 c_uv[4] =
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};	
	//アニメーション
	m_texture->SetUV(c_uv);

	//////////////////////////////////////////////
	//数字が変更されたらアニメーションさせる
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



	//位置、スケール調整	
	m_texture->SetPosition(bpos.x, bpos.y, bpos.z);
	m_texture->SetScale(bscale.x, bscale.y, bscale.z);

	b_num = num;

	//値によって数字を描画
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
/// 描画処理
/// </summary>
void Score::Draw()
{
	//頂点更新
	m_texture->updateVertex(50,50,XMFLOAT3(1.0f,1.0f,1.0f));
	m_texture->updateVbuffer();

	//テクスチャ描画
	m_texture->Draw();
}

/// <summary>
/// 終了処理
/// </summary>
void Score::Finish()
{
	m_texture->UnInit();
	delete m_texture;

}
