#pragma once
#include <cinttypes>
#include"Scean.h"
class Game {
public:

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

	
	static Game* GetInstance()
	{
		static Game instance;
		return &instance;
	}


	GAME_SCEAN_ID GAME_MODE = S_ID_STAGE1_INI;//初期のゲームシーン
	GAME_SCEAN_ID B_GAME_MODE;//前回のゲームモード

	static void GameInit();
	static void GameInput(uint64_t dt);
	static void GameUpdate(uint64_t dt);
	static void GameRender(uint64_t dt);
	static void GameDispose();



protected:
	static Scean* mScean;

	// カメラ
	//static CCamera* mCamera;

};
