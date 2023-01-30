#pragma once
#include"CTex.h"
#include"instan.h"

class Score {
private:

	int b_num = 0;
	XMFLOAT3 mypos;
	XMFLOAT3 bpos;

	XMFLOAT3 bscale;
	XMFLOAT3 myscale = {1.0f,1.0f,1.0f};

	bool rotate = false;
	int angle = 0;
	CTex* m_texture;//テクスチャ
	//DXManager* m_texture;//テクスチャ
	//InstanceModel* m_model;//テクスチャ

	bool mIsInstancing = true;
public:
	int drawnum;

	XMFLOAT2 mousepos;

	void Init(XMFLOAT3 pos);

	void Update(int num,int kurai);

	void Draw();

	void Finish();


	static Score* GetInstance()
	{
		static Score instance;
		return &instance;
	}



private:

	/*void SetTexture(DXManager* tex)
	{
		m_texture = tex;
	}*/
	void SetTexture(CTex* tex)
	{
		m_texture = tex;
	}
};


