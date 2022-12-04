#pragma once
#include"CBillBoard.h"
#include"CTex.h"
class BoidsHp {
private:

	
	 CBillBoard* m_bill;

public:
	XMFLOAT2 mousepos;

	void Init();

	void Create();

	void Update(XMFLOAT3 pos);

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

};
