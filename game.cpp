//=============================================================================
//
// 全Gameシーン処理 [Game.cpp]
//
//=============================================================================

#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "Seiha.h"
#include"Game.h"
#include"IMgui/imgui.h"
#include"IMgui/imgui_impl_win32.h"
#include"IMgui/imgui_impl_dx11.h"
#include"gui.h"
#include"S_Title.h"
#include"S_Clear.h"
#include"XIController.h"
#include"Scean.h"
#include"CBillboardMgr.h"
#include"CTexMgr.h"
#include"InstanceModelMgr.h"

Scean* Game::mScean;

/// <summary>
/// シーン初期化
/// </summary>
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
	DirectX::XMFLOAT3 up(0, 1, 0);			// カメラの上向きベクトル

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

/// <summary>
/// インプット更新
/// </summary>
/// <param name="dt"></param>
void Game::GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
	XIController::Update();
}

/// <summary>
/// ゲームシーン更新
/// </summary>
/// <param name="dt"></param>
void Game::GameUpdate(uint64_t dt) {

	//FPS表示GUI
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("FPS");
		ImGui::SetNextWindowSize(ImVec2(300, 400));
		float dlet = dt;
		dlet = 16.666 / dlet;
		dlet = 60 * dlet;
		ImGui::DragFloat("FPS", &dlet);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	//シーン遷移
	switch (Game::GetInstance()->GAME_MODE)
	{
	case S_ID_TITLE_INI:
	{
		mScean = new S_Title();//タイトルシーン初期化読み込み
		mScean->Initialize();
		Game::GetInstance()->GAME_MODE = S_ID_TITLE_UPDATE;

		break;
	}

	case S_ID_TITLE_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			Game::GetInstance()->GAME_MODE = S_ID_STAGE1_INI;//デモシーン移動
		}

		break;
	}
	//デモシーン初期化
	case S_ID_STAGE1_INI:
	{
		mScean = new Seiha();//デモシーン初期化読み込み
		mScean->Initialize();
		Game::GetInstance()->GAME_MODE = S_ID_STAGE1_UPDATE;

		break;
	}
	//デモシーン更新
	case S_ID_STAGE1_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			Game::GetInstance()->GAME_MODE = S_ID_TITLE_INI;
		}
		break;
	}

	}

}


/// <summary>
/// ゲーム秒描画
/// </summary>
/// <param name="dt"></param>
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

	//ImGuiの描画実行呼び出しここから
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// ここまで
	// Dxのpresent関数呼び出し
	// 描画後処理
	DX11AfterRender();
}

/// <summary>
/// 終了処理
/// </summary>
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