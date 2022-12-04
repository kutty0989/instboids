#include"S_Title.h"
#include"Timing_UI.h"
#include"Notes.h"
#include"CCamera.h"
#include"CDirectInput.h"
#include"CTex.h"
#include "CLight.h"

//CModel			g_model;			// 主人公モデル



CModel			g_modelenemy;		// 敵モデル
XMFLOAT4X4		g_mtxenemy;			// 敵の行列


std::vector<COBB*> g_playerobblist;
std::vector<COBB*> g_enemyobblist;

void S_Title::Initialize()
{
	bool sts = false;

	// ASSIMPを使用したモデル読み込み
	// ASSIMPを使用したモデル読み込み
	//sts = g_model.Init("assets/Charcter.x", "shader/vsoneskin.fx", "shader/ps.fx",
	//	"");
	//if (!sts) {
	//	MessageBox(NULL, "load enemy model error", "error", MB_OK);
	//	
	//}
	//sts = g_model.Init("assets/Charcter.x", "shader/vsoneskin.fx", "shader/ps.fx",
	//	"");
	//if (!sts) {
	//	MessageBox(NULL, "load enemy model error", "error", MB_OK);
	//
	//}

	//// 単位行列にする
	//DX11MtxIdentity(g_mtxplayer);

	//// ASSIMPを使用したアニメーションの読み込み
	//sts = g_model.LoadAnimation("assets/Charcter.x");
	//if (!sts) {
	//	MessageBox(NULL, "load enemy animation error", "error", MB_OK);
	//	
	//}

		//ディスプレイトメントマッピングをしたい画像の初期化
		//Titlepng = new CHeight_Map();
		//Titlepng->LoadTexture("assets/UI/taisetsu.png");
		//Titlepng->Init(100.0f, 100.0f, XMFLOAT3(1.0f, 1.0f, 1.0f),"Quad_Lo.obj","assets");
		//Titlepng->SetPosition(0.0f,0.0f, 0.0f);
		//Titlepng->SetScale(1.0f, 1.0f, 1.0f);

	
}

void S_Title::Update(uint64_t dt)
{
	// 入力を受け付ける
	CDirectInput::GetInstance().GetKeyBuffer();
	static XMFLOAT3 angle[2] = {
							{ -90.0f,0.0f,0.0f },
							{ -90.0f, 0.0f, 0.0f }
	};			// 角度情報

	static XMFLOAT3 trans[2] = {
		{ 0.0f,0.0f,0.0f, },
		{ 0.0f, 0.0f, 0.0f }
	};			// 平行移動量

	static float zpos = 0.0f;

	static unsigned int animno = 0;

	static int idx = 0;


	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
		angle[idx].y++;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
		angle[idx].y--;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F1)) {
		zpos += 1.0f;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F2)) {
		zpos -= 1.0f;
	}


	//if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
	//	animno++;
	//	unsigned int animnummax = g_model.GetAnimationNum();
	//	if (animno >= animnummax) {
	//		animno = 0;
	//	}
	//}

	//if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RETURN)) {
	//	g_model.ChangeAnimFileIdx();
	//}


	//DX11MakeWorldMatrix(g_mtxplayer, angle[0], trans[0]);
	//g_mtxplayer._43 = zpos;

	//g_model.Update(animno,			// アニメーション番号
	//	g_mtxplayer);				// モデル表示位置と姿勢

	//DX11MakeWorldMatrix(g_mtxenemy, angle[1], trans[1]);
	//g_mtxenemy._43 = zpos;



	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
	//	Titlepng->g_hight += 10.01f;

	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
	//	Titlepng->g_hight -= 10.01f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
	//	Titlepng->g_angle += 1.01f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
	//	Titlepng->g_angle -= 1.01f;
	//}

	//
//	CCamera::GetInstance()->Update(S_Title::GetInstance()->g_mtxplayer);

}

void S_Title::Draw()
{
	g_mtxplayer._11 = 1.0f;
	g_mtxplayer._22 = 1.0f;
	g_mtxplayer._33 = 1.0f;
	// モデル描画

	// モデル描画
	//g_model.Draw(g_mtxplayer);
	//ディスプレイトメントマッピングをしたい画像の描画
//	Titlepng->SetUV(CHeight_Map::GetInstance()->c_uv);
//	Titlepng->SetScale(1.0f, 1.0f, 1.0f);
//	Titlepng->SetRotation(90.0f,0.0f,0.0f);
//	Titlepng->updateVertex(100.0f, 100.0f, XMFLOAT3(1.0f, 0.5f, 1.0f));
//	Titlepng->updateVbuffer();
//	Titlepng->Draw();
//
//

}
void S_Title::Release()
{
	// モデル終了処理
//	g_model.Uninit();



	// DirectX11 グラフィックス終了処理
	CDirectXGraphics::GetInstance()->Exit();
}

bool S_Title::IsAbleChangeScean()
{
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}
