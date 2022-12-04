//#pragma once
//#include"dx11mathutil.h"
//#include"DX11Settransform.h"
//#include"DX11util.h"
//#include"Notes_Data.h"
//#include<wrl/client.h>
//#include"vertexproto.h"
//#include"CTex.h"
//#include"Application.h"
//#define debuglog(a) std::cout<<a<<std::endl;
//
//
//
//
//class Notes_Object {
//public:
//
//	NOTES_DIRECTION m_dir;//ノーツの左右を判断
//	NOTES_NAME n_name;//何のノーツか
//	CTex* m_texture;//テクスチャ
//
//
//
//public:
//
//	int Change_UV = 0;//ノーツのuvを反転させる　longノーツ限定
//	float start_notes = 0.0f;//ノーツが生成された時の時間
//	NOTES_STATUS m_sts = NOTES_STATUS::DEAD;//ノーツのステータス
//	XMFLOAT3 m_pos = {};//ノーツのポジション
//	XMFLOAT3 m_scale = {};//ノーツのスケール
//	float m_Alpha = 1.0f;//アルファ値
//	float m_rot = 0.0f;//ノーツの回転
//
//	//ノーツのUV
//	XMFLOAT2 m_uv[4] = {
//		{0.0f,0.0f},
//		{1.0f,0.0f},
//		{0.0f,1.0f},
//		{1.0f,1.0f},
//	};
//
//
//
//	/// <summary>
//	/// テクスチャの大きさと場所をセット
//	/// </summary>
//	/// <param name="notes_LR">trueが右false が左のノーツ</param>
//	/// <param name="m_name">//短いノーツ長いノーツなどを格納</param>
//	/// <returns></returns>
//	bool Notes_Object_Initialize( CTex* m_texture);//ノーツの左右と何のノーツかを代入
//
//   /// <summary>
//   /// BPMの割合をfloat値で返す　移動の線形補完で使う
//   /// </summary>
//   /// <returns></returns>
//	float Notes_Object_Update();
//
//	/// <summary>
//	/// CTexにあるセット関数にノーツのステータスを入れて描画
//	/// </summary>
//	/// <param name="m_texture">ノーツテクスチャのポインター</param>
//	void Notes_Object_Draw(CTex* m_texture);
//
//
//	void Notes_Object_Finish(CTex* m_texture);
//
//	/// <summary>
//	/// シザー矩形を使うかどうかの関数
//	/// </summary>
//	void ScissorLR()
//	{
//		if (m_dir == NOTES_DIRECTION::LEFT)
//		{
//			TurnOnLeftScissor();//使う
//		}
//		else if (m_dir == NOTES_DIRECTION::RIGHT)
//		{
//			TurnOnRightScissor();//使わない
//		}
//	}
//
//
//
//	/// <summary>
//	/// ノーツのステータスを返す
//	/// </summary>
//	/// <returns></returns>
//	NOTES_STATUS IsLive()
//	{
//		if (m_sts == NOTES_STATUS::LIVE)
//		{
//			return NOTES_STATUS::LIVE;
//		}
//		if (m_sts == NOTES_STATUS::UNDEAD)
//		{
//			return NOTES_STATUS::UNDEAD;
//		}
//		else if (m_sts == NOTES_STATUS::DEAD)
//		{
//			return NOTES_STATUS::DEAD;
//		}
//
//		else
//		{
//			NOTES_STATUS::DEAD;
//		}
//	}
//
//	/// <summary>
//	/// テクスチャのポインターを格納
//	/// </summary>
//	/// <param name="tex"></param>
//	void SetTexture(CTex* tex)
//	{
//		m_texture = tex;
//	}
//};
