#include"S_Clear.h"
#include"Timing_UI.h"
#include"Notes.h"
#include"CCamera.h"
#include"CDirectInput.h"

void S_Clear::Initialize()
{/*
	Clearpng = new CTex();
	Clearpng->Init(Scean::g_texlist.at(2).cgname, Scean::g_texlist.at(2).vsfilename, Scean::g_texlist.at(2).psfilename);
	Clearpng->SetPos(XMFLOAT3(0.0f, 0.0f, 0.0f));
	Clearpng->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));



	Spacepng = new CTex();
	Spacepng->Init(Scean::g_texlist.at(3).cgname, Scean::g_texlist.at(3).vsfilename, Scean::g_texlist.at(3).psfilename);
	Spacepng->SetPos(XMFLOAT3(0.0f, -0.5f, 0.0f));
	Spacepng->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));*/
}

void S_Clear::Update()
{



}

void S_Clear::Draw()
{
	

}

void S_Clear::Release()
{
}

bool S_Clear::IsAbleChangeScean()
{


	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}
