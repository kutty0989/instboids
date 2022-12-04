#pragma once
#include <cinttypes>
#include"Scean.h"
class Game {
public:

	static void GameInit();
	static void GameInput(uint64_t dt);
	static void GameUpdate(uint64_t dt);
	static void GameRender(uint64_t dt);
	static void GameDispose();



protected:
	static Scean* mScean;

	// ƒJƒƒ‰
	//static CCamera* mCamera;

};
