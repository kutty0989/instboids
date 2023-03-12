#pragma once
//=============================================================================
//
// ユニークエネミーのHPクラス [UniqueBombHp.h]
//
//=============================================================================
#include"CBillBoard.h"
#include"CTex.h"
#include"CTexInstance.h"
class UniqueBombHp {
private:


	CBillBoard* hpin;
	CBillBoard* hpout;


	XMFLOAT3 posision;
public:
	XMFLOAT2 mousepos;

	void Init();

	void Create();

	void Update(XMFLOAT3 pos,float hp);

	void UpdateHp(float hp);

	void Draw();

	void Finish();


	static UniqueBombHp* GetInstance()
	{
		static UniqueBombHp instance;
		return &instance;
	}


private:


	void Sethpout(CBillBoard* tex)
	{
		hpout = tex;
	}


	void Sethpin(CBillBoard* tex)
	{
		hpin = tex;
	}

};
