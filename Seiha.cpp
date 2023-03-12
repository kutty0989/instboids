#include<string>
#include <chrono>
#include <iostream>
#include <time.h>
#include <ctime>
#include"BoidsAI.h"
#include"CCamera.h"
#include"skybox.h"
#include"BoundingSphere.h"
#include"updatespherecamera.h"
#include"CBillBoard.h"
#include"Stage.h"
#include"CLight.h"
#include"Seiha.h"
#include"Timing_UI.h"
#include"Notes_Arrange.h"
#include"BoidsAIMgr.h"
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

#define debuglog(a) std::cout<<a<<std::endl;

CModel			g_model;			// 主人公モデル
SkyBox  g_skybox;       // 背景オブジェクト
CBillBoard fire;
CLight g_clight;


static bool turnflg;//１ターンの切り替え true行動できる　false行動した
static bool createflg;//true 作っていい　false 作ったらダメ
static bool saveflg;//true まだつくられてない　false すでにつくられた
static bool notes_LR;//ノーツの左右分けるための変数　ｆ左　ｔ右　

//-----------------------------------------------------------------
//    変数宣言
//-----------------------------------------------------------------
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;//ミリ秒用
using std::chrono::seconds;//時間用変数
using std::chrono::system_clock;


XMFLOAT4 color = { 1.0f,0.1f,0.1f,0.0f };
static bool init = false;
int maxcounttime = 10000;


//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f

template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

/// <summary>
/// 初期化処理
/// </summary>
void Seiha::Initialize() {

	//ゲームで一度だけ
	if (init == false)
	{
		//使用するモデルを全て読み込む
		for (int i = 0; i < g_modellist.size(); i++)
		{
			ModelMgr::GetInstance().LoadModel(
				g_modellist[i].modelname,
				g_modellist[i].vsfilenamename,
				g_modellist[i].psfilename,
				g_modellist[i].texfoldername
			);

		}
		//使用するインスタンス用モデルを全て読み込む
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
		//使用するテクスチャ―を全て読み込む
		for (int i = 0; i < g_texlist.size(); i++)
		{
			CTexMgr::GetInstance().LoadModel(
				g_texlist[i].cgname,
				g_texlist[i].vsfilename,
				g_texlist[i].psfilename
			);
		}
		//使用するビルボードを全て読み込む
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


	BoidsAIMgr::GetInstance()->Init();//AIの全初期化

	//スカイボックスの初期化
	g_skybox.Init();
	g_skybox.SetModel(ModelMgr::GetInstance().GetModelPtr(g_modellist[static_cast<int>(MODELID::SKYDOME)].modelname));

	///ビルボードの全初期化
	BillBoardMgr::GetInstance()->Init();

	//地形生成
	g_ground.Init();

	//マウスUIの初期化
	MouseCircle::GetInstance()->Init();
	//テクスチャ―の全初期化
	TexMgr::GetInstance()->Init();

}

/// <summary>
/// 状態を戻す
/// </summary>
void Seiha::Reset()
{
	turnflg = false;//１ターンの切り替え true行動できる　false行動した
	createflg = false;//true 作っていい　false 作ったらダメ
	saveflg = false;//true まだつくられてない　false すでにつくられた
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="dt">デルタタイム</param>
void  Seiha::Update(uint64_t dt) {
	//ダイレクトインプット初期化
	CDirectInput::GetInstance().GetMouseState();

	//AIの更新関数
	BoidsAIMgr::GetInstance()->Update();

	//スカイボックス更新
	g_skybox.Update();
	//ノーツの更新
	Timing_UI::GetInstance()->Update();

	static bool music = true;//音楽再生フラグ

	//地形の更新
	g_ground.Update();

	//カメラの位置に光源をセット
	XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	DX11LightUpdate(XMFLOAT4(eye.x, eye.y, eye.z, 1.0f));

	//テクスチャ全更新
	TexMgr::GetInstance()->Update();

	//マウスサークル更新
	MouseCircle::GetInstance()->Update();

	//カメラの位置更新
	XMFLOAT4X4 mat;
	DX11MtxIdentity(mat);
	CCamera::GetInstance()->Update(mat);
	CCamera::GetInstance()->Update(BoidsAIMgr::GetInstance()->ImBoidsAI->GetMtx());

}

/// <summary>
/// 描画関数 
/// </summary>
void Seiha::Draw()
{
	//スカイボックス描画
	g_skybox.Draw();

	//地形描画
	g_ground.Draw();

	//ビルボード全描画
	BillBoardMgr::GetInstance()->Draw();

	//AI全描画
	BoidsAIMgr::GetInstance()->Draw();

	//マウスUI描画
	MouseCircle::GetInstance()->Draw();

	//テクスチャ―全描画
	TexMgr::GetInstance()->Draw();
}

/// <summary>
/// シーン遷移条件関数
/// </summary>
/// <returns></returns>
bool Seiha::IsAbleChangeScean()
{
	//スペースで現状変更
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}

void  Seiha::Release() {

	// プレイヤ終了処理	
	BoidsAIMgr::GetInstance()->Finsh();
	//スカイボックス終了処理
	g_skybox.Finalize();
	//地形終了処理
	g_ground.Finalize();
	//マウスUI終了処理
	MouseCircle::GetInstance()->Finish();
	//全ビルボード終了処理
	BillBoardMgr::GetInstance()->Finalize();
	//モデル全終了処理
	ModelMgr::GetInstance().Finalize();
	//テクスチャ終了処理
	TexMgr::GetInstance()->Finalize();
	//ノーツ終了処理
	Timing_UI::GetInstance()->Finish();

}

/// <summary>
/// カメラ行列計算
/// </summary>
void mtx()
{
	XMFLOAT4X4 vmtx;
	XMFLOAT4X4 pmtx;

	pmtx = CCamera::GetInstance()->GetProjectionMatrix();

	vmtx = CCamera::GetInstance()->GetCameraMatrix();

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, pmtx);

}

/// <summary>
/// UI描画処理
/// </summary>
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