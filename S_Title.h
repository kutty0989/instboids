#pragma once
//=============================================================================
//
// タイトルシーンクラス [S_Title.h]
//
//=============================================================================
#include"Scean.h"
#include"CTexMgr.h"
#include"CHeightMgr.h"
#include"Notes.h"
#include"CTex.h"
#include"CHeight_Map.h"
#include"CModel.h"

class S_Title :public Scean
{
public:
	void Initialize();

	void Update(uint64_t dt);

	void Draw();

	void Release();

	bool IsAbleChangeScean();
	void SetTexture(CHeight_Map* tex)
	{
		Titlepng = tex;
	}
	std::shared_ptr<BoidsAI> Im;

private:
	CHeight_Map* Titlepng = nullptr;
	CHeight_Map* Spacepng = nullptr;
	CModel* im = nullptr;
};