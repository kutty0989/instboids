#include "skybox.h"
#include"drawaxis.h"

bool SkyBox::Init()
{
	DX11MtxIdentity(m_mtx);


	return true;
}

void SkyBox::Draw()
{
	m_skymodel->Draw(m_mtx);

	
	//Draw();
}


void SkyBox::Update()
{
}

void SkyBox::Finalize()
{
	m_skymodel->Uninit();
}
