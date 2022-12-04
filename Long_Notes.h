//#pragma once
//#include"Notes_Object.h"
//
//
//
//#define debuglog(a) std::cout<<a<<std::endl;
//
//class Long_Notes :public Notes_Object {
//private:
//
//public:
//
//	/// <summary>
//	/// テクスチャの大きさと場所をセット
//	/// </summary>
//	/// <param name="notes_LR">trueが右false が左のノーツ</param>
//	/// <param name="m_name">//短いノーツ長いノーツなどを格納</param>
//	/// <returns></returns>
//	bool Init(NOTES_NAME m_name);//ノーツの左右と何のノーツかを代入
//
//	void SetInit(bool NotesLR);
//
//	/// <summary>
//	/// ノーツオブジェクトで貰ってきたbpmの割合を元に線形補完する
//	/// </summary>
//	void Update();
//
//	void Draw();
//
//	void Finish();
//
//	/// <summary>
//	/// 右のノーツが中心あたりにいるならtrueを返す
//	/// </summary>
//	/// <returns></returns>
//	bool GetCenterNotes();
//
//	void Set_Notes_Sts(NOTES_STATUS sts)
//	{
//		m_sts = sts;
//	}
//
//
//	XMFLOAT2 rm_uv[4] = {
//		{1.0f,1.0f},
//		{0.0f,1.0f},
//		{1.0f,0.0f},
//		{0.0f,0.0f},
//	};
//
//};
//#pragma once
