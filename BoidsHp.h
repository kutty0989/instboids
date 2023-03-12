#pragma once
//=============================================================================
//
// プレイヤーのHPクラス [BombHp.h]
//
//=============================================================================

#include"CBillBoard.h"
#include"CTex.h"
#include"CTexInstance.h"
class BoidsHp {
private:

	CTexInstance* m_texture;//テクスチャ
	 CBillBoard* m_bill;
	 CBillBoard* hpin;
	 CBillBoard* hpout;
	 CBillBoard* hpub;


public:
	XMFLOAT2 mousepos;

	void Init();

	void Create();

	void Update(XMFLOAT3 pos);
	
	void UpdateHp(int hp);

	void Draw();

	void Finish();


	static BoidsHp* GetInstance()
	{
		static BoidsHp instance;
		return &instance;
	}


private:

	void SetTexture(CBillBoard* tex)
	{
		m_bill = tex;
	}

	void Sethpout(CBillBoard* tex)
	{
		hpout = tex;
	}
	

	void Sethpin(CBillBoard* tex)
	{
		hpin = tex;
	}

};
