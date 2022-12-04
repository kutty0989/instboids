#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

//*********************************************
//
// XInput�N���X ver1.3.1
// by �쒆�I�� 2022/02/14
//
//*********************************************

// ver1.1�@�F�U���ǉ�
// ver1.2�@�FGetButtonTrigger�C��
// ver1.3�@�FGetTrgTrigger�C��
// ver1.3.1�F�U���C��

// XInput�̓��͎��
enum XI_CON {
	LXPOS,
	LYPOS,
	RXPOS,
	RYPOS,
	LTRG,
	RTRG,
	XI_BTNS,
	MAX_CON_XI,
};

// BTNS�̎��
enum XI_BTNS {
	XI_POV_UP,
	XI_POV_DOWN,
	XI_POV_LEFT,
	XI_POV_RIGHT,
	XI_START,
	XI_SELECT,
	XI_L3,
	XI_R3,
	XI_L,
	XI_R,
	XI_NON_1,
	XI_NON_2,
	XI_A,
	XI_B,
	XI_X,
	XI_Y,
};

// �R���g���[���[�N���X
class XIController {
public:
	static void Update();                            // �R���g���[���[�̓��͏� game.cpp�ɋL��
	static bool GetButtonPress(int btns);            // �{�^���̓��̗͂L��
	static bool GetButtonReleace(int btns);           // �{�^���𗣂������̗L��
	static bool GetButtonTrigger(int btns);          // �{�^���̓��̗͂L��1��̂�
	static bool GetStickPress(int stick, int rid);   // �X�e�B�b�N�̌X���𔻒肷��
	static bool GetStickTrigger(int stick, int rid); // �X�e�B�b�N�̌X����1�񂾂����肷��
	static bool GetTrgPress(int trg, int rid);       // �g���K�[�̉������݂𔻒肷��
	static bool GetTrgTrigger(int trg, int rid);     // �g���K�[�̉������݂�1�񂾂����肷��
	static void SetVibrationRight(int power);        // �E���̃��[�^�[��U��������
	static void SetVibrationLeft(int power);         // �����̃��[�^�[��U��������

	static int GetStickRig(int stick);        //�g���K�[�X����Ԃ��B

private:
	static XINPUT_STATE ControllerState;             // �R���g���[���[���
	static XINPUT_VIBRATION Vibration;               // �R���g���[���[�̐U��
	static int XICon[MAX_CON_XI];                    // ���t���[���̃L�[���
	static int XIConOld[MAX_CON_XI];                 // �O�t���[���̃L�[���
};