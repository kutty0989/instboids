//=============================================================================
//
// サウンド処理 [XAudio2.cpp]
//
//=============================================================================

#include "XAudio2.h"

IXAudio2* XAudio::g_pXAudio2 = NULL;
IXAudio2MasteringVoice* XAudio::g_pMasteringVoice = NULL;
IXAudio2SourceVoice* XAudio::g_pSourceVoice[SOUND_LABEL_MAX];

WAVEFORMATEXTENSIBLE    XAudio::g_wfx[SOUND_LABEL_MAX];            // WAVフォーマット
XAUDIO2_BUFFER            XAudio::g_buffer[SOUND_LABEL_MAX];
BYTE* XAudio::g_DataBuffer[SOUND_LABEL_MAX];

// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
} PARAM;

PARAM g_param[SOUND_LABEL_MAX] =
{
	
	{"assets/BGM/My_Song.wav",true},		// 制作BGM	0
	{"assets/BGM/My_Song_dark.wav",true},	// 制作BGM	1
	{"assets/BGM/Organ.wav",true},		// 制作BGM	2
	{"assets/BGM/hoisul.wav",false},		// 制作BGM	2
	{"assets/BGM/long_hoisul.wav",false},		// 制作BGM	2
	};

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//-----------------------------------------------------------------
//    プロトタイプ宣言
//-----------------------------------------------------------------
HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

XAudio::XAudio()
{
	IXAudio2* g_pXAudio2 = NULL;
	IXAudio2MasteringVoice* g_pMasteringVoice = NULL;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT XAudio::XA_Initialize()
{
	HRESULT      hr;

	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;

	// ＣＯＭの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&g_pXAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// 第三引数は、windowsでは無視
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// 本当６個の引数を持っている
	if (FAILED(hr)) {
		if (g_pXAudio2)	g_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(g_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
			return HRESULT_FROM_WIN32(GetLastError());
		}

		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &g_wfx[i], dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		g_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, g_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 	サブミットボイスで利用するサブミットバッファの設定
		g_buffer[i].AudioBytes = dwChunkSize;
		g_buffer[i].pAudioData = g_DataBuffer[i];
		g_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		if (g_param[i].bLoop)
			g_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			g_buffer[i].LoopCount = 0;

		g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[i], &(g_wfx[i].Format));
	}

	return hr;
}

//=============================================================================
// 開放処理
//=============================================================================
void XAudio::XA_Release(void)
{
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		if (g_pSourceVoice[i])
		{
			g_pSourceVoice[i]->Stop(0);
			g_pSourceVoice[i]->FlushSourceBuffers();
			g_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  g_DataBuffer[i];
		}
	}

	g_pMasteringVoice->DestroyVoice();

	if (g_pXAudio2) g_pXAudio2->Release();

	// ＣＯＭの破棄
	CoUninitialize();
}

void XAudio::XA_Play(SOUND_LABEL label)
{
	// ソースボイス作成
	g_pXAudio2->CreateSourceVoice(&(g_pSourceVoice[(int)label]), &(g_wfx[(int)label].Format));
	g_pSourceVoice[(int)label]->SubmitSourceBuffer(&(g_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファーを追加
	// 再生
	g_pSourceVoice[(int)label]->Start(0);
}

//=============================================================================
// 再生
//=============================================================================
void XAudio::XA_Play(SOUND_LABEL label, float Volume)
{
	// ソースボイス作成
	g_pXAudio2->CreateSourceVoice(&(g_pSourceVoice[(int)label]), &(g_wfx[(int)label].Format));
	g_pSourceVoice[(int)label]->SubmitSourceBuffer(&(g_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファーを追加
	g_pSourceVoice[(int)label]->SetVolume(Volume);
	// 再生
	g_pSourceVoice[(int)label]->Start(0);

}

//void XAudio::XA_Play(SOUND_LABEL label, float left, float right)
//{
//	int inchannels = 1;
//	int outchannels = 2;
//	float Volume[] = { left, right };
//
//	g_pXAudio2->CreateSourceVoice(&(g_pSourceVoice[(int)label]), &(g_wfx[(int)label].Format));
//	g_pSourceVoice[(int)label]->SubmitSourceBuffer(&(g_buffer[(int)label]));
//	g_pSourceVoice[(int)label]->SetOutputMatrix(NULL, inchannels, outchannels, Volume);
//
//	g_pSourceVoice[(int)label]->Start(0);
//}

//=============================================================================
// 停止
//=============================================================================
void XAudio::XA_Stop(SOUND_LABEL label)
{
	if (g_pSourceVoice[(int)label] == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	g_pSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		g_pSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// 一時停止
//=============================================================================
void XAudio::XA_Pause(SOUND_LABEL label)
{
	if (g_pSourceVoice[(int)label] == NULL) return;

	//再生中ではないかどうかチェックする
	XAUDIO2_VOICE_STATE xa2state;
	g_pSourceVoice[(int)label]->GetState(&xa2state);

	//	xa2state.BuffersQueuedが0じゃなければ再生中

	g_pSourceVoice[(int)label]->Stop(0);


	if (g_pSourceVoice[(int)label]->Stop(0)) {
		g_pSourceVoice[(int)label]->Start(0);
	}
	if (g_pSourceVoice[(int)label]->Start(0)) {
		g_pSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// 再生位置取得
//=============================================================================
float XAudio::XA_GetSoundSeconds(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE state;
	g_pSourceVoice[(int)label]->GetState(&state);

	float res = state.SamplesPlayed / (float)g_wfx[(int)label].Format.nSamplesPerSec;

	return res;
}


//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
