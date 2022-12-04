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
//	/// ノーツを再セットしたり更新をまとめて行う
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// セットされてないときにノーツを格納する
//	/// </summary>
//	void SetNotesBarance();
//
//	/// <summary>
//	/// 全種類のノーツの更新
//	/// </summary>
//	void NotesUpdate();
//
//	/// <summary>
//	/// 全種類のノーツを描画　seiha.cppで呼び出し
//	/// </summary>
//	void NotesDraw();
//
//	/// <summary>
//	/// BPMのタイミングで配列のノーツをinit　sihaで呼び出し
//	/// </summary>
//	void NotesCreateTiming();
//
//	void ShortNotesCreateTiming();
//
//	void LongNotesCreateTiming();
//
//	/// <summary>
//	/// 短いノーツノーツのテクスチャptrを事前に確保
//	/// </summary>
//	void ShortNotesCreate();
//
//	void DefaultNotesCreate();
//
//	void LongNotesCreate();
//	
//
//	/// <summary>
//	/// ロングノーツノーツ先頭のテクスチャptrを事前に確保
//	/// </summary>
//	void LongNotesCreateTop();
//	
//	/// <summary>
//	/// ロングノーツノーツ真ん中のテクスチャptrを事前に確保
//	/// </summary>
//	void LongNotesCreateMid();
//	
//
//	/// <summary>
//	/// ロングノーツノーツ後ろのテクスチャptrを事前に確保
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
///// ノーツを再セットしているかどうか判断するフラグ確認
///// </summary>
///// <returns>trueなら再セット中</returns>
//	bool GetArrangeFlg()
//	{
//		return Arrannge_time;
//	}
//
//	/// <summary>
//	/// 現在のノーツの配列のイテレータ
//	/// </summary>
//	/// <returns>NOTES_NAMEを返す</returns>
//	NOTES_NAME GetNit()
//	{
//		return *nit;
//	}
//
//	/// <summary>
//	/// 現在のノーツの配列のアドレス
//	/// </summary>
//	/// <returns>NOTES_NAMEを返す</returns>
//	std::vector<NOTES_NAME>::iterator GetAdress()
//	{
//		return nit;
//	}
//
//
//	/// <summary>
///// 現在のノーツの配列のイテレータの一つ次
///// </summary>
///// <returns>NOTES_NAMEを返す</returns>
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
//	//デフォルトノーツ
//	std::list <std::unique_ptr<Notes>> g_defaultnotes;
//	//ロングノーツの先頭
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes_top;
//	
//	//ロングノーツの中央
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes_mid;
//	
//	//ロングノーツの末尾
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes_bot;
//
//	std::list <std::unique_ptr<Long_Notes>> g_longnotes;
//	
//	//ショートノーツ
//	std::list <std::unique_ptr<Short_Notes>> g_shortnotes;
//
//	bool Arrannge_time = false;
//
//	std::vector<NOTES_NAME> NotesArray;//8個のノーツ配列
//	
//	std::vector<NOTES_NAME>::iterator nit;
//
//	bool turn_flg = false;//ノーツを生成したかどうか
//
//	
//};