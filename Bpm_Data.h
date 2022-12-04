//#pragma once
//#include    "XAudio2.h"
//
//#define BPM 100.0f
//
//
//class BPM_DATA
//{
//private:
//	XAudio audio;						//‰¹Šy‚È‚ç‚·
//	float seconds = 0.0f;//‹È‚Ì•b”
//	int iseconds = 0;//‹È‚Ì•b‚Ì10000”{
//	int judge_seconds = 0;//‚‚‚‚‚Ì10000”{
//	float beat = 0.0f;//‚P‚‚‚‚“–‚½‚è‚Ì•b”
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
//		//‹È‚Ì•b”‚ğæ‚é
//		seconds = audio.XA_GetSoundSeconds(SOUND_LABEL_BGM001);
//		iseconds = seconds * 10000;
//		beat = 60.0f / BPM;
//		judge_seconds = beat * 10000;//bpm‚Ì100”{
//
//		zs_flg = iseconds % judge_seconds <= 1000;//BPM‚Ìƒ[ƒ‚©‚ç1000‚Ü‚Å‚ÌŠÔ
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
