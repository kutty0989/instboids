#pragma once
#include <cinttypes>
#include"Scean.h"

//=============================================================================
//
// �SGame�V�[������ [Game.h]
//
//=============================================================================
class Game {
public:

	//�Q�[���V�[��
	enum GAME_SCEAN_ID
	{
		S_ID_TITLE_INI,//�^�C�g��������
		S_ID_TITLE_UPDATE,//�^�C�g���X�V
		S_ID_STAGE1_INI,//�f���X�e�[�W������
		S_ID_STAGE1_UPDATE,//�f���V�[���X�V
		S_ID_GAMEOVER_INI,
		S_ID_GAMEOVER_UPDATE,
		S_ID_CLEAR_INI,
		S_ID_CLEAR_UPDATE,


		S_ID_MAX//���X�g
	};


	static Game* GetInstance()
	{
		static Game instance;
		return &instance;
	}


	GAME_SCEAN_ID GAME_MODE = S_ID_STAGE1_INI;//�����̃Q�[���V�[��
	GAME_SCEAN_ID B_GAME_MODE;//�O��̃Q�[�����[�h

	static void GameInit();
	static void GameInput(uint64_t dt);
	static void GameUpdate(uint64_t dt);
	static void GameRender(uint64_t dt);
	static void GameDispose();



protected:
	static Scean* mScean;


};
