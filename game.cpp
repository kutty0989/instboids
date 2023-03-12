//=============================================================================
//
// �SGame�V�[������ [Game.cpp]
//
//=============================================================================

#include <cinttypes>
#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "Seiha.h"
#include"Game.h"
#include"IMgui/imgui.h"
#include"IMgui/imgui_impl_win32.h"
#include"IMgui/imgui_impl_dx11.h"
#include"gui.h"
#include"S_Title.h"
#include"S_Clear.h"
#include"XIController.h"
#include"Scean.h"
#include"CBillboardMgr.h"
#include"CTexMgr.h"
#include"InstanceModelMgr.h"

Scean* Game::mScean;

/// <summary>
/// �V�[��������
/// </summary>
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
	DirectX::XMFLOAT3 up(0, 1, 0);			// �J�����̏�����x�N�g��

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

/// <summary>
/// �C���v�b�g�X�V
/// </summary>
/// <param name="dt"></param>
void Game::GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
	XIController::Update();
}

/// <summary>
/// �Q�[���V�[���X�V
/// </summary>
/// <param name="dt"></param>
void Game::GameUpdate(uint64_t dt) {

	//FPS�\��GUI
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("FPS");
		ImGui::SetNextWindowSize(ImVec2(300, 400));
		float dlet = dt;
		dlet = 16.666 / dlet;
		dlet = 60 * dlet;
		ImGui::DragFloat("FPS", &dlet);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	//�V�[���J��
	switch (Game::GetInstance()->GAME_MODE)
	{
	case S_ID_TITLE_INI:
	{
		mScean = new S_Title();//�^�C�g���V�[���������ǂݍ���
		mScean->Initialize();
		Game::GetInstance()->GAME_MODE = S_ID_TITLE_UPDATE;

		break;
	}

	case S_ID_TITLE_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			Game::GetInstance()->GAME_MODE = S_ID_STAGE1_INI;//�f���V�[���ړ�
		}

		break;
	}
	//�f���V�[��������
	case S_ID_STAGE1_INI:
	{
		mScean = new Seiha();//�f���V�[���������ǂݍ���
		mScean->Initialize();
		Game::GetInstance()->GAME_MODE = S_ID_STAGE1_UPDATE;

		break;
	}
	//�f���V�[���X�V
	case S_ID_STAGE1_UPDATE:
	{
		mScean->Update(dt);
		if (mScean->IsAbleChangeScean())
		{
			mScean->Release();

			Game::GetInstance()->GAME_MODE = S_ID_TITLE_INI;
		}
		break;
	}

	}

}


/// <summary>
/// �Q�[���b�`��
/// </summary>
/// <param name="dt"></param>
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

	//ImGui�̕`����s�Ăяo����������
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// �����܂�
	// Dx��present�֐��Ăяo��
	// �`��㏈��
	DX11AfterRender();
}

/// <summary>
/// �I������
/// </summary>
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