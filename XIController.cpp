#include "XIController.h"

#define STK_KAKUDO 327     // スティックの数値を-100～100にするための値
#define TRG_KAKUDO 2.55f   // トリガーの数値を0～100にするための値
#define XI_NUM_MAX 65535   //	16ビットの最大値


int XIController::XICon[MAX_CON_XI];     // 現フレームの数値
int XIController::XIConOld[MAX_CON_XI];  // 前フレームの数値

// 実体化
XINPUT_STATE     XIController::ControllerState;
XINPUT_VIBRATION XIController::Vibration;

void XIController::Update()
{
	// 前のフレームのキー状態を保存
	memcpy_s(XIConOld, sizeof(XIConOld), XICon, sizeof(XICon));
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION)); // 震える強さを0にする
	
	// どのコントローラーの情報を入れるか 取り敢えず1(0)番目のコントローラー
	XInputGetState(0, &ControllerState);
	XInputSetState(0, &Vibration);

	// 入力された数値を入れる
	XICon[LXPOS] = ControllerState.Gamepad.sThumbLX;
	XICon[LYPOS] = ControllerState.Gamepad.sThumbLY;
	XICon[RXPOS] = ControllerState.Gamepad.sThumbRX;
	XICon[RYPOS] = ControllerState.Gamepad.sThumbRY;
	XICon[LTRG] = ControllerState.Gamepad.bLeftTrigger;
	XICon[RTRG] = ControllerState.Gamepad.bRightTrigger;
	XICon[XI_BTNS] = ControllerState.Gamepad.wButtons;
}

// 引数:(ボタンの種類)
bool XIController::GetButtonPress(int btns)
{
	// ビットの論理積で何処が押されているか判断して結果を返す
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

// 引数:(ボタンの種類)
bool XIController::GetButtonTrigger(int btns)
{

	bool Flg = (XICon[XI_BTNS] >> btns) & 0x01;

	bool OldFlg = (XIConOld[XI_BTNS] >> btns) & 0x01;

	if (Flg == false && OldFlg == true) {
		return true;
	}

	return false;
}

// 引数:(左右スティックのXかY, 角度(-100～100))
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
	// コントローラーの数値 / 数値を-100～100にするための数値 >= 傾ける割合
	return XICon[stick] / STK_KAKUDO;
}


// 引数:(左右スティックのXかY, 角度(-100～100))
bool XIController::GetStickTrigger(int stick, int rid)
{
	if (stick > RYPOS || stick < LXPOS) {
		return false;
	}

	if (rid > 0) {
		// コントローラーの数値 / 数値を-100～100にするための数値 >= 傾ける割合
		return XICon[stick] / STK_KAKUDO >= rid && XIConOld[stick] / STK_KAKUDO < rid;
	}

	else if (rid < 0) {
		return XICon[stick] / STK_KAKUDO <= rid && XIConOld[stick] / STK_KAKUDO < rid;
	}
	else {
		return 0;
	}
}




// 引数:(左右トリガー, 角度(0～100))
bool XIController::GetTrgPress(int trg, int rid)
{
	if (trg != LTRG && trg != RTRG) {
		return false;
	}

	return (float)rid <= (float)XICon[trg] / TRG_KAKUDO;
}

// 引数:(左右トリガー, 角度(0～100))
bool XIController::GetTrgTrigger(int trg, int rid)
{
	if (trg != LTRG && trg != RTRG) {
		return false;
	}
	return (float)rid <= (float)XICon[trg] / TRG_KAKUDO && (float)rid > (float)XIConOld[trg] / TRG_KAKUDO;
}

// 引数:(震える強さ)
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

// 引数:(震える強さ)
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

