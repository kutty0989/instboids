#pragma once
//=============================================================================
//
// テクスチャー管理クラス [TexMgr.h]
//
//=============================================================================
#include<list>
#include<DirectXMath.h>
#include"granate.h"
#include"Score.h"

class TexMgr
{
public:

	//初期化処理
	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);

	//更新
	void Update();

	//描画
	void Draw();

	//終了処理
	void Finalize();

	//スコアのイラストを制作
	void ScoreCreate(XMFLOAT3 pos);

	static TexMgr* GetInstance()
	{
		static TexMgr instance;
		return &instance;
	}

	
	std::vector <std::unique_ptr<Score>> g_scorevector;//スコアのイラスト配列


private:


};
