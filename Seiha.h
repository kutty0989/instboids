#pragma once
#include"Scean.h"


bool hitenemy();//“G‚Æ’e‚Ì“–‚½‚è”»’è

class Seiha :public Scean
{
public:
	void Initialize();
	void Reset();
	void Release();
	void Update(uint64_t dt);
	void Draw();
	bool IsAbleChangeScean();

	static int counttime;
	static float pertime;
	static bool changemapflg;

};

