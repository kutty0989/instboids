#pragma once
#include"CTex.h"
#include"instan.h"
#include"instance.h"
#include"instancemodel.h"
class MouseCircle {
private:

	CTex* m_texture;//テクスチャ
	//DXManager* m_texture;//テクスチャ
	//InstanceModel* m_model;//テクスチャ

	bool mIsInstancing = true;
public:
	XMFLOAT2 mousepos;

	void Init();

	void Update();

	void Draw();

	void Finish();


	static MouseCircle* GetInstance()
	{
		static MouseCircle instance;
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
