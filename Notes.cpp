//#include"Notes.h"
//#include"Bpm_Data.h"
//#include"Notes_Arrange.h"
//#define debuglog(a) std::cout<<a<<std::endl;
//
//
//bool Notes::Init( NOTES_NAME m_name)
//{
//
//	Notes_Object::Notes_Object_Initialize(m_texture);
//
//	n_name = m_name;
//	return true;
//
//}
//
//void Notes::SetInit(bool notesLR)
//{
//	if (notesLR)
//	{
//		m_dir = NOTES_DIRECTION::LEFT;
//	}
//	else if (!notesLR)
//	{
//		m_dir = NOTES_DIRECTION::RIGHT;
//	}
//
//	start_notes = (int)BPM_DATA::GetInstance()->GetISeconds();//�m�[�c�����ꂽ�^�C�~���O���Ԃ�ۑ�
//
//	m_scale.x = 2.0f;
//	m_scale.y = 1.0f;
//	m_pos.y = 0.85f;
//	m_pos.x = 3.0f;
//
//}
//
//
//
//void Notes::Draw()
//{
//		Notes_Object::Notes_Object_Draw(m_texture);
//}
//
////go ���̍��W�l
////to�@�s��̍��W�l
////ratio�@���݂̐i�s�����@0.0f�`1.0f
//template<typename T>
//T LeapID(T _go, T _to, float _ratio)
//{
//	return _go * (1.0f - _ratio) + _to * (T)_ratio;
//}
//
//float CalcHitStop(float t, float t0, float t1, float k) {
//	if (t < t0) { return t; }
//	if (t0 <= t && t <= t1) { return k * (t - t0) + t0; }
//	return ((1.0f - k * (t1 - t0) - t0) / (1.0f - t1)) * (t - t1) + (k * (t1 - t0) + t0);
//}
//
//
//void Notes::Update()
//{
//	float notesa = Notes_Object::Notes_Object_Update();
//
//	if (m_dir == NOTES_DIRECTION::LEFT)
//	{
//		m_pos.x = LeapID<float>(-1.0f, 1.0f, notesa);//���`�⊮�@��ʂ̉E�[����^�񒆂�
//		
//		if (m_pos.x >= 0.35f)
//		{
//			m_sts = NOTES_STATUS::DEAD;
//		}
//	}
//
//	if (m_dir == NOTES_DIRECTION::RIGHT)
//	{
////	float time = CalcHitStop(notesa, 0.1f, 0.2f, 0.01f);//���`�⊮�@��ʂ̉E�[����^�񒆂�
//	m_pos.x = LeapID<float>(1.0f, -1.0f, notesa);//���`�⊮�@��ʂ̍��[����^�񒆂�
//	//m_pos.x *= time;
//		if (m_pos.x <= -0.35f)
//		{
//			m_sts = NOTES_STATUS::DEAD;
//		}
//
//	}
//
//
//	/// <summary>
//	/// �m�[�c�����Z�b�g�����Ƃ��ɁA�`��A���s���Ă������̂̃��[�v���O��
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
//void Notes::Finish()
//{
//	Notes_Object::Notes_Object_Finish(m_texture);
//}
//
//
//bool Notes::GetCenterNotes()
//{
//	if ((m_dir == NOTES_DIRECTION::RIGHT) && (m_sts == NOTES_STATUS::LIVE))
//	{
//		if ((m_pos.x < 0.05f) && (m_pos.x > -0.1f))
//		{
//			return true;
//		}
//
//	}
//	return false;
//}
//
//
