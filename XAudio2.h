#pragma once
#pragma once
//=============================================================================
//
// サウンド処理 [XAudio2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	//	BGM
	SOUND_LABEL_BGM000 = 0,		// サンプルBGM
	SOUND_LABEL_BGM001,			// 制作BGM
	SOUND_LABEL_BGM002,			// 制作BGM
	SOUND_LABEL_BGM003,			// 制作BGM
	SOUND_LABEL_BGM004,			// 制作BGM

	SOUND_LABEL_MAX,
} SOUND_LABEL;

class XAudio
{
public:

	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	XAudio();
	static HRESULT XA_Initialize(void);	//サウンドライブラリを初期化する　→　アプリ内で1回だけ呼ぶ
	static void XA_Release(void);	// サウンドライブラリを解放する　→　アプリ内1回だけ呼ぶ、サウンド使わなくなる
	static void XA_Play(SOUND_LABEL label);		// 指定したサウンドを再生する
	static void XA_Play(SOUND_LABEL label, float);	// 指定したサウンドを再生・音量調整する
	//static void XA_Play(SOUND_LABEL label, float, float);	// 指定したサウンドを再生・音量調整する
	static void XA_Stop(SOUND_LABEL label);	// 指定したサウンドを停止する
	static void XA_Pause(SOUND_LABEL label);	// 指定したサウンドを一時停止する

	static float XA_GetSoundSeconds(SOUND_LABEL label);

private:
	//-----------------------------------------------------------------
	//    グローバル変数
	//-----------------------------------------------------------------
	static IXAudio2* g_pXAudio2;
	static IXAudio2MasteringVoice* g_pMasteringVoice;
	static IXAudio2SourceVoice* g_pSourceVoice[SOUND_LABEL_MAX];

	static WAVEFORMATEXTENSIBLE	g_wfx[SOUND_LABEL_MAX];			// WAVフォーマット
	static XAUDIO2_BUFFER			g_buffer[SOUND_LABEL_MAX];
	static BYTE* g_DataBuffer[SOUND_LABEL_MAX];
	//static float Volume;

};
#endif



