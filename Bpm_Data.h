//#pragma once
//#include    "XAudio2.h"
//
//#define BPM 100.0f
//
//
//class BPM_DATA
//{
//private:
//	XAudio audio;						//���y�Ȃ炷
//	float seconds = 0.0f;//�Ȃ̕b��
//	int iseconds = 0;//�Ȃ̕b��10000�{
//	int judge_seconds = 0;//��������10000�{
//	float beat = 0.0f;//�P������������̕b��
//	float bpm = BPM;
//
//	bool zs_flg = false;
//	bool m_sz_flg = false;
//public:
//	float GetSeconds()
//	{
//		return seconds;
//	}
//	float GetISeconds()
//	{
//		return iseconds;
//	}
//	float GetJudee_Seconds()
//	{
//		return judge_seconds;
//	}
//	float GetBeat()
//	{
//		return beat;
//	}
//	float GetBpm()
//	{
//		return bpm;
//	}
//
//	void BGM()
//	{
//		audio.XA_Play(SOUND_LABEL_BGM001, 0.85f);
//	}
//
//	void BPM_Count()
//	{
//		//�Ȃ̕b�������
//		seconds = audio.XA_GetSoundSeconds(SOUND_LABEL_BGM001);
//		iseconds = seconds * 10000;
//		beat = 60.0f / BPM;
//		judge_seconds = beat * 10000;//bpm��100�{
//
//		zs_flg = iseconds % judge_seconds <= 1000;//BPM�̃[������1000�܂ł̊�
//		m_sz_flg = iseconds %judge_seconds >= judge_seconds - 1000;
//	}
//
//	bool Get_zs()
//	{
//		return zs_flg;
//	}
//	bool Get_m_sz()
//	{
//		return m_sz_flg;
//	}
//
//	static BPM_DATA* GetInstance()
//	{
//		static BPM_DATA instance;
//		return &instance;
//	}
//	
//	bool Over_Notes_timing()
//	{
//		return (iseconds % judge_seconds > 1000);
//	
//	}
//	bool Zero_Create_Timing()
//	{
//		
//		return (iseconds % judge_seconds >= 0);
//	}
//
//private:
//
//};
//
