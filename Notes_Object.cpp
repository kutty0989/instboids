//#include"Notes.h"
//#include"CCamera.h"
//#include"CDirectxGraphics.h"
//#include"BoidsAI.h"
//#include"Scean.h"
//#include"CTexMgr.h"
//#include"Notes_Arrange.h"
//#include"Bpm_Data.h"
//#define debuglog(a) std::cout<<a<<std::endl;
//
//
//bool Notes_Object::Notes_Object_Initialize(CTex* m_texture)
//{
//
//	//aa = &bb;
//	m_texture->Init(100, 100, XMFLOAT3(1.0f, 1.0f, 1.0f));
//
//	//if (notes_LR == false)//ノーツの左
//	//{
//	//	m_dir = NOTES_DIRECTION::LEFT;
//
//	//}
//	//else if (notes_LR == true)//ノーツの右
//	//{
//	//	m_dir = NOTES_DIRECTION::RIGHT;
//	//}
//
//	if (m_dir == NOTES_DIRECTION::LEFT)
//	{
//
//		m_uv[0] = { 1.0f,0.0f };
//		m_uv[1] = { 0.0f,0.0f };
//		m_uv[2] = { 1.0f,1.0f };
//		m_uv[3] = { 0.0f,1.0f };
//	}
//
//	start_notes = (int)BPM_DATA::GetInstance()->GetISeconds();//ノーツが作られたタイミング時間を保存
//
//	
//	return true;
//
//}
//
//void  Notes_Object::Notes_Object_Draw(CTex* m_texture)
//{
//		m_texture->SetPosition(m_pos.x,m_pos.y,m_pos.z);
//		m_texture->SetScale(m_scale.x, m_scale.y,m_scale.z);
//		m_texture->SetUV(m_uv);
//		m_texture->SetAlpha(m_Alpha);
//		m_texture->updateVertex(Application::CLIENT_WIDTH * 0.5f, Application::CLIENT_HEIGHT * 0.5f, XMFLOAT3(1.0f, 1.0f, 1.0f));
//	
//		m_texture->updateVbuffer();
//		ScissorLR();
//		m_texture->Draw();
//
//	
//
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
//float Notes_Object::Notes_Object_Update()
//{
//	float notesa;
//
//	//作られてから何bpm分経ったのかを出す
//	notesa = ((((int)BPM_DATA::GetInstance()->GetISeconds() - (int)start_notes)) / 6) % (int)BPM_DATA::GetInstance()->GetJudee_Seconds();
//	notesa = (int)notesa % 10000 / BPM_DATA::GetInstance()->GetJudee_Seconds();//100％当たりに
//	
//	return notesa;
//}
//
//
//
//void Notes_Object::Notes_Object_Finish(CTex* m_texture)
//{
//	m_texture->UnInit();
//}
//
//
//
//
