//#pragma once
//#include<list>
//#include"Notes.h"
//#include<iostream>
//#include"Long_Notes.h"
//#include"short_notes.h"
//class Notes_Arrange
//{
//public:
//
//	void Init();
//	
//	/// <summary>
//	/// �m�[�c���ăZ�b�g������X�V���܂Ƃ߂čs��
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// �Z�b�g����ĂȂ��Ƃ��Ƀm�[�c���i�[����
//	/// </summary>
//	void SetNotesBarance();
//
//	/// <summary>
//	/// �S��ނ̃m�[�c�̍X�V
//	/// </summary>
//	void NotesUpdate();
//
//	/// <summary>
//	/// �S��ނ̃m�[�c��`��@seiha.cpp�ŌĂяo��
//	/// </summary>
//	void NotesDraw();
//
//	/// <summary>
//	/// BPM�̃^�C�~���O�Ŕz��̃m�[�c��init�@siha�ŌĂяo��
//	/// </summary>
//	void NotesCreateTiming();
//
//	void ShortNotesCreateTiming();
//
//	void LongNotesCreateTiming();
//
//	/// <summary>
//	/// �Z���m�[�c�m�[�c�̃e�N�X�`��ptr�����O�Ɋm��
//	/// </summary>
//	void ShortNotesCreate();
//
//	void DefaultNotesCreate();
//
//	void LongNotesCreate();
//	
//
//	/// <summary>
//	/// �����O�m�[�c�m�[�c�擪�̃e�N�X�`��ptr�����O�Ɋm��
//	/// </summary>
//	void LongNotesCreateTop();
//	
//	/// <summary>
//	/// �����O�m�[�c�m�[�c�^�񒆂̃e�N�X�`��ptr�����O�Ɋm��
//	/// </summary>
//	void LongNotesCreateMid();
//	
//
//	/// <summary>
//	/// �����O�m�[�c�m�[�c���̃e�N�X�`��ptr�����O�Ɋm��
//	/// </summary>
//	void LongNotesCreateBot();
//
//	void UnInit();
//
//
//	static Notes_Arrange* GetInstance()
//	{
//		static Notes_Arrange instance;
//		return &instance;
//	}
//
//	NOTES_NAME GetCenter_NotesName();
//
//
//	/// <summary>
///// �m�[�c���ăZ�b�g���Ă��邩�ǂ������f����t���O�m�F
///// </summary>
///// <returns>true�Ȃ�ăZ�b�g��</returns>
//	bool GetArrangeFlg()
//	{
//		return Arrannge_time;
//	}
//
//	/// <summary>
//	/// ���݂̃m�[�c�̔z��̃C�e���[�^
//	/// </summary>
//	/// <returns>NOTES_NAME��Ԃ�</returns>
//	NOTES_NAME GetNit()
//	{
//		return *nit;
//	}
//
//	/// <summary>
//	/// ���݂̃m�[�c�̔z��̃A�h���X
//	/// </summary>
//	/// <returns>NOTES_NAME��Ԃ�</returns>
//	std::vector<NOTES_NAME>::iterator GetAdress()
//	{
//		return nit;
//	}
//
//
//	/// <summary>
///// ���݂̃m�[�c�̔z��̃C�e���[�^�̈��
///// </summary>
///// <returns>NOTES_NAME��Ԃ�</returns>
//	NOTES_NAME GetNitPlusPlus(std::vector<NOTES_NAME>::iterator nit)
//	{
//		auto it = NotesArray.end() - 1;
//
//		if (nit != it)
//		{
//			nit++;
//		}
//		else
//		{
//			nit = NotesArray.begin();
//		}
//		return *nit;
//	}
//
//
//private:
//
//	//�f�t�H���g�m�[�c
//	std::list <std::unique_ptr<Notes>> g_defaultnotes;
//	//�����O�m�[�c�̐擪
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes_top;
//	
//	//�����O�m�[�c�̒���
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes_mid;
//	
//	//�����O�m�[�c�̖���
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes_bot;
//
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes;
//	
//	//�V���[�g�m�[�c
//	std::list <std::unique_ptr<Short_Notes>> g_shortnotes;
//
//	bool Arrannge_time = false;
//
//	std::vector<NOTES_NAME> NotesArray;//8�̃m�[�c�z��
//	
//	std::vector<NOTES_NAME>::iterator nit;
//
//	bool turn_flg = false;//�m�[�c�𐶐��������ǂ���
//
//	
//};