#pragma once
//=============================================================================
//
// スコア処理 [Score.h]
//
//=============================================================================
#include"CTex.h"


class Score {
private:

	int b_num = 0;//BoidsAIから渡されたスコアを格納用
	XMFLOAT3 mypos;//現在の場所
	XMFLOAT3 bpos;//アニメーション用の場所

	XMFLOAT3 bscale;//アニメーション用の場所
	XMFLOAT3 myscale = {1.0f,1.0f,1.0f};//初期値

	bool rotate = false;//二桁以上回転
	int angle = 0;//角度
	CTex* m_texture;//テクスチャ

	bool mIsInstancing = true;
public:
	int drawnum;//描画の桁数

	XMFLOAT2 mousepos;

	//初期化処理
	void Init(XMFLOAT3 pos);

	//スコア更新処理
	void Update(int num,int kurai);

	//スコア描画処理
	void Draw();

	//スコア終了処理
	void Finish();


	static Score* GetInstance()
	{
		static Score instance;
		return &instance;
	}



private:

	//テクスチャをセット
	void SetTexture(CTex* tex)
	{
		m_texture = tex;
	}
};


