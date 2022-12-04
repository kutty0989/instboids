#include "DIController.h"

#define STK_POS 32767    // スティックの中心を0にするための値
#define STK_KAKUDO 327   // スティックの数値を-100～100にするための値
#define TRG_KAKUDO 655   // トリガーの数値を0～100にするための値
#define POV_NUM 4500     // POVを判定するための数値
#define DI_NUM_MAX 65535 //	16ビットの最大値

JOYINFOEX DIController::JoyConState;
int DIController::DICon[MAX_CON_DI];    // 現フレームの数値
int DIController::DIConOld[MAX_CON_DI]; // 前フレームの数値

void DIController::Update()
{

	JoyConState.dwSize = sizeof(JOYINFOEX);
	JoyConState.dwFlags = JOY_RETURNALL;

	// 前のフレームのキー状態を保存
	memcpy_s(DIConOld, sizeof(DIConOld), DICon, sizeof(DICon)); // どのコントローラーの情報を入れるか 取り敢えず1(0)番目のコントローラー

	// 入力された数値を入れる
	joyGetPosEx(JOYSTICKID2, &JoyConState);
	//JOYERR_PARMS
	//165
	DICon[XPOS] = JoyConState.dwXpos;
	DICon[YPOS] = JoyConState.dwYpos;
	DICon[ZPOS] = JoyConState.dwZpos;       // 右スティックの横
	DICon[RPOS] = JoyConState.dwRpos;       // 右スティックの縦(上がマイナス)
	DICon[UPOS] = JoyConState.dwUpos;       // 右トリガーの押し込み具合
	DICon[VPOS] = JoyConState.dwVpos;       // 左トリガーの押し込み具合
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
	// ※YPOS,RPOSはXInputと向きが逆なことに注意
	// XInput 下がマイナス 

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
