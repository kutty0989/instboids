#include	<string>
#include	"player.h"
#include	"CCamera.h"
#include    "skybox.h"
#include    "BoundingSphere.h"
#include    "updatespherecamera.h"
#include"CBillBoard.h"
#include"Stage.h"
#include "CLight.h"
#include"Seiha.h"
#include"Timing_UI.h"
#include"Notes_Arrange.h"
#include"PlayerMgr.h"
#include"MouseCircle.h"
#include"S_Title.h"
#include"BoidsHp.h"
#include"CBillboardMgr.h"
#include"billboardMgr.h"
#include"CModelInstance.h"
#include"enemy.h"
#include"InstanceModelMgr.h"
#include"TexMgr.h"
#include"game.h"
#include <chrono>
#include <iostream>
#include <time.h>
#include <ctime>
#define debuglog(a) std::cout<<a<<std::endl;

CModel			g_model;			// 主人公モデル


//Player	g_player;		// プレイヤオブジェクト
SkyBox  g_skybox;       // 背景オブジェクト
//BoundingSphere g_boundingsphere;//当たり判定の球オブジェクト


CBillBoard fire;
CLight g_clight;


static bool turnflg;//１ターンの切り替え true行動できる　false行動した
static bool createflg;//true 作っていい　false 作ったらダメ
static bool saveflg;//true まだつくられてない　false すでにつくられた
static bool notes_LR;//ノーツの左右分けるための変数　ｆ左　ｔ右　

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

//
//
//void NotesCreateTurn()
//{
//
//	if (BPM_DATA::GetInstance()->Over_Notes_timing())
//	{
//		turnflg = false;
//		saveflg = true;
//	}
//	if ((BPM_DATA::GetInstance()->Get_zs()) && (saveflg == true))
//	{
//		turnflg = true;
//		saveflg = false;
//	}
//	if ((BPM_DATA::GetInstance()->Zero_Create_Timing()) &&(BPM_DATA::GetInstance()->Get_zs()) && (turnflg == true))
//	{
//		createflg = true;
//		turnflg = false;
//	}
//	if (turnflg == true)
//	{
//	
//	}
//	if (createflg == true)
//	{
//		Notes_Arrange::GetInstance()->NotesCreateTiming();
//		createflg = false;
//	}
//}



//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f

template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

float t;

//t = static_cast<float>()


XMFLOAT4 color = { 1.0f,0.1f,0.1f,0.0f };

static bool init = false;
int maxcounttime = 10000;
void Seiha::Initialize() {
	
	if (init == false)
	{
		//空中戦で使用するモデルを全て読み込む
		for (int i = 0; i < g_modellist.size(); i++)
		{
			ModelMgr::GetInstance().LoadModel(
				g_modellist[i].modelname,
				g_modellist[i].vsfilenamename,
				g_modellist[i].psfilename,
				g_modellist[i].texfoldername
			);

		}
		for (int i = 0; i < g_modelinstancelist.size(); i++)
		{
			InstanceModelMgr::GetInstance().LoadInstanceModel(
				g_modelinstancelist[i].num,
				g_modelinstancelist[i].modelname,
				g_modelinstancelist[i].vsfilenamename,
				g_modelinstancelist[i].psfilename,
				g_modelinstancelist[i].texfoldername

			);

		}
		for (int i = 0; i < g_texlist.size(); i++)
		{
			CTexMgr::GetInstance().LoadModel(
				g_texlist[i].cgname,
				g_texlist[i].vsfilename,
				g_texlist[i].psfilename
			);
		}
		for (int i = 0; i < g_btexlist.size(); i++)
		{
			CBillBoardMgr::GetInstance().LoadModel(
				g_btexlist[i].cgname,
				g_btexlist[i].vsfilename,
				g_btexlist[i].psfilename
			);
		}
		init = true;
	}


		PlayerMgr::GetInstance()->Init();

		g_skybox.Init();
		g_skybox.SetModel(ModelMgr::GetInstance().GetModelPtr(g_modellist[static_cast<int>(MODELID::SKYDOME)].modelname));

		BillBoardMgr::GetInstance()->Init();

		//g_stage.Init();

		g_ground.Init();

		MouseCircle::GetInstance()->Init();

		TexMgr::GetInstance()->Init();


	
	

}
void Seiha::Reset()
{

	turnflg = false;//１ターンの切り替え true行動できる　false行動した
	createflg = false;//true 作っていい　false 作ったらダメ
	saveflg = false;//true まだつくられてない　false すでにつくられた
	
}

static bool firsttime = false;
static int inittime;
int Seiha::counttime = 0;
float Seiha::pertime = 0;
bool Seiha::changemapflg = false;

void  Seiha::Update(uint64_t dt) {
	CDirectInput::GetInstance().GetMouseState();
	PlayerMgr::GetInstance()->Update();
	
	g_skybox.Update();
	Timing_UI::GetInstance()->Update();
	
	if (firsttime == false)
	{
		auto msec = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		msec = int(msec);
		inittime = msec + maxcounttime;
		firsttime = true;
	}

	auto msec = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	int nnow = msec;
	counttime = nnow - inittime;
	pertime = (float)-counttime / (float)maxcounttime;
	
	if (pertime == 0.0f)
	{
		changemapflg = true;
	}
	if(changemapflg == true)
	{
		auto msec = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		float now = msec;
		inittime = now + maxcounttime;
		changemapflg = false;
		
	}
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("time");
		ImGui::SetNextWindowSize(ImVec2(300, 400));
	
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;
		ImGui::DragInt("time", &counttime);
		ImGui::DragFloat("pertime", &pertime);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}



	static bool music = true;

	g_ground.Update();
	//カメラの位置に光源をセット
	XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	DX11LightUpdate(XMFLOAT4(eye.x, eye.y, eye.z, 1.0f));

	TexMgr::GetInstance()->Update();
	MouseCircle::GetInstance()->Update();
	XMFLOAT4X4 mat;
	DX11MtxIdentity(mat);
	CCamera::GetInstance()->Update(mat);
	CCamera::GetInstance()->Update(PlayerMgr::GetInstance()->ImPlayer->GetMtx());
	
}
void Seiha::Draw() 
{

	//int sceannum = static_cast<int>(Game::GetInstance()->GAME_MODE);
	//sceannum %= 2;
	if (Game::GetInstance()->GAME_MODE == Game::GAME_SCEAN_ID::S_ID_STAGE1_UPDATE)
	{

		g_skybox.Draw();

		g_ground.Draw();

		//BillBoardMgr::GetInstance()->Update();

		BillBoardMgr::GetInstance()->Draw();

	//	PlayerMgr::GetInstance()->Draw();

		MouseCircle::GetInstance()->Draw();

		TexMgr::GetInstance()->Draw();
	}
}

bool Seiha::IsAbleChangeScean()
{

	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}

void  Seiha::Release() {

	// プレイヤ終了処理
	//Player::GetInstance()->Finalize();
	//PlayerMgr::GetInstance()->Finsh();

//	g_boundingsphere.Exit();

	//g_skybox.Finalize();


	///*g_bsenemy.Exit();
	//g_s_bsenemy.Exit();
	//g_bshomis.Exit();
	//g_bsbullet.Exit();*/
	//g_ground.Finalize();
	//MouseCircle::GetInstance()->Finish();
	//BillBoardMgr::GetInstance()->Finalize();

	//CTexMgr::GetInstance().Finalize();
	//ModelMgr::GetInstance().Finalize();
	TexMgr::GetInstance()->Finalize();
	//Timing_UI::GetInstance()->Finish();
	// TexMgr::GetInstance()->Draw();
//	Notes_Arrange::GetInstance()->UnInit();
}

void mtx()
{
	XMFLOAT4X4 vmtx;
	XMFLOAT4X4 pmtx;

	pmtx = CCamera::GetInstance()->GetProjectionMatrix();
	//DX11MtxIdentity(pmtx);

	vmtx = CCamera::GetInstance()->GetCameraMatrix();
	//	DX11MtxIdentity(vmtx);

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, pmtx);

}


void UIDraw() {
	//2D矩形描画
	TurnOffZbuffer();//ｚバッファをオフ

	static int loop = 0;
	loop++;

	static int idk = 0;
	if (loop % 30 == 29) {
		idk++;
	}
}