//#include"Long_Notes.h"
//#include"Notes_Arrange.h"
//#include"Bpm_Data.h"
//#include"XAudio2.h"
//#define debuglog(a) std::cout<<a<<std::endl;
//
//
//bool Long_Notes::Init(NOTES_NAME m_name)
//{
//	Notes_Object::Notes_Object_Initialize(m_texture);
//	n_name = m_name;
//
//
//	//if (m_name == NOTES_NAME::N_LONG_TOP)//ショートノーツのサイズ指定
//	//{
//	//	m_scale.x = 0.2f;
//	//	m_scale.y = 0.4f;
//	//	m_pos.y = 0.8f;
//	//	m_pos.x = 3.0f;
//	//	n_name = NOTES_NAME::N_LONG_TOP;
//	//}
//	//if (m_name == NOTES_NAME::N_LONG_BOT)//ショートノーツのサイズ指定
//	//{
//	//	m_scale.x = 0.2f;
//	//	m_scale.y = 0.4f;
//	//	m_pos.y = 0.8f;
//	//	m_pos.x = 3.0f;
//	//	n_name = NOTES_NAME::N_LONG_BOT;
//	//}
//	//if (m_name == NOTES_NAME::N_LONG_MID)//ロングノーツのサイズ指定
//	//{
//	//	m_scale.x = 3.0f;
//	//	m_scale.y = 1.7f;
//	//	m_pos.y = 0.8f;
//	//	m_pos.x = 1.0f;
//	//	m_pos.x = 3.0f;
//	//	n_name = NOTES_NAME::N_LONG_MID;
//	//}
//	return true;
//
//}
//
//void Long_Notes::SetInit(bool NotesLR)
//{
//	m_Alpha = 1.0f;
//	m_scale.x = 4.0f;
//	m_scale.y = 1.0f;
//	start_notes = (int)BPM_DATA::GetInstance()->GetISeconds();//ノーツが作られたタイミング時間を保存
//
//	if (NotesLR)
//	{
//		m_dir = NOTES_DIRECTION::LEFT;
//	}
//	else if (!NotesLR)
//	{
//		m_dir = NOTES_DIRECTION::RIGHT;
//	}
//
//	if (m_dir == NOTES_DIRECTION::LEFT)
//	{
//		m_uv[0] = rm_uv[0];
//		m_uv[1] = rm_uv[1];
//		m_uv[2] = rm_uv[2];
//		m_uv[3] = rm_uv[3];
//		m_pos.y = 0.8525f;
//		m_pos.x = -1.0f;
//	}
//	else if (m_dir == NOTES_DIRECTION::RIGHT)
//	{
//		XAudio::XA_Play(SOUND_LABEL_BGM004, 0.3f);
//		m_pos.y = 0.85f;
//		m_pos.x = 0.0f;
//	}
//}
//
//void Long_Notes::Draw()
//{
//	if (m_sts == NOTES_STATUS::LIVE) {//ノーツが生きてる時だけ描画
//		Notes_Object::Notes_Object_Draw(m_texture);
//	}
//}
//
////go 元の座標値
////to　行先の座標値
////ratio　現在の進行割合　0.0f～1.0f
//template<typename T>
//T LeapID(T _go, T _to, float _ratio)
//{
//	return _go * (1.0f - _ratio) + _to * (T)_ratio;
//}
//
//void Long_Notes::Update()
//{
//
//	float notesa = Notes_Object::Notes_Object_Update();
//
//	if (m_dir == NOTES_DIRECTION::LEFT)
//	{
//		m_pos.x = LeapID<float>(-1.0f, 1.0f, notesa);//線形補完　画面の右端から真ん中に
//
//		if (m_pos.x >= -0.70f)
//		{
//			m_sts = NOTES_STATUS::DEAD;
//		}
//	}
//
//	if (m_dir == NOTES_DIRECTION::RIGHT)
//	{
//		//	float time = CalcHitStop(notesa, 0.1f, 0.2f, 0.01f);//線形補完　画面の右端から真ん中に
//		m_pos.x = LeapID<float>(-1.0f, -3.0f, notesa);//線形補完　画面の左端から真ん中に
//		//m_pos.x *= time;
//		if (m_pos.x <= -1.3f)
//		{
//			m_sts = NOTES_STATUS::DEAD;
//		}
//	}
//
//	if (m_Alpha <= 0.0f)
//	{
//		m_sts = NOTES_STATUS::DEAD;
//	}
//
//	/// <summary>
//	/// ノーツをリセットしたときに、描画、実行していたもののループを外す
//	/// </summary>
//	if (Notes_Arrange::GetInstance()->GetArrangeFlg() == true)
//	{
//		m_sts = NOTES_STATUS::DEAD;
//	}
//
//	//float notesa = Notes_Object::Notes_Object_Update();
//
//	////debuglog(Player::GetInstance()->judge_flg);
//
//
//	//
//	//if ((m_dir == NOTES_DIRECTION::LEFT) && (n_name == NOTES_NAME::N_LONG_MID))
//	//{
//	//	m_pos.x = LeapID<float>(-1.0f, 1.0f, notesa);
//	//	if (m_pos.x >= 0.35f)
//	//	{
//	//		m_sts = NOTES_STATUS::DEAD;
//	//	}
//	//}
//	//if ((m_dir == NOTES_DIRECTION::RIGHT) && (n_name == NOTES_NAME::N_LONG_MID))
//	//{
//	//	m_pos.x = LeapID<float>(1.0f, -1.0f, notesa);
//	//	if (m_pos.x <= -0.35f)
//	//	{
//	//		m_sts = NOTES_STATUS::DEAD;
//	//	}
//	//}
//	//if ((m_dir == NOTES_DIRECTION::LEFT) && (n_name == NOTES_NAME::N_LONG_BOT))
//	//{
//	//	m_pos.x = LeapID<float>(-1.0f, 1.0f, notesa);
//	//	if (m_pos.x >= 0.35f)
//	//	{
//	//		m_sts = NOTES_STATUS::DEAD;
//	//	}
//	//}
//	//if ((m_dir == NOTES_DIRECTION::RIGHT) && (n_name == NOTES_NAME::N_LONG_BOT))
//	//{
//	//	m_pos.x = LeapID<float>(1.0f, -1.0f, notesa);
//	//	if (m_pos.x <= -0.35f)
//	//	{
//	//		m_sts = NOTES_STATUS::DEAD;
//	//	}
//	//}
//	//if ((m_dir == NOTES_DIRECTION::LEFT) && (n_name == NOTES_NAME::N_LONG_TOP))
//	//{
//	//	m_pos.x = LeapID<float>(-1.0f, 1.0f, notesa);
//	//	if (m_pos.x >= 0.35f)
//	//	{
//	//		m_sts = NOTES_STATUS::DEAD;
//	//	}
//	//}
//	//if ((m_dir == NOTES_DIRECTION::RIGHT) && (n_name == NOTES_NAME::N_LONG_TOP))
//	//{
//	//	m_pos.x = LeapID<float>(1.0f, -1.0f, notesa);
//	//	if (m_pos.x <= -0.35f)
//	//	{
//	//		m_sts = NOTES_STATUS::DEAD;
//	//	}
//	//}
//
//	///// <summary>
//	///// ノーツをリセットしたときに、描画、実行していたもののループを外す
//	///// </summary>
//	//if (Notes_Arrange::GetInstance()->GetArrangeFlg() == true)
//	//{
//	//	m_sts = NOTES_STATUS::DEAD;
//	//}
//
//
//}
//
//
//
//void Long_Notes::Finish()
//{
//	Notes_Object::Notes_Object_Finish(m_texture);
//}
//
//
//
//
//bool Long_Notes::GetCenterNotes()
//{
//	if ((m_dir == NOTES_DIRECTION::RIGHT) && (m_sts == NOTES_STATUS::LIVE))
//	{
//		if ((m_pos.x < 0.0f) && (m_pos.x > -0.15f))
//		{
//			return true;
//		}
//	}
//	return false;
//}
