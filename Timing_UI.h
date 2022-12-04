#pragma once
#include"CTex.h"
class Timing_UI {
private:

	CTex* m_texture;//テクスチャ

public:

	void Init();

	void Update();

	void Draw();

	void Finish();


	static Timing_UI* GetInstance()
	{
		static Timing_UI instance;
		return &instance;
	}



private:

	void SetTexture(CTex* tex)
	{
		m_texture = tex;
	}

};
