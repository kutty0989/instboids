#pragma once
#pragma once
#include"CBillBoard.h"
#include"CTex.h"
class Granate {
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
	
	static Granate* GetInstance()
	{
		static Granate instance;
		return &instance;
	}
	void SetTexture(CBillBoard* tex)
	{
		m_bill = tex;
	}




	//弾ステータス
	enum class Granate_Sts {
		LIVE,
		DEAD
	};
	Granate_Sts b_sts = Granate_Sts::DEAD;


	bool isLive() {
		if (b_sts == Granate_Sts::LIVE) {
			return true;
		}
		else {
			return false;
		}
	}
private:

	
};
