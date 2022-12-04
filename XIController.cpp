#include "XIController.h"

#define STK_KAKUDO 327     // �X�e�B�b�N�̐��l��-100�`100�ɂ��邽�߂̒l
#define TRG_KAKUDO 2.55f   // �g���K�[�̐��l��0�`100�ɂ��邽�߂̒l
#define XI_NUM_MAX 65535   //	16�r�b�g�̍ő�l


int XIController::XICon[MAX_CON_XI];     // ���t���[���̐��l
int XIController::XIConOld[MAX_CON_XI];  // �O�t���[���̐��l

// ���̉�
XINPUT_STATE     XIController::ControllerState;
XINPUT_VIBRATION XIController::Vibration;

void XIController::Update()
{
	// �O�̃t���[���̃L�[��Ԃ�ۑ�
	memcpy_s(XIConOld, sizeof(XIConOld), XICon, sizeof(XICon));
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION)); // �k���鋭����0�ɂ���
	
	// �ǂ̃R���g���[���[�̏������邩 ��芸����1(0)�Ԗڂ̃R���g���[���[
	XInputGetState(0, &ControllerState);
	XInputSetState(0, &Vibration);

	// ���͂��ꂽ���l������
	XICon[LXPOS] = ControllerState.Gamepad.sThumbLX;
	XICon[LYPOS] = ControllerState.Gamepad.sThumbLY;
	XICon[RXPOS] = ControllerState.Gamepad.sThumbRX;
	XICon[RYPOS] = ControllerState.Gamepad.sThumbRY;
	XICon[LTRG] = ControllerState.Gamepad.bLeftTrigger;
	XICon[RTRG] = ControllerState.Gamepad.bRightTrigger;
	XICon[XI_BTNS] = ControllerState.Gamepad.wButtons;
}

// ����:(�{�^���̎��)
bool XIController::GetButtonPress(int btns)
{
	// �r�b�g�̘_���ςŉ�����������Ă��邩���f���Č��ʂ�Ԃ�
	return (XICon[XI_BTNS] >> btns) & 0x01;
}

bool XIController::GetButtonReleace(int btns)
{
	bool Flg = (XICon[XI_BTNS] >> btns) & 0x01;

	bool OldFlg = (XIConOld[XI_BTNS] >> btns) & 0x01;

	if (Flg == false && OldFlg == true)
	{
		return true;
	}
	return false;
	
}

// ����:(�{�^���̎��)
bool XIController::GetButtonTrigger(int btns)
{

	bool Flg = (XICon[XI_BTNS] >> btns) & 0x01;

	bool OldFlg = (XIConOld[XI_BTNS] >> btns) & 0x01;

	if (Flg == false && OldFlg == true) {
		return true;
	}

	return false;
}

// ����:(���E�X�e�B�b�N��X��Y, �p�x(-100�`100))
bool XIController::GetStickPress(int stick, int rid)
{
	if (stick > RYPOS || stick < LXPOS) {
		return false;
	}

	if (rid > 0) {
		return XICon[stick] / STK_KAKUDO >= rid;
	}

	else if (rid < 0) {
		return XICon[stick] / STK_KAKUDO <= rid;
	}
	else {
		return false;
	}
}


int XIController::GetStickRig(int stick)
{
	if (stick > RYPOS || stick < LXPOS) {
		return false;
	}
	// �R���g���[���[�̐��l / ���l��-100�`100�ɂ��邽�߂̐��l >= �X���銄��
	return XICon[stick] / STK_KAKUDO;
}


// ����:(���E�X�e�B�b�N��X��Y, �p�x(-100�`100))
bool XIController::GetStickTrigger(int stick, int rid)
{
	if (stick > RYPOS || stick < LXPOS) {
		return false;
	}

	if (rid > 0) {
		// �R���g���[���[�̐��l / ���l��-100�`100�ɂ��邽�߂̐��l >= �X���銄��
		return XICon[stick] / STK_KAKUDO >= rid && XIConOld[stick] / STK_KAKUDO < rid;
	}

	else if (rid < 0) {
		return XICon[stick] / STK_KAKUDO <= rid && XIConOld[stick] / STK_KAKUDO < rid;
	}
	else {
		return 0;
	}
}




// ����:(���E�g���K�[, �p�x(0�`100))
bool XIController::GetTrgPress(int trg, int rid)
{
	if (trg != LTRG && trg != RTRG) {
		return false;
	}

	return (float)rid <= (float)XICon[trg] / TRG_KAKUDO;
}

// ����:(���E�g���K�[, �p�x(0�`100))
bool XIController::GetTrgTrigger(int trg, int rid)
{
	if (trg != LTRG && trg != RTRG) {
		return false;
	}
	return (float)rid <= (float)XICon[trg] / TRG_KAKUDO && (float)rid > (float)XIConOld[trg] / TRG_KAKUDO;
}

// ����:(�k���鋭��)
void XIController::SetVibrationRight(int power)
{
	if (power < 0) {
		Vibration.wRightMotorSpeed = 0;
	}
	else if (power > XI_NUM_MAX) {
		Vibration.wRightMotorSpeed = XI_NUM_MAX;
	}
	else {
		Vibration.wRightMotorSpeed = power;
	}

	XInputSetState(0, &Vibration);
}

// ����:(�k���鋭��)
void XIController::SetVibrationLeft(int power)
{
	if (power < 0) {
		Vibration.wLeftMotorSpeed = 0;
	}
	else if (power > XI_NUM_MAX) {
		Vibration.wLeftMotorSpeed = XI_NUM_MAX;
	}
	else {
		Vibration.wLeftMotorSpeed = power;
	}

	XInputSetState(0, &Vibration);
}

