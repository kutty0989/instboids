#pragma once
#pragma once
//=============================================================================
//
// �T�E���h���� [XAudio2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	//	BGM
	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	SOUND_LABEL_BGM001,			// ����BGM
	SOUND_LABEL_BGM002,			// ����BGM
	SOUND_LABEL_BGM003,			// ����BGM
	SOUND_LABEL_BGM004,			// ����BGM

	SOUND_LABEL_MAX,
} SOUND_LABEL;

class XAudio
{
public:

	//*****************************************************************************
	// �v���g�^�C�v�錾
	//*****************************************************************************
	XAudio();
	static HRESULT XA_Initialize(void);	//�T�E���h���C�u����������������@���@�A�v������1�񂾂��Ă�
	static void XA_Release(void);	// �T�E���h���C�u�������������@���@�A�v����1�񂾂��ĂԁA�T�E���h�g��Ȃ��Ȃ�
	static void XA_Play(SOUND_LABEL label);		// �w�肵���T�E���h���Đ�����
	static void XA_Play(SOUND_LABEL label, float);	// �w�肵���T�E���h���Đ��E���ʒ�������
	//static void XA_Play(SOUND_LABEL label, float, float);	// �w�肵���T�E���h���Đ��E���ʒ�������
	static void XA_Stop(SOUND_LABEL label);	// �w�肵���T�E���h���~����
	static void XA_Pause(SOUND_LABEL label);	// �w�肵���T�E���h���ꎞ��~����

	static float XA_GetSoundSeconds(SOUND_LABEL label);

private:
	//-----------------------------------------------------------------
	//    �O���[�o���ϐ�
	//-----------------------------------------------------------------
	static IXAudio2* g_pXAudio2;
	static IXAudio2MasteringVoice* g_pMasteringVoice;
	static IXAudio2SourceVoice* g_pSourceVoice[SOUND_LABEL_MAX];

	static WAVEFORMATEXTENSIBLE	g_wfx[SOUND_LABEL_MAX];			// WAV�t�H�[�}�b�g
	static XAUDIO2_BUFFER			g_buffer[SOUND_LABEL_MAX];
	static BYTE* g_DataBuffer[SOUND_LABEL_MAX];
	//static float Volume;

};
#endif



