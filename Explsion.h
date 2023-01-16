#pragma once

#include"CBillBoard.h"
#include"CTex.h"
class Explsion {
private:
	XMINT2 part;

	CBillBoard* m_bill;
	XMFLOAT3 m_pos;
	int effectcnt = 0;
public:


	void Init();

	void Create(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Finish();

	static Explsion* GetInstance()
	{
		static Explsion instance;
		return &instance;
	}
	void SetTexture(CBillBoard* tex)
	{
		m_bill = tex;
	}




	//弾ステータス
	enum class Explsion_Sts {
		LIVE,
		DEAD
	};
	Explsion_Sts b_sts = Explsion_Sts::DEAD;


	bool isLive() {
		if (b_sts == Explsion_Sts::LIVE) {
			return true;
		}
		else {
			return false;
		}
	}
private:


};
