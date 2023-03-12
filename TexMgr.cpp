//=============================================================================
//
// テクスチャー管理クラス [TexMgr.cpp]
//
//=============================================================================

#include "TexMgr.h"
#include"ModelMgr.h"
#include"Scean.h"
#include"CTexMgr.h"
#include"BoidsAIMgr.h"

/// <summary>
/// /スコアを5桁制作
/// </summary>
void TexMgr::Init()
{
	for (int i = 0; i < 5; i++)
	{
		XMFLOAT3 pos;
		pos.x = -0.8+i*0.05;
		pos.y = -0.8;
		pos.z = 0;
		ScoreCreate(pos);
	}
}



/// <summary>
/// スコアの位を調整
/// </summary>
void TexMgr::Update()
{
	//スコアを取ってくる
	int aa = BoidsAIMgr::GetInstance()->ScoreNum;

	//格納していく
	g_scorevector.at(0)->drawnum = aa * 0.0001;
	g_scorevector.at(1)->drawnum = aa * 0.001 - g_scorevector.at(0)->drawnum * 10;
	g_scorevector.at(2)->drawnum = aa * 0.01 - g_scorevector.at(0)->drawnum * 100 - g_scorevector.at(1)->drawnum * 10;
	g_scorevector.at(3)->drawnum = aa * 0.1 - g_scorevector.at(0)->drawnum * 1000 - g_scorevector.at(1)->drawnum * 100 - g_scorevector.at(2)->drawnum * 10;
	g_scorevector.at(4)->drawnum = aa - g_scorevector.at(0)->drawnum * 10000 - g_scorevector.at(1)->drawnum * 1000 - g_scorevector.at(2)->drawnum * 100 - g_scorevector.at(3)->drawnum * 10;

	//一つずつ更新
	for (int i = 0; i < g_scorevector.size(); i++)
	{
		g_scorevector.at(i)->Update(g_scorevector.at(i)->drawnum, i);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void TexMgr::Draw()
{
	//全スコア描画
	for (auto& b : g_scorevector) {
			b->Draw();	
	}
}

/// <summary>
/// 終了処理
/// </summary>
void TexMgr::Finalize()
{
	for (auto& b : g_scorevector) {
		b->Finish();
	}

	//配列をクリア
	g_scorevector.clear();
	g_scorevector.resize(0);
}



void TexMgr::ScoreCreate(XMFLOAT3 pos)
{
	std::unique_ptr<Score> p;
	p = std::make_unique<Score>();
	//弾の初期化
	p->Init(pos);
	//最後尾に球を追加
	//ベクターコンテナにユニークポインタをセット
	g_scorevector.emplace_back(std::move(p));
}
