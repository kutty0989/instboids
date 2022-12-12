#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "Seiha.h"
#include"game.h"
#include"IMgui/imgui.h"
#include"IMgui/imgui_impl_win32.h"
#include"IMgui/imgui_impl_dx11.h"
#include"gui.h"
#include"S_Title.h"
#include"S_Clear.h"
#include"XIController.h"

/// <summary>
/// ゲームのシーン
/// </summary>
enum GAME_SCEAN_ID
{
	S_ID_TITLE_INI,
	S_ID_TITLE_UPDATE,
	S_ID_STAGE1_INI,
	S_ID_STAGE1_UPDATE,
	S_ID_GAMEOVER_INI,
	S_ID_GAMEOVER_UPDATE,
	S_ID_CLEAR_INI,
	S_ID_CLEAR_UPDATE,


	S_ID_MAX
};

GAME_SCEAN_ID GAME_MODE = S_ID_STAGE1_INI;//初期のゲームシーン
GAME_SCEAN_ID B_GAME_MODE;//前回のゲームモード
Scean* Game::mScean;


bool StageClear_Flg = false;//updateで結果をboolで返してもらいリザルトへ

void Game::GameInit() {
	// DX11初期化
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,//画面サイズ
		Application::CLIENT_HEIGHT,
		false);

	// ここからImGui初期化------------
// バージョンチェック
	IMGUI_CHECKVERSION();

	// ImGuiのコンテキスト作成
	ImGui::CreateContext();

	// ImGuiのIO取得
	ImGuiIO& io = ImGui::GetIO();

	// Win32の初期化内容でImGui初期化
	// アプリケーションのhWndを渡す
	bool sts = ImGui_ImplWin32_Init(Application::Instance()->GetHWnd());

	// TODO: エラーチェック

		// DX11の初期化内容でImGui初期化
	sts = ImGui_ImplDX11_Init(GetDX11Device(), GetDX11DeviceContext());

	// TODO: エラーチェック

// スタイルをダークに統一
	ImGui::StyleColorsDark();
	// ここまでImGui初期化----------------


	// カメラが必要
	DirectX::XMFLOAT3 eye(0, 100, -50);		// カメラの位置
	DirectX::XMFLOAT3 lookat(0, -10, 0);		// 注視点
	DirectX::XMFLOAT3 up(0,  1, 0);			// カメラの上向きベクトル

	CCamera::GetInstance()->Init(
		10.0f,							// ニアクリップ
		10000.0f,						// ファークリップ
		XM_PI / 5.0f,					// 視野角
		static_cast<float>(Application::CLIENT_WIDTH),		// スクリーン幅
		static_cast<float>(Application::CLIENT_HEIGHT),		// スクリーンの高さ
		eye, lookat, up);					// カメラのデータ

	// 平行光源をセット
	DX11LightInit(
		DirectX::XMFLOAT4(0, 10, 1, 0));

	// DIRECTINPUT初期化
	CDirectInput::GetInstance().Init(
		Application::Instance()->GetHInst(),
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,			// スクリーン幅
		Application::CLIENT_HEIGHT			// スクリーンの高さ
	);

	// アルファブレンド有効化
	TurnOnAlphablend();

	srand(GetTickCount());//乱数を最初に一回だけ設定


}

void Game::GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
	XIController::Update();
}

void Game::GameUpdate(uint64_t dt) {

	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("FPS");
		ImGui::SetNextWindowSize(ImVec2(300, 400));
		float dlet = dt;
		dlet =16.666 /dlet;
		dlet = 60 * dlet;
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;
		ImGui::DragFloat("FPS", &dlet);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}


	switch (GAME_MODE)
	{
	case S_ID_TITLE_INI:
	{
		mScean = new S_Title();//タイトルシーン読み込み
		mScean->Initialize();
		GAME_MODE = S_ID_TITLE_UPDATE;

		break;
	}

	case S_ID_TITLE_UPDATE:
	{
		mScean->Update(dt);


		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			GAME_MODE = S_ID_STAGE1_INI;
		}

		break;
	}

	case S_ID_STAGE1_INI:
	{
		mScean = new Seiha();
		mScean->Initialize();
		GAME_MODE = S_ID_STAGE1_UPDATE;

		break;
	}

	case S_ID_STAGE1_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			GAME_MODE = S_ID_CLEAR_INI;
		}
		break;
	}
	case S_ID_CLEAR_INI:
	{
		mScean = new S_Clear();
		mScean->Initialize();
		GAME_MODE = S_ID_CLEAR_UPDATE;

		break;
	}

	case S_ID_CLEAR_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			GAME_MODE = S_ID_TITLE_INI;
		}
		break;
	}

	
	}

	// 空中戦更新
	//AirFightUpdate();

}



void Game::GameRender(uint64_t dt) {

	float col[4] = { 1,0,0,1 };

	// 描画前処理
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;

	// プロジェクション変換行列取得
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// ビュー変換行列を取得
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);



	mScean->Draw();
	
	// テスト表示ここから---------------------------------

	imgui::GetInstance()->draw();

	// テスト表示ここまで---------------------------------

	// ImGuiの描画実行呼び出しここから
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// ここまで
	// Dxのpresent関数呼び出し
	// 描画後処理
	DX11AfterRender();
}

void Game::GameDispose() {

	// ここからImGuiの解放処理------------------
	// DX11に対するImGuiの処理終了
	ImGui_ImplDX11_Shutdown();
	// Win32に対するImGuiの処理終了
	ImGui_ImplWin32_Shutdown();
	// コンテキストを削除
	ImGui::DestroyContext(ImGui::GetCurrentContext());
	// ここまでImGuiの解放処理------------------

	CTexMgr::GetInstance().Finalize();
	DX11Uninit();
}