#pragma once
//=============================================================================
//
// ビルボード管理クラス [billboardMgr.h]
//
//=============================================================================
#include<list>
#include<DirectXMath.h>
#include"granate.h"
#include"Explsion.h"


class BillBoardMgr
{
public:

	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);

	void Update();

	void Draw();

	void Finalize();

	void GranateCreate(XMFLOAT3 pos);

	void ExplsionCreate(XMFLOAT3 pos);

	static BillBoardMgr* GetInstance()
	{
		static BillBoardMgr instance;
		return &instance;
	}

	

	void BGranateCreate();

	void BExplsionCreate();

	std::list <std::unique_ptr<Granate>> g_granatelist;//弾の配列

	std::vector <std::unique_ptr<Explsion>> g_explsionlist;//弾の配列

	
private:


};
