#pragma once
#include"Scean.h"
#include"CTexMgr.h"
#include"Notes.h"
#include"CTex.h"
class S_Clear :public Scean
{
public:
	void Initialize();

	void Update();

	void Draw();

	void Release();

	bool IsAbleChangeScean();


private:
	CTex* Clearpng;
	CTex* Spacepng;

};