#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

//*********************************************
//
// XInputクラス ver1.3.1
// by 川中悠吾 2022/02/14
//
//*********************************************

// ver1.1　：振動追加
// ver1.2　：GetButtonTrigger修正
// ver1.3　：GetTrgTrigger修正
// ver1.3.1：振動修正

// XInputの入力種類
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

// BTNSの種類
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

// コントローラークラス
class XIController {
public:
	static void Update();                            // コントローラーの入力状況 game.cppに記入
	static bool GetButtonPress(int btns);            // ボタンの入力の有無
	static bool GetButtonReleace(int btns);           // ボタンを離したかの有無
	static bool GetButtonTrigger(int btns);          // ボタンの入力の有無1回のみ
	static bool GetStickPress(int stick, int rid);   // スティックの傾きを判定する
	static bool GetStickTrigger(int stick, int rid); // スティックの傾きを1回だけ判定する
	static bool GetTrgPress(int trg, int rid);       // トリガーの押し込みを判定する
	static bool GetTrgTrigger(int trg, int rid);     // トリガーの押し込みを1回だけ判定する
	static void SetVibrationRight(int power);        // 右側のモーターを振動させる
	static void SetVibrationLeft(int power);         // 左側のモーターを振動させる

	static int GetStickRig(int stick);        //トリガー傾きを返す。

private:
	static XINPUT_STATE ControllerState;             // コントローラー情報
	static XINPUT_VIBRATION Vibration;               // コントローラーの振動
	static int XICon[MAX_CON_XI];                    // 現フレームのキー情報
	static int XIConOld[MAX_CON_XI];                 // 前フレームのキー情報
};