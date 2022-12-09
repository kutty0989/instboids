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

void Seiha::Initialize() {

	
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


		//g_air.InitiInstancing(5000, "assets/f1/f1.x.dat", "assets/vsinstance.fx", "assets/ps.fx");
	


	/*	bool sts = false;
		sts = g_model.Init("assets/Charcter.x", "shader/vs.hlsl", "shader/ps.hlsl","");
		if (!sts) {
			MessageBox(NULL, "load enemy model error", "error", MB_OK);

		}*/

		// 単位行列にする
		//DX11MtxIdentity(g_mtxplayer);


		//{
			////境界球作成
			////モデルの前頂点を抜き出す
			//const CModel* pmodel = ModelMgr::GetInstance().GetModelPtr(g_modellist[static_cast<int>(MODELID::PLAYER)].modelname);
			//const ModelData& md = pmodel->GetModelData();
			//const std::vector<Mesh>& meshes = md.GetMeshes();

			//std::vector<XMFLOAT3> verticis;


			//for (auto& m : meshes) {
			//	{
			//		for (auto& v : m.m_vertices)
			//		{
			//			verticis.emplace_back(v.m_Pos);
			//		}
			//	}
			//}

			////境界球初期化
			//g_boundingsphere.Init(
			//	verticis,//長点数
			//	XMFLOAT4(1, 1, 1, 0.0f//頂点カラー
			//	));



		//	//境界球初期化
		//	g_bsenemy.Init(
		//		verticis,//長点数
		//		XMFLOAT4(1, 1, 1, 0.0f//頂点カラー
		//		));
		//	g_s_bsenemy.Init(
		//		verticis,//長点数
		//		XMFLOAT4(1, 1, 1, 0.0f//頂点カラー
		//		));
		//	//境界球初期化
		//	g_bshomis.Init(
		//		verticis,//長点数
		//		XMFLOAT4(1, 1, 1, 0.0f//頂点カラー
		//		));
		//	//境界球初期化
		//	g_bsbullet.Init(
		//		verticis,//長点数
		//		XMFLOAT4(1, 1, 1, 0.0f//頂点カラー
		//		));
		//}


		//BoidsHp::GetInstance()->Init();
	/*	fire.LoadTexTure("assets/UI/circle.png");
		XMFLOAT4 firecol = { 1.0f,1.0f,1.0f,1.0f };

		fire.Init(Player::GetInstance()->GetPos().x, 500.0f, Player::GetInstance()->GetPos().z + 100.0f, 100.0f, 100.0f, firecol);


	XMFLOAT2 fireUV[] =
		{
			{0,0},
			{0,1},
			{1,0},
			{1,1}
		};

		fire.SetUV(fireUV);
		fire.SetPosiotion(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z + 30.0f);*/

	
	//// プレイヤ初期化
	//Player::GetInstance()->Init();
	//Player::GetInstance()->SetModel(ModelMgr::GetInstance().GetModelPtr(g_modellist[static_cast<int>(MODELID::PLAYER)].modelname));
	//Player::GetInstance()->SetColor(XMFLOAT4(0.1f, 1.0f, 1.0f, 1.0f));

	PlayerMgr::GetInstance()->Init();

	g_skybox.Init();
	g_skybox.SetModel(ModelMgr::GetInstance().GetModelPtr(g_modellist[static_cast<int>(MODELID::SKYDOME)].modelname));
	
	BillBoardMgr::GetInstance()->Init();

	//g_stage.Init();

	g_ground.Init();
	
	MouseCircle::GetInstance()->Init();

	//BPM_DATA::GetInstance()->BGM();

	//Timing_UI::GetInstance()->Init();
	//Notes_Arrange::GetInstance()->Init();
	//

	

}
void Seiha::Reset()
{

	turnflg = false;//１ターンの切り替え true行動できる　false行動した
	createflg = false;//true 作っていい　false 作ったらダメ
	saveflg = false;//true まだつくられてない　false すでにつくられた
	
}
void  Seiha::Update(uint64_t dt) {


	CDirectInput::GetInstance().GetMouseState();
	//BPM_DATA::GetInstance()->BPM_Count();

	// プレイヤ更新
	//Player::GetInstance()->Update();
	PlayerMgr::GetInstance()->Update();
	
	g_skybox.Update();

//	g_boundingsphere.UpdatePosition(Player::GetInstance()->GetMtx());
	Timing_UI::GetInstance()->Update();


	static bool music = true;
	BillBoardMgr::GetInstance()->Update();

	
	//Notes_Arrange::GetInstance()->Update();
	//NotesCreateTurn();//ノーツが一度だけｂｐｍに合わせて作られるように

	g_ground.Update();


	//カメラの位置に光源をセット
	XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	DX11LightUpdate(XMFLOAT4(eye.x, eye.y, eye.z, 1.0f));

	//
	

	MouseCircle::GetInstance()->Update();
	CCamera::GetInstance()->Update(PlayerMgr::GetInstance()->ImPlayer->GetMtx());
	
}
void Seiha::Draw() 
{

	// プレイヤ描画
	// プレイヤ描画(ローカル座標軸描画付き)
//	Player::GetInstance()->DrawWithAxis();

	
		//
	g_skybox.Draw();
	
	g_ground.Draw();

	BillBoardMgr::GetInstance()->Draw();

	PlayerMgr::GetInstance()->Draw();
	
	
	//fire.DrawBillBoard(CCamera::GetInstance()->GetCameraMatrix());
	
	//BoidsHp::GetInstance()->Draw();
	MouseCircle::GetInstance()->Draw();


	//	// 敵描画
	//XMFLOAT4X4 viewmtx = CCamera::GetInstance()->GetCameraMatrix();
	//for (int i = 0; i < ENEMYMAX; i++) {
	//	XMFLOAT3 pos = g_enemy[i].GetPos();
	//	g_billboard.SetPosition(pos.x,pos.y, pos.z);
	//	g_billboard.DrawBillBoard(viewmtx);
	//}
	
	//Notes_Arrange::GetInstance()->NotesDraw();

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
	PlayerMgr::GetInstance()->Finsh();

//	g_boundingsphere.Exit();

	g_skybox.Finalize();


	/*g_bsenemy.Exit();
	g_s_bsenemy.Exit();
	g_bshomis.Exit();
	g_bsbullet.Exit();*/
	g_ground.Finalize();
	MouseCircle::GetInstance()->Finish();
	BillBoardMgr::GetInstance()->Finalize();

	CTexMgr::GetInstance().Finalize();
	ModelMgr::GetInstance().Finalize();
	//Timing_UI::GetInstance()->Finish();
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