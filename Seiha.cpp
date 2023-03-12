#include<string>
#include <chrono>
#include <iostream>
#include <time.h>
#include <ctime>
#include"BoidsAI.h"
#include"CCamera.h"
#include"skybox.h"
#include"BoundingSphere.h"
#include"updatespherecamera.h"
#include"CBillBoard.h"
#include"Stage.h"
#include"CLight.h"
#include"Seiha.h"
#include"Timing_UI.h"
#include"Notes_Arrange.h"
#include"BoidsAIMgr.h"
#include"MouseCircle.h"
#include"S_Title.h"
#include"BoidsHp.h"
#include"CBillboardMgr.h"
#include"billboardMgr.h"
#include"CModelInstance.h"
#include"enemy.h"
#include"InstanceModelMgr.h"
#include"TexMgr.h"
#include"game.h"

#define debuglog(a) std::cout<<a<<std::endl;

CModel			g_model;			// ��l�����f��
SkyBox  g_skybox;       // �w�i�I�u�W�F�N�g
CBillBoard fire;
CLight g_clight;


static bool turnflg;//�P�^�[���̐؂�ւ� true�s���ł���@false�s������
static bool createflg;//true ����Ă����@false �������_��
static bool saveflg;//true �܂������ĂȂ��@false ���łɂ���ꂽ
static bool notes_LR;//�m�[�c�̍��E�����邽�߂̕ϐ��@�����@���E�@

//-----------------------------------------------------------------
//    �ϐ��錾
//-----------------------------------------------------------------
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;//�~���b�p
using std::chrono::seconds;//���ԗp�ϐ�
using std::chrono::system_clock;


XMFLOAT4 color = { 1.0f,0.1f,0.1f,0.0f };
static bool init = false;
int maxcounttime = 10000;


//go ���̍��W�l
//to�@�s��̍��W�l
//ratio�@���݂̐i�s�����@0.0f�`1.0f

template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

/// <summary>
/// ����������
/// </summary>
void Seiha::Initialize() {

	//�Q�[���ň�x����
	if (init == false)
	{
		//�g�p���郂�f����S�ēǂݍ���
		for (int i = 0; i < g_modellist.size(); i++)
		{
			ModelMgr::GetInstance().LoadModel(
				g_modellist[i].modelname,
				g_modellist[i].vsfilenamename,
				g_modellist[i].psfilename,
				g_modellist[i].texfoldername
			);

		}
		//�g�p����C���X�^���X�p���f����S�ēǂݍ���
		for (int i = 0; i < g_modelinstancelist.size(); i++)
		{
			InstanceModelMgr::GetInstance().LoadInstanceModel(
				g_modelinstancelist[i].num,
				g_modelinstancelist[i].modelname,
				g_modelinstancelist[i].vsfilenamename,
				g_modelinstancelist[i].psfilename,
				g_modelinstancelist[i].texfoldername

			);

		}
		//�g�p����e�N�X�`���\��S�ēǂݍ���
		for (int i = 0; i < g_texlist.size(); i++)
		{
			CTexMgr::GetInstance().LoadModel(
				g_texlist[i].cgname,
				g_texlist[i].vsfilename,
				g_texlist[i].psfilename
			);
		}
		//�g�p����r���{�[�h��S�ēǂݍ���
		for (int i = 0; i < g_btexlist.size(); i++)
		{
			CBillBoardMgr::GetInstance().LoadModel(
				g_btexlist[i].cgname,
				g_btexlist[i].vsfilename,
				g_btexlist[i].psfilename
			);
		}
		init = true;
	}


	BoidsAIMgr::GetInstance()->Init();//AI�̑S������

	//�X�J�C�{�b�N�X�̏�����
	g_skybox.Init();
	g_skybox.SetModel(ModelMgr::GetInstance().GetModelPtr(g_modellist[static_cast<int>(MODELID::SKYDOME)].modelname));

	///�r���{�[�h�̑S������
	BillBoardMgr::GetInstance()->Init();

	//�n�`����
	g_ground.Init();

	//�}�E�XUI�̏�����
	MouseCircle::GetInstance()->Init();
	//�e�N�X�`���\�̑S������
	TexMgr::GetInstance()->Init();

}

