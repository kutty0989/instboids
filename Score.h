#pragma once
#include"CTex.h"
#include"instan.h"

class Score {
private:



	CTex* m_texture;//�e�N�X�`��
	//DXManager* m_texture;//�e�N�X�`��
	//InstanceModel* m_model;//�e�N�X�`��

	bool mIsInstancing = true;
public:
	int drawnum;

	XMFLOAT2 mousepos;

	void Init(XMFLOAT3 pos);

	void Update(int num);

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


