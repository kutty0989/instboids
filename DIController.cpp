#include "DIController.h"

#define STK_POS 32767    // �X�e�B�b�N�̒��S��0�ɂ��邽�߂̒l
#define STK_KAKUDO 327   // �X�e�B�b�N�̐��l��-100�`100�ɂ��邽�߂̒l
#define TRG_KAKUDO 655   // �g���K�[�̐��l��0�`100�ɂ��邽�߂̒l
#define POV_NUM 4500     // POV�𔻒肷�邽�߂̐��l
#define DI_NUM_MAX 65535 //	16�r�b�g�̍ő�l

JOYINFOEX DIController::JoyConState;
int DIController::DICon[MAX_CON_DI];    // ���t���[���̐��l
int DIController::DIConOld[MAX_CON_DI]; // �O�t���[���̐��l

void DIController::Update()
{

	JoyConState.dwSize = sizeof(JOYINFOEX);
	JoyConState.dwFlags = JOY_RETURNALL;

	// �O�̃t���[���̃L�[��Ԃ�ۑ�
	memcpy_s(DIConOld, sizeof(DIConOld), DICon, sizeof(DICon)); // �ǂ̃R���g���[���[�̏������邩 ��芸����1(0)�Ԗڂ̃R���g���[���[

	// ���͂��ꂽ���l������
	joyGetPosEx(JOYSTICKID2, &JoyConState);
	//JOYERR_PARMS
	//165
	DICon[XPOS] = JoyConState.dwXpos;
	DICon[YPOS] = JoyConState.dwYpos;
	DICon[ZPOS] = JoyConState.dwZpos;       // �E�X�e�B�b�N�̉�
	DICon[RPOS] = JoyConState.dwRpos;       // �E�X�e�B�b�N�̏c(�オ�}�C�i�X)
	DICon[UPOS] = JoyConState.dwUpos;       // �E�g���K�[�̉������݋
	DICon[VPOS] = JoyConState.dwVpos;       // ���g���K�[�̉������݋
	DICon[DI_BTNS] = JoyConState.dwButtons;
	DICon[POV] = JoyConState.dwPOV;
}

bool DIController::GetButtonPress(int btns)
{
	return (DICon[DI_BTNS] >> btns) & 0x01;
}

bool DIController::GetButtonTrigger(int btns)
{

	bool Flg = (DICon[DI_BTNS] >> btns) & 0x01;
	bool OldFlg = (DIConOld[DI_BTNS] >> btns) & 0x01;

	if (Flg == true && OldFlg == false) {
		return true;
	}

	return false;
}

bool DIController::GetStickPress(int stick, int rid)
{
	// ��YPOS,RPOS��XInput�ƌ������t�Ȃ��Ƃɒ���
	// XInput �����}�C�i�X 

	if (stick > RPOS || stick < XPOS) {
		return false;
	}

	if (rid > 0) {
		return (DICon[stick] - STK_POS) / STK_KAKUDO >= rid;
	}

	else if (rid < 0) {
		return (DICon[stick] - STK_POS) / STK_KAKUDO <= rid;
	}
	else {
		return false;
	}
}

bool DIController::GetStickTrigger(int stick, int rid)
{
	if (stick > RPOS || stick < XPOS) {
		return false;
	}

	if (rid > 0) {
		return (DICon[stick] - STK_POS) / STK_KAKUDO >= rid && (DIConOld[stick] - STK_POS) / STK_KAKUDO < rid;
	}

	else if (rid < 0) {
		return (DICon[stick] - STK_POS) / STK_KAKUDO <= rid && (DIConOld[stick] - STK_POS) / STK_KAKUDO > rid;
	}
	else {
		return false;
	}
}

bool DIController::GetTrgPress(int trg, int rid)
{
	if (trg != UPOS && trg != VPOS) {
		return false;
	}

	return DICon[trg] / TRG_KAKUDO >= rid;
}

bool DIController::GetTrgTrigger(int trg, int rid)
{
	if (trg != UPOS && trg != VPOS) {
		return false;
	}

	return DICon[trg] / TRG_KAKUDO >= rid && DIConOld[trg] / TRG_KAKUDO == 0;
}

bool DIController::GetPOVPress(int pov)
{
	if (DICon[POV] == DI_NUM_MAX) {
		return false;
	}

	return DICon[POV] / POV_NUM == pov;
}

bool DIController::GetPOVTrigger(int pov)
{
	if (DICon[POV] == DI_NUM_MAX) {
		return false;
	}

	return DICon[POV] / POV_NUM == pov && DIConOld[POV] == DI_NUM_MAX;
}
