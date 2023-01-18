#pragma once
#include<list>
#include<DirectXMath.h>
#include"granate.h"
#include"Score.h"

class TexMgr
{
public:

	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);

	void Update();

	void Draw();

	void Finalize();

	void ScoreCreate(XMFLOAT3 pos);

	static TexMgr* GetInstance()
	{
		static TexMgr instance;
		return &instance;
	}

	std::vector <std::unique_ptr<Score>> g_scorevector;//’e‚Ì”z—ñ


private:


};
