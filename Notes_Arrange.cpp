//#include"Notes_Arrange.h"
//#include"CTexMgr.h"
//#include"Scean.h"
//#include"BoidsAI.h"
//#include"Notes_Data.h"
//#include<string.h>
//#include<stdio.h>
//#include"CDirectInput.h"
//
//#define debuglog(a) std::cout<<a<<std::endl;
//
//static bool a = false;//8�ڂ̃m�[�c��`�悷�邽�߂�
//
//void Notes_Arrange::Init()
//{
//	for (int i = 0; i < 20; i++)
//	{
//		DefaultNotesCreate();
//		
//	}
//	for (int i = 0; i < 6; i++)
//	{
//		ShortNotesCreate();
//		
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		LongNotesCreate();
//
//	}
//
//	for (int i = 1; i <= 8; i++)
//	{
//		NotesArray.emplace_back(NOTES_NAME::N_DEFAULT);
//	
//	}
//	nit = NotesArray.begin();
//
//}
//
//void Notes_Arrange::Update()
//{
//	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_1))
//	{
//		Arrannge_time = true;
//		NotesArray.resize(0);
//	}
//	
//	if (Arrannge_time == true)
//	{
//		
//		if (NotesArray.size() >= 8)
//		{
//			nit = NotesArray.begin();
//			Arrannge_time = false;
//		}
//		else if (NotesArray.size() < 8)
//		{
//			SetNotesBarance();
//		}
//	}
//
//	NotesUpdate();
//	
//	
//}
//
//void Notes_Arrange::SetNotesBarance()
//{
//	
//}
//
//
//void Notes_Arrange::NotesCreateTiming()
//{    
//
//	if (!Arrannge_time)
//	{
//		turn_flg = true;
//		
//		if ((*nit == NOTES_NAME::N_DEFAULT) && (turn_flg == true))
//		{
//	
//			for (auto it = g_defaultnotes.begin(); it != g_defaultnotes.end(); it++)
//			{
//				static int cnt = 0;//���E�̃m�[�c����邽�߂̕�
//				if ((*it)->IsLive() == NOTES_STATUS::DEAD)
//				{
//					if (cnt == 0)
//					{
//						(*it)->Set_Notes_Sts(NOTES_STATUS::LIVE);
//						(*it)->SetInit(true);						
//						cnt++;
//					}
//					else if (cnt == 1)
//					{
//						(*it)->Set_Notes_Sts(NOTES_STATUS::LIVE);
//						(*it)->SetInit(false);
//				
//
//						cnt = 0;
//						break;
//					}
//				}
//			}
//			nit++;
//			turn_flg = false;
//		}
//		
//		if (a == true)
//		{
//			nit = NotesArray.begin();//�Ō�̎���ptr�ɔz��̍ŏ���ptr������
//			a = false;
//		}
//	
//		if (nit == NotesArray.end() - 1)//���݂̃C�e���[�^���z��̍Ōゾ������
//		{
//		
//			a = true;
//		//	nit = NotesArray.begin();//�Ō�̎���ptr�ɔz��̍ŏ���ptr������
//		}
//		
//	}
//	
//}
//
//void Notes_Arrange::ShortNotesCreateTiming()
//{
//	auto it = g_shortnotes.begin();
//	while (it != g_shortnotes.end())
//	{
//		static int shortcnt = 0;//���E�̃m�[�c����邽�߂̕�
//		if ((*it)->IsLive() == NOTES_STATUS::DEAD)
//		{
//			if (shortcnt == 0)
//			{
//				
//				(*it)->Set_Notes_Sts(NOTES_STATUS::LIVE);
//				(*it)->SetInit(true);
//				shortcnt++;
//			}
//			else if (shortcnt == 1)
//			{
//				(*it)->Set_Notes_Sts(NOTES_STATUS::LIVE);
//				(*it)->SetInit(false);
//				shortcnt = 0;
//				break;
//			}
//		}
//		++it;
//	}
//}
//
//void Notes_Arrange::LongNotesCreateTiming()
//{
//	auto it = g_longnotes.begin();
//	while (it != g_longnotes.end())
//	{
//		static int longcnt = 0;//���E�̃m�[�c����邽�߂̕�
//		if ((*it)->IsLive() == NOTES_STATUS::DEAD)
//		{
//			if (longcnt == 0)
//			{
//				(*it)->Set_Notes_Sts(NOTES_STATUS::LIVE);
//				(*it)->SetInit(true);
//				longcnt++;
//			}
//			else if (longcnt == 1)
//			{
//				(*it)->Set_Notes_Sts(NOTES_STATUS::LIVE);
//				(*it)->SetInit(false);
//				longcnt = 0;
//				break;
//			}
//		}
//		++it;
//	}
//}
//
//void Notes_Arrange::NotesUpdate()
//{
//
//	//�S�X�V
//	for (auto& n : g_defaultnotes)
//	{
//		if (n->IsLive() == NOTES_STATUS::LIVE)
//		{
//			n->Update();
//		}
//	}
//	for (auto& n : g_shortnotes)
//	{
//		if (n->IsLive() == NOTES_STATUS::LIVE)
//		{
//			n->Update();
//		}
//	}
//	for (auto& n : g_longnotes)
//	{
//		if (n->IsLive() == NOTES_STATUS::LIVE)
//		{
//			n->Update();
//		}
//	}
//}
//
//void Notes_Arrange::NotesDraw()
//{
//	if (Arrannge_time == false)
//	{
//		//�S�`��
//		for (auto& n : g_defaultnotes) {
//			if (n->IsLive() == NOTES_STATUS::LIVE)
//			{
//				n->Draw();
//			}
//		}
//		//�S�`��
//		for (auto& n : g_shortnotes) {
//			if (n->IsLive() == NOTES_STATUS::LIVE)
//			{
//				n->Draw();
//			}
//		}
//		for (auto& n : g_longnotes) {
//			if (n->IsLive() == NOTES_STATUS::LIVE)
//			{
//				n->Draw();
//			}
//		}
//	}
//}
//
//void Notes_Arrange::DefaultNotesCreate()
//{
//	std::unique_ptr<Notes> t;
//	t = std::make_unique<Notes>();
//	//�Z���m�[�c�̃e�N�X�`�����Z�b�g
//	t->SetTexture(CTexMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_texlist[static_cast<int>(Scean::CGID::NOTES)].cgname));
//	t->Init(NOTES_NAME::N_DEFAULT);
//	//���j�[�N�|�C���^�[�Ȃ̂ŃA�h���X��n��
//	g_defaultnotes.emplace_back(std::move(t));
//}
//
//void Notes_Arrange::LongNotesCreate()
//{
//	std::unique_ptr<Long_Notes> t;
//	t = std::make_unique<Long_Notes>();
//	//�Z���m�[�c�̃e�N�X�`�����Z�b�g
//	t->SetTexture(CTexMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_texlist[static_cast<int>(Scean::CGID::NOTES_LONG)].cgname));
//	t->Init(NOTES_NAME::N_LONG);
//	//���j�[�N�|�C���^�[�Ȃ̂ŃA�h���X��n��
//	g_longnotes.emplace_back(std::move(t));
//}
//
//void Notes_Arrange::ShortNotesCreate()
//{
//	std::unique_ptr<Short_Notes> t;
//	t = std::make_unique<Short_Notes>();
//	//�����O�m�[�c�̐擪�e�N�X�`�����Z�b�g
//	t->SetTexture(CTexMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_texlist[static_cast<int>(Scean::CGID::NOTES_SHORT)].cgname));
//	t->Init(NOTES_NAME::N_SHORT);
//	g_shortnotes.emplace_back(std::move(t));
//}
//
//
//void Notes_Arrange::UnInit()
//{
//	for (auto& e : g_defaultnotes)
//	{
//		if (e->m_sts == NOTES_STATUS::DEAD)
//		{
//			e->Finish();
//		}
//	}
//	for (auto& e : g_shortnotes)
//	{
//		if (e->m_sts == NOTES_STATUS::DEAD)
//		{
//			e->Finish();
//		}
//	}
//	for (auto& e : g_longnotes)
//	{
//		if (e->m_sts == NOTES_STATUS::DEAD)
//		{
//			e->Finish();
//		}
//	}
//
//}
//
//NOTES_NAME Notes_Arrange::GetCenter_NotesName()
//{
//	for (auto& e : g_defaultnotes)
//	{
//		if (e->GetCenterNotes())
//		{
//			return NOTES_NAME::N_DEFAULT;
//		}
//	}
//	for (auto& e : g_longnotes)
//	{
//		if (e->GetCenterNotes())
//		{
//			return NOTES_NAME::N_LONG;
//		}
//	}
//
//	return NOTES_NAME();
//}
