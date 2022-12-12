#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "Seiha.h"
#include"game.h"
#include"IMgui/imgui.h"
#include"IMgui/imgui_impl_win32.h"
#include"IMgui/imgui_impl_dx11.h"
#include"gui.h"
#include"S_Title.h"
#include"S_Clear.h"
#include"XIController.h"

/// <summary>
/// �Q�[���̃V�[��
/// </summary>
enum GAME_SCEAN_ID
{
	S_ID_TITLE_INI,
	S_ID_TITLE_UPDATE,
	S_ID_STAGE1_INI,
	S_ID_STAGE1_UPDATE,
	S_ID_GAMEOVER_INI,
	S_ID_GAMEOVER_UPDATE,
	S_ID_CLEAR_INI,
	S_ID_CLEAR_UPDATE,


	S_ID_MAX
};

GAME_SCEAN_ID GAME_MODE = S_ID_STAGE1_INI;//�����̃Q�[���V�[��
GAME_SCEAN_ID B_GAME_MODE;//�O��̃Q�[�����[�h
Scean* Game::mScean;


bool StageClear_Flg = false;//update�Ō��ʂ�bool�ŕԂ��Ă��炢���U���g��

void Game::GameInit() {
	// DX11������
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,//��ʃT�C�Y
		Application::CLIENT_HEIGHT,
		false);

	// ��������ImGui������------------
// �o�[�W�����`�F�b�N
	IMGUI_CHECKVERSION();

	// ImGui�̃R���e�L�X�g�쐬
	ImGui::CreateContext();

	// ImGui��IO�擾
	ImGuiIO& io = ImGui::GetIO();

	// Win32�̏��������e��ImGui������
	// �A�v���P�[�V������hWnd��n��
	bool sts = ImGui_ImplWin32_Init(Application::Instance()->GetHWnd());

	// TODO: �G���[�`�F�b�N

		// DX11�̏��������e��ImGui������
	sts = ImGui_ImplDX11_Init(GetDX11Device(), GetDX11DeviceContext());

	// TODO: �G���[�`�F�b�N

// �X�^�C�����_�[�N�ɓ���
	ImGui::StyleColorsDark();
	// �����܂�ImGui������----------------


	// �J�������K�v
	DirectX::XMFLOAT3 eye(0, 100, -50);		// �J�����̈ʒu
	DirectX::XMFLOAT3 lookat(0, -10, 0);		// �����_
	DirectX::XMFLOAT3 up(0,  1, 0);			// �J�����̏�����x�N�g��

	CCamera::GetInstance()->Init(
		10.0f,							// �j�A�N���b�v
		10000.0f,						// �t�@�[�N���b�v
		XM_PI / 5.0f,					// ����p
		static_cast<float>(Application::CLIENT_WIDTH),		// �X�N���[����
		static_cast<float>(Application::CLIENT_HEIGHT),		// �X�N���[���̍���
		eye, lookat, up);					// �J�����̃f�[�^

	// ���s�������Z�b�g
	DX11LightInit(
		DirectX::XMFLOAT4(0, 10, 1, 0));

	// DIRECTINPUT������
	CDirectInput::GetInstance().Init(
		Application::Instance()->GetHInst(),
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,			// �X�N���[����
		Application::CLIENT_HEIGHT			// �X�N���[���̍���
	);

	// �A���t�@�u�����h�L����
	TurnOnAlphablend();

	srand(GetTickCount());//�������ŏ��Ɉ�񂾂��ݒ�


}

void Game::GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
	XIController::Update();
}

void Game::GameUpdate(uint64_t dt) {

	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("FPS");
		ImGui::SetNextWindowSize(ImVec2(300, 400));
		float dlet = dt;
		dlet =16.666 /dlet;
		dlet = 60 * dlet;
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;
		ImGui::DragFloat("FPS", &dlet);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}


	switch (GAME_MODE)
	{
	case S_ID_TITLE_INI:
	{
		mScean = new S_Title();//�^�C�g���V�[���ǂݍ���
		mScean->Initialize();
		GAME_MODE = S_ID_TITLE_UPDATE;

		break;
	}

	case S_ID_TITLE_UPDATE:
	{
		mScean->Update(dt);


		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			GAME_MODE = S_ID_STAGE1_INI;
		}

		break;
	}

	case S_ID_STAGE1_INI:
	{
		mScean = new Seiha();
		mScean->Initialize();
		GAME_MODE = S_ID_STAGE1_UPDATE;

		break;
	}

	case S_ID_STAGE1_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			GAME_MODE = S_ID_CLEAR_INI;
		}
		break;
	}
	case S_ID_CLEAR_INI:
	{
		mScean = new S_Clear();
		mScean->Initialize();
		GAME_MODE = S_ID_CLEAR_UPDATE;

		break;
	}

	case S_ID_CLEAR_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			GAME_MODE = S_ID_TITLE_INI;
		}
		break;
	}

	
	}

	// �󒆐�X�V
	//AirFightUpdate();

}



void Game::GameRender(uint64_t dt) {

	float col[4] = { 1,0,0,1 };

	// �`��O����
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;

	// �v���W�F�N�V�����ϊ��s��擾
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// �r���[�ϊ��s����擾
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);



	mScean->Draw();
	
	// �e�X�g�\����������---------------------------------

	imgui::GetInstance()->draw();

	// �e�X�g�\�������܂�---------------------------------

	// ImGui�̕`����s�Ăяo����������
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// �����܂�
	// Dx��present�֐��Ăяo��
	// �`��㏈��
	DX11AfterRender();
}

void Game::GameDispose() {

	// ��������ImGui�̉������------------------
	// DX11�ɑ΂���ImGui�̏����I��
	ImGui_ImplDX11_Shutdown();
	// Win32�ɑ΂���ImGui�̏����I��
	ImGui_ImplWin32_Shutdown();
	// �R���e�L�X�g���폜
	ImGui::DestroyContext(ImGui::GetCurrentContext());
	// �����܂�ImGui�̉������------------------

	CTexMgr::GetInstance().Finalize();
	DX11Uninit();
}