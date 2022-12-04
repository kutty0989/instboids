//#include"Short_Notes.h"
//#include"Bpm_Data.h"
//#include"Notes_Arrange.h"
//#include"XAudio2.h"
//#define debuglog(a) std::cout<<a<<std::endl;
//
//
//bool Short_Notes::Init( NOTES_NAME m_name)
//{
//
//	Notes_Object::Notes_Object_Initialize(m_texture);
//
//	n_name = m_name;
//
//
//	return true;
//
//}
//void Short_Notes::SetInit(bool NotesLR)
//{
//	
//	m_Alpha = 1.0f;
//	m_scale.x = 2.0f;
//	m_scale.y = 1.0f;
//	if (NotesLR)
//	{
//		
//		m_dir = NOTES_DIRECTION::LEFT;
//	}
//	else if (!NotesLR)
//	{
//		m_dir = NOTES_DIRECTION::RIGHT;
//	}
//
////	start_notes = (int)BPM_DATA::GetInstance()->GetISeconds();//ノーツが作られたタイミング時間を保存
//
//	if (m_dir == NOTES_DIRECTION::LEFT)
//	{
//		m_pos.y = 0.85f;
//		m_pos.x = 0.025f;
//	}
//	else if (m_dir == NOTES_DIRECTION::RIGHT)
//	{
//		m_pos.y = 0.85f;
//		m_pos.x = -0.025f;
//	}
//
//}
//
//
//
//
//void Short_Notes::Draw()
//{
//	Notes_Object::Notes_Object_Draw(m_texture);
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
//
//
//void Short_Notes::Update()
//{
//	
//	m_scale.x -= 0.03f;
//	m_scale.y -= 0.015f;
//	m_Alpha -= 0.015f;
//	if (m_dir == NOTES_DIRECTION::LEFT)
//	{
//		m_pos.x -= 0.01f;
//	}
//	if (m_dir == NOTES_DIRECTION::RIGHT)
//	{
//		m_pos.x += 0.01f;
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
//}
//
//
//
//void Short_Notes::Finish()
//{
//	
//	Notes_Object::Notes_Object_Finish(m_texture);
//}
//
