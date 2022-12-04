#pragma once
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

//*********************************************
//
// DirectInput�N���X
//
//*********************************************

// ***** ���� ***** //
// ���삪�s����ł� //

// DirectInput�̓��͎��
enum DI_CON {
	XPOS,       // LXPOS
	YPOS,       // LYPOS
	ZPOS,       // RXPOS
	RPOS,       // RYPOS
	UPOS,       // RTRG
	VPOS,       // LTRG
	DI_BTNS,
	POV,
	MAX_CON_DI,
};

// BTNS�̎�� ��PS5�R���g���[���[
enum DI_BTNS {
	DI_X,
	DI_A,
	DI_B,
	DI_Y,
	DI_L,
	DI_R,
	DI_LT,
	DI_RT,
	DI_SELECT, 
	DI_START,
	DI_L3,
	DI_R3,
	DI_PS,     // PS�{�^��
	DI_PAD,
	DI_MIC,    // �}�C�N�{�^��
	DI_BTNS_MAX,
};

// POV�̎��(�΂߂ɂ��ʂ̐��l�������Ă��邽�ߒ���)
enum DI_POV {
	POV_U,
	POV_UR, // �E��
	POV_R,
	POV_DR, // �E��
	POV_D,
	POV_DL, // ����
	POV_L,
	POV_UL, // ����
};

class DIController {
public:
	static void Update();                            // �R���g���[���[�̓��͏� game.cpp�ɋL��
	static bool GetButtonPress(int btns);            // �{�^���̓��͂𔻒肷��
	static bool GetButtonTrigger(int btns);          // �{�^���̓��͂�1�񂾂����肷��
	static bool GetStickPress(int stick, int rid);   // �X�e�B�b�N�̌X���𔻒肷��
	static bool GetStickTrigger(int stick, int rid); // �X�e�B�b�N�̌X����1�񂾂����肷��
	static bool GetTrgPress(int trg, int rid);       // �g���K�[�̉������݂𔻒肷��
	static bool GetTrgTrigger(int trg, int rid);     // �g���K�[�̉������݂�1�񂾂����肷��
	static bool GetPOVPress(int pov);                // �\���L�[�̓��͂𔻒肷��
	static bool GetPOVTrigger(int pov);              // �\���L�[�̓��͂�1�񂾂�	���肷��
private:
	static JOYINFOEX JoyConState;
	static int DICon[MAX_CON_DI];                    // ���t���[���̃L�[���
	static int DIConOld[MAX_CON_DI];                 // �O�t���[���̃L�[���
};