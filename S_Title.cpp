//=============================================================================
//
// タイトルシーンクラス [S_Title.cpp]
//
//=============================================================================
#include"S_Title.h"
#include"Timing_UI.h"
#include"Notes.h"
#include"CCamera.h"
#include"CDirectInput.h"
#include"CTex.h"
#include "CLight.h"


CModel			g_modelenemy;		// 敵モデル
XMFLOAT4X4		g_mtxenemy;			// 敵の行列


std::vector<COBB*> g_BoidsAIobblist;
std::vector<COBB*> g_enemyobblist;

void S_Title::Initialize()
{
	bool sts = false;


}

void S_Title::Update(uint64_t dt)
{
}

void S_Title::Draw()
{
	

}
void S_Title::Release()
{
}

bool S_Title::IsAbleChangeScean()
{

	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}

	
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}