/// <summary>
/// ��Ԃ�߂�
/// </summary>
void Seiha::Reset()
{
	turnflg = false;//�P�^�[���̐؂�ւ� true�s���ł���@false�s������
	createflg = false;//true ����Ă����@false �������_��
	saveflg = false;//true �܂������ĂȂ��@false ���łɂ���ꂽ
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="dt">�f���^�^�C��</param>
void  Seiha::Update(uint64_t dt) {
	//�_�C���N�g�C���v�b�g������
	CDirectInput::GetInstance().GetMouseState();

	//AI�̍X�V�֐�
	BoidsAIMgr::GetInstance()->Update();

	//�X�J�C�{�b�N�X�X�V
	g_skybox.Update();
	//�m�[�c�̍X�V
	Timing_UI::GetInstance()->Update();

	static bool music = true;//���y�Đ��t���O

	//�n�`�̍X�V
	g_ground.Update();

	//�J�����̈ʒu�Ɍ������Z�b�g
	XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	DX11LightUpdate(XMFLOAT4(eye.x, eye.y, eye.z, 1.0f));

	//�e�N�X�`���S�X�V
	TexMgr::GetInstance()->Update();

	//�}�E�X�T�[�N���X�V
	MouseCircle::GetInstance()->Update();

	//�J�����̈ʒu�X�V
	XMFLOAT4X4 mat;
	DX11MtxIdentity(mat);
	CCamera::GetInstance()->Update(mat);
	CCamera::GetInstance()->Update(BoidsAIMgr::GetInstance()->ImBoidsAI->GetMtx());

}

/// <summary>
/// �`��֐� 
/// </summary>
void Seiha::Draw()
{
	//�X�J�C�{�b�N�X�`��
	g_skybox.Draw();

	//�n�`�`��
	g_ground.Draw();

	//�r���{�[�h�S�`��
	BillBoardMgr::GetInstance()->Draw();

	//AI�S�`��
	BoidsAIMgr::GetInstance()->Draw();

	//�}�E�XUI�`��
	MouseCircle::GetInstance()->Draw();

	//�e�N�X�`���\�S�`��
	TexMgr::GetInstance()->Draw();
}

/// <summary>
/// �V�[���J�ڏ����֐�
/// </summary>
/// <returns></returns>
bool Seiha::IsAbleChangeScean()
{
	//�X�y�[�X�Ō���ύX
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}

void  Seiha::Release() {

	// �v���C���I������	
	BoidsAIMgr::GetInstance()->Finsh();
	//�X�J�C�{�b�N�X�I������
	g_skybox.Finalize();
	//�n�`�I������
	g_ground.Finalize();
	//�}�E�XUI�I������
	MouseCircle::GetInstance()->Finish();
	//�S�r���{�[�h�I������
	BillBoardMgr::GetInstance()->Finalize();
	//���f���S�I������
	ModelMgr::GetInstance().Finalize();
	//�e�N�X�`���I������
	TexMgr::GetInstance()->Finalize();
	//�m�[�c�I������
	Timing_UI::GetInstance()->Finish();

}

/// <summary>
/// �J�����s��v�Z
/// </summary>
void mtx()
{
	XMFLOAT4X4 vmtx;
	XMFLOAT4X4 pmtx;

	pmtx = CCamera::GetInstance()->GetProjectionMatrix();

	vmtx = CCamera::GetInstance()->GetCameraMatrix();

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, pmtx);

}

/// <summary>
/// UI�`�揈��
/// </summary>
void UIDraw() {
	//2D��`�`��
	TurnOffZbuffer();//���o�b�t�@���I�t

	static int loop = 0;
	loop++;

	static int idk = 0;
	if (loop % 30 == 29) {
		idk++;
	}
}