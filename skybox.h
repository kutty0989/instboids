#pragma once
#include"gameobject.h"
#include"CModel.h"
#include"dx11mathutil.h"
class SkyBox :GameObject
{
	CModel *m_skymodel;

public:

	bool Init();

	void Draw();


	void Update();

	void Finalize();

	void SetModel(CModel* model)
	{
		m_skymodel = model;
	}


};