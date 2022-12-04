#include"S_Title.h"
#include"Timing_UI.h"
#include"Notes.h"
#include"CCamera.h"
#include"CDirectInput.h"
#include"CTex.h"
#include "CLight.h"

//CModel			g_model;			// ��l�����f��



CModel			g_modelenemy;		// �G���f��
XMFLOAT4X4		g_mtxenemy;			// �G�̍s��


std::vector<COBB*> g_playerobblist;
std::vector<COBB*> g_enemyobblist;

void S_Title::Initialize()
{
	bool sts = false;

	// ASSIMP���g�p�������f���ǂݍ���
	// ASSIMP���g�p�������f���ǂݍ���
	//sts = g_model.Init("assets/Charcter.x", "shader/vsoneskin.fx", "shader/ps.fx",
	//	"");
	//if (!sts) {
	//	MessageBox(NULL, "load enemy model error", "error", MB_OK);
	//	
	//}
	//sts = g_model.Init("assets/Charcter.x", "shader/vsoneskin.fx", "shader/ps.fx",
	//	"");
	//if (!sts) {
	//	MessageBox(NULL, "load enemy model error", "error", MB_OK);
	//
	//}

	//// �P�ʍs��ɂ���
	//DX11MtxIdentity(g_mtxplayer);

	//// ASSIMP���g�p�����A�j���[�V�����̓ǂݍ���
	//sts = g_model.LoadAnimation("assets/Charcter.x");
	//if (!sts) {
	//	MessageBox(NULL, "load enemy animation error", "error", MB_OK);
	//	
	//}

		//�f�B�X�v���C�g�����g�}�b�s���O���������摜�̏�����
		//Titlepng = new CHeight_Map();
		//Titlepng->LoadTexture("assets/UI/taisetsu.png");
		//Titlepng->Init(100.0f, 100.0f, XMFLOAT3(1.0f, 1.0f, 1.0f),"Quad_Lo.obj","assets");
		//Titlepng->SetPosition(0.0f,0.0f, 0.0f);
		//Titlepng->SetScale(1.0f, 1.0f, 1.0f);

	
}

void S_Title::Update(uint64_t dt)
{
	// ���͂��󂯕t����
	CDirectInput::GetInstance().GetKeyBuffer();
	static XMFLOAT3 angle[2] = {
							{ -90.0f,0.0f,0.0f },
							{ -90.0f, 0.0f, 0.0f }
	};			// �p�x���

	static XMFLOAT3 trans[2] = {
		{ 0.0f,0.0f,0.0f, },
		{ 0.0f, 0.0f, 0.0f }
	};			// ���s�ړ���

	static float zpos = 0.0f;

	static unsigned int animno = 0;

	static int idx = 0;


	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
		angle[idx].y++;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
		angle[idx].y--;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F1)) {
		zpos += 1.0f;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_F2)) {
		zpos -= 1.0f;
	}


	//if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE)) {
	//	animno++;
	//	unsigned int animnummax = g_model.GetAnimationNum();
	//	if (animno >= animnummax) {
	//		animno = 0;
	//	}
	//}

	//if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_RETURN)) {
	//	g_model.ChangeAnimFileIdx();
	//}


	//DX11MakeWorldMatrix(g_mtxplayer, angle[0], trans[0]);
	//g_mtxplayer._43 = zpos;

	//g_model.Update(animno,			// �A�j���[�V�����ԍ�
	//	g_mtxplayer);				// ���f���\���ʒu�Ǝp��

	//DX11MakeWorldMatrix(g_mtxenemy, angle[1], trans[1]);
	//g_mtxenemy._43 = zpos;



	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
	//	Titlepng->g_hight += 10.01f;

	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
	//	Titlepng->g_hight -= 10.01f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
	//	Titlepng->g_angle += 1.01f;
	//}

	//if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
	//	Titlepng->g_angle -= 1.01f;
	//}

	//
//	CCamera::GetInstance()->Update(S_Title::GetInstance()->g_mtxplayer);

}

void S_Title::Draw()
{
	g_mtxplayer._11 = 1.0f;
	g_mtxplayer._22 = 1.0f;
	g_mtxplayer._33 = 1.0f;
	// ���f���`��

	// ���f���`��
	//g_model.Draw(g_mtxplayer);
	//�f�B�X�v���C�g�����g�}�b�s���O���������摜�̕`��
//	Titlepng->SetUV(CHeight_Map::GetInstance()->c_uv);
//	Titlepng->SetScale(1.0f, 1.0f, 1.0f);
//	Titlepng->SetRotation(90.0f,0.0f,0.0f);
//	Titlepng->updateVertex(100.0f, 100.0f, XMFLOAT3(1.0f, 0.5f, 1.0f));
//	Titlepng->updateVbuffer();
//	Titlepng->Draw();
//
//

}
void S_Title::Release()
{
	// ���f���I������
//	g_model.Uninit();



	// DirectX11 �O���t�B�b�N�X�I������
	CDirectXGraphics::GetInstance()->Exit();
}

bool S_Title::IsAbleChangeScean()
{
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_SPACE))
	{
		return true;
	}
	return false;
}
