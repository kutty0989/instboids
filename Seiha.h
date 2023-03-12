#pragma once
#include"Scean.h"


//=============================================================================
//
// ゲームシーン処理 [Seiha.h]
//
//=============================================================================
class Seiha :public Scean
{
public:
	void Initialize();//モデルを一度だけ読み込む
	void Reset();//条件の初期化
	void Release();//モデルの解放処理
	void Update(uint64_t dt);//カメラやモデル、光源を変更
	void Draw();//プレイヤーや地面を描画
	bool IsAbleChangeScean();//シーン遷移条件関数

	
};