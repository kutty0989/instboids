#pragma once
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

//*********************************************
//
// DirectInputクラス
//
//*********************************************

// ***** 注意 ***** //
// 動作が不安定です //

// DirectInputの入力種類
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

// BTNSの種類 ※PS5コントローラー
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
	DI_PS,     // PSボタン
	DI_PAD,
	DI_MIC,    // マイクボタン
	DI_BTNS_MAX,
};

// POVの種類(斜めにも個別の数値が入っているため注意)
enum DI_POV {
	POV_U,
	POV_UR, // 右上
	POV_R,
	POV_DR, // 右下
	POV_D,
	POV_DL, // 左下
	POV_L,
	POV_UL, // 左上
};

class DIController {
public:
	static void Update();                            // コントローラーの入力状況 game.cppに記入
	static bool GetButtonPress(int btns);            // ボタンの入力を判定する
	static bool GetButtonTrigger(int btns);          // ボタンの入力を1回だけ判定する
	static bool GetStickPress(int stick, int rid);   // スティックの傾きを判定する
	static bool GetStickTrigger(int stick, int rid); // スティックの傾きを1回だけ判定する
	static bool GetTrgPress(int trg, int rid);       // トリガーの押し込みを判定する
	static bool GetTrgTrigger(int trg, int rid);     // トリガーの押し込みを1回だけ判定する
	static bool GetPOVPress(int pov);                // 十字キーの入力を判定する
	static bool GetPOVTrigger(int pov);              // 十字キーの入力を1回だけ	判定する
private:
	static JOYINFOEX JoyConState;
	static int DICon[MAX_CON_DI];                    // 現フレームのキー情報
	static int DIConOld[MAX_CON_DI];                 // 前フレームのキー情報
};