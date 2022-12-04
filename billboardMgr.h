#pragma once
#include<list>
#include<DirectXMath.h>
#include"granate.h"

class BillBoardMgr
{
public:

	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);

	void Update();

	void Draw();

	void Finalize();

	void GranateCreate(XMFLOAT3 pos);

	static BillBoardMgr* GetInstance()
	{
		static BillBoardMgr instance;
		return &instance;
	}

	

	void BGranateCreate();

	std::list <std::unique_ptr<Granate>> g_granatelist;//’e‚Ì”z—ñ

	
private:


};
