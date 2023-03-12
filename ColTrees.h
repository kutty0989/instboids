//// ColTrees.h (2007.3.25)
//
//// 衝突判定用ツリークラス宣言部
//
//// 修正情報
//// 2007. 5. 13
////  2つの共通空間を算出する時に引き算をしていたバグを
////  排他的論理和に変更
//
//#pragma once
//
//#include <windows.h>
//#include <set>
//#include "SmartPtr.h"
//#include <vector>
//#include <list>
//#include <map>
//
//using namespace std;
//
//
//namespace IKD
//{
//
//
//	template <class T>
//	class CCell;
//	/////////////////////////////////////
//	// 分木登録オブジェクト(OFT)
//	//////////////////////////////////
//	template< class T>
//	class OBJECT_FOR_TREE
//	{
//	public:
//		CCell<T>* m_pCell;			// 登録空間
//		T* m_pObject;				// 判定対象オブジェクト
//		sp<OBJECT_FOR_TREE<T> > m_spPre;	// 前のOBJECT_FOR_TREE構造体
//		sp<OBJECT_FOR_TREE<T> > m_spNext;	// 次のOBJECT_FOR_TREE構造体
//
//	public:
//		OBJECT_FOR_TREE() {
//			m_pCell = NULL;
//			m_pObject = NULL;
//		}
//
//		virtual ~OBJECT_FOR_TREE()
//		{
//		}
//
//	public:
//		// 自らリストから外れる
//		bool Remove() {
//			// すでに逸脱している時は処理終了
//			if (!m_pCell)
//				return false;
//
//			// 自分を登録している空間に自身を通知
//			if (!m_pCell->OnRemove(this))
//				return false;
//
//			// 逸脱処理
//			// 前後のオブジェクトを結びつける
//			if (m_spPre.GetPtr() != NULL)
//			{
//				m_spPre->m_spNext = m_spNext;
//				m_spPre.SetPtr(NULL);
//			}
//			if (m_spNext.GetPtr() != NULL)
//			{
//				m_spNext->m_spPre = m_spPre;
//				m_spNext.SetPtr(NULL);
//			}
//			m_pCell = NULL;
//			return true;
//		}
//
//		// 空間を登録
//		void RegistCell(CCell<T>* pCell)
//		{
//			m_pCell = pCell;
//		}
//
//		// 次のオブジェクトへのスマートポインタを取得
//		sp<OBJECT_FOR_TREE<T> >& GetNextObj() {
//			return m_spNext;
//		}
//	};
//
//
//
//	/////////////////////////////////////
//	// 線形4分木空間管理クラス
//	//////////////////////////////////
//#define CLINER4TREEMANAGER_MAXLEVEL		9
//	template <class T>
//	class CLiner4TreeManager
//	{
//	protected:
//	public:
//		unsigned int m_uiDim;
//		CCell<T>** ppCellAry;	// 線形空間ポインタ配列
//		unsigned int m_iPow[CLINER4TREEMANAGER_MAXLEVEL + 1];	// べき乗数値配列
//		float m_fW;		// 領域のX軸幅
//		float m_fH;		// 領域のY軸幅
//		float m_fLeft;	// 領域の左側（X軸最小値）
//		float m_fTop;	// 領域の上側（Y軸最小値）
//		float m_fUnit_W;		// 最小レベル空間の幅単位
//		float m_fUnit_H;		// 最小レベル空間の高単位
//		DWORD m_dwCellNum;		// 空間の数
//		unsigned int m_uiLevel;			// 最下位レベル
//
//	public:
//		// コンストラクタ
//		CLiner4TreeManager()
//		{
//			m_uiLevel = 0;
//			m_fW = 0.0f;
//			m_fH = 0.0f;
//			m_fLeft = 0.0f;
//			m_fTop = 0.0f;
//			m_fUnit_W = 0.0f;
//			m_fUnit_H = 0.0f;
//			m_dwCellNum = 0;
//			ppCellAry = NULL;
//			m_uiDim = 0;
//		}
//
//		// デストラクタ
//		virtual ~CLiner4TreeManager()
//		{
//			DWORD i;
//			for (i = 0; i < m_dwCellNum; i++) {
//				if (ppCellAry[i] != NULL)
//					delete ppCellAry[i];
//			}
//			delete[] ppCellAry;
//		}
//
//		// 線形4分木配列を構築する
//		bool Init(unsigned int Level, float left, float top, float right, float bottom)
//		{
//			// 設定最高レベル以上の空間は作れない
//			if (Level >= CLINER4TREEMANAGER_MAXLEVEL)
//				return false;
//
//			// 各レベルでの空間数を算出
//			int i;
//			m_iPow[0] = 1;
//			for (i = 1;i < CLINER4TREEMANAGER_MAXLEVEL + 1;i++)
//				m_iPow[i] = m_iPow[i - 1] * 4;
//
//			// Levelレベル（0基点）の配列作成
//			m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
//			ppCellAry = new CCell<T>*[m_dwCellNum];
//			ZeroMemory(ppCellAry, sizeof(CCell<T>*) * m_dwCellNum);
//
//			// 領域を登録
//			m_fLeft = left;
//			m_fTop = top;
//			m_fW = right - left;
//			m_fH = bottom - top;
//			m_fUnit_W = m_fW / (1 << Level);
//			m_fUnit_H = m_fH / (1 << Level);
//
//			m_uiLevel = Level;
//
//			return true;
//		}
//
//		// オブジェクトを登録する
//		bool Regist(float left, float top, float right, float bottom, sp<OBJECT_FOR_TREE<T> >& spOFT)
//		{
//			// オブジェクトの境界範囲から登録モートン番号を算出
//			DWORD Elem = GetMortonNumber(left, top, right, bottom);
//			if (Elem < m_dwCellNum) {
//				// 空間が無い場合は新規作成
//				if (!ppCellAry[Elem])
//					CreateNewCell(Elem);
//				return ppCellAry[Elem]->Push(spOFT);
//			}
//			return false;	// 登録失敗
//		}
//
//		// 衝突判定リストを作成する
//		DWORD GetAllCollisionList(vector<T*>& ColVect)
//		{
//			// リスト（配列）は必ず初期化します
//			ColVect.clear();
//
//			// ルート空間の存在をチェック
//			if (ppCellAry[0] == NULL)
//				return 0;	// 空間が存在していない
//
//			// ルート空間を処理
//			list<T*> ColStac;
//			GetCollisionList(0, ColVect, ColStac);
//
//			return (DWORD)ColVect.size();
//		}
//		// 空間内で衝突リストを作成する
//		bool GetCollisionList(DWORD Elem, vector<T*>& ColVect, list<T*>& ColStac)
//		{
//			// リスト（配列）は必ず初期化します
//			ColVect.clear();
//
//			// ルート空間の存在をチェック
//			if (ppCellAry[0] == NULL)
//				return 0;	// 空間が存在していない
//
//
//			typename list<T*>::iterator it;
//			// ① 空間内のオブジェクト同士の衝突リスト作成
//			sp<OBJECT_FOR_TREE<T>> spOFT1 = ppCellAry[Elem]->GetFirstObj();
//			while (spOFT1.GetPtr() != NULL)
//			{
//				sp<OBJECT_FOR_TREE<T> > spOFT2 = spOFT1->m_spNext;
//				while (spOFT2 != NULL) {
//					// 衝突リスト作成
//					ColVect.push_back(spOFT1->m_pObject);
//					ColVect.push_back(spOFT2->m_pObject);
//					spOFT2 = spOFT2->m_spNext;
//				}
//				// ② 衝突スタックとの衝突リスト作成
//				for (it = ColStac.begin(); it != ColStac.end(); it++) {
//					ColVect.push_back(spOFT1->m_pObject);
//					ColVect.push_back(*it);
//				}
//				spOFT1 = spOFT1->m_spNext;
//			}
//
//			bool ChildFlag = false;
//			// ③ 子空間に移動
//			DWORD ObjNum = 0;
//			DWORD i, NextElem;
//			for (i = 0; i < 4; i++) {
//				NextElem = Elem * 4 + 1 + i;
//				if (NextElem < m_dwCellNum && ppCellAry[Elem * 4 + 1 + i]) {
//					if (!ChildFlag) {
//						// ④ 登録オブジェクトをスタックに追加
//						spOFT1 = ppCellAry[Elem]->GetFirstObj();
//						while (spOFT1.GetPtr()) {
//							ColStac.push_back(spOFT1->m_pObject);
//							ObjNum++;
//							spOFT1 = spOFT1->m_spNext;
//						}
//					}
//					ChildFlag = true;
//					GetCollisionList(Elem * 4 + 1 + i, ColVect, ColStac);	// 子空間へ
//				}
//			}
//
//			// ⑤ スタックからオブジェクトを外す
//			if (ChildFlag) {
//				for (i = 0; i < ObjNum; i++)
//					ColStac.pop_back();
//			}
//
//			return true;
//		}
//
//
//		// 空間を生成
//		bool CreateNewCell(DWORD Elem)
//		{
//			// 引数の要素番号
//			while (!ppCellAry[Elem])
//			{
//				// 指定の要素番号に空間を新規作成
//				ppCellAry[Elem] = new CCell<T>;
//
//				// 親空間にジャンプ
//				Elem = (Elem - 1) >> 2;
//				if (Elem >= m_dwCellNum) break;
//			}
//			return true;
//		}
//
//		// 座標から空間番号を算出
//		DWORD GetMortonNumber(float left, float top, float right, float bottom)
//		{
//			// 最小レベルにおける各軸位置を算出
//			DWORD LT = GetPointElem(left, top);
//			DWORD RB = GetPointElem(right, bottom);
//
//			// 空間番号を引き算して
//			// 最上位区切りから所属レベルを算出
//			DWORD Def = RB - LT;
//			unsigned int HiLevel = 0;
//			unsigned int i;
//			for (i = 0; i < m_uiLevel; i++)
//			{
//				DWORD Check = (Def >> (i * 2)) & 0x3;
//				if (Check != 0)
//					HiLevel = i + 1;
//			}
//			DWORD SpaceNum = RB >> (HiLevel * 2);
//			DWORD AddNum = (m_iPow[m_uiLevel - HiLevel] - 1) / 3;
//			SpaceNum += AddNum;
//
//			if (SpaceNum > m_dwCellNum)
//				return 0xffffffff;
//
//			return SpaceNum;
//		}
//
//		// ビット分割関数
//		DWORD BitSeparate32(DWORD n)
//		{
//			n = (n | (n << 8)) & 0x00ff00ff;
//			n = (n | (n << 4)) & 0x0f0f0f0f;
//			n = (n | (n << 2)) & 0x33333333;
//			return (n | (n << 1)) & 0x55555555;
//		}
//
//		// 2Dモートン空間番号算出関数
//		WORD Get2DMortonNumber(WORD x, WORD y)
//		{
//			return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
//		}
//
//		// 座標→線形4分木要素番号変換関数
//		DWORD GetPointElem(float pos_x, float pos_y)
//		{
//			return Get2DMortonNumber((WORD)((pos_x - m_fLeft) / m_fUnit_W), (WORD)((pos_y - m_fTop) / m_fUnit_H));
//		}
//	};
//
//
//
//
//
//
//
//
//
//
//	/////////////////////////////////////
//	// 空間クラス
//	//////////////////////////////////
//	template <class T>
//	class CCell
//	{
//	protected:
//		sp<OBJECT_FOR_TREE<T> > m_spLatest;	// 最新OFLへのスマートポインタ
//
//	public:
//		// コンストラクタ
//		CCell()
//		{
//		}
//
//		// デストラクタ
//		virtual ~CCell()
//		{
//			if (m_spLatest.GetPtr() != NULL)
//				ResetLink(m_spLatest);
//		}
//
//		// リンクを全てリセットする
//		void ResetLink(sp<OBJECT_FOR_TREE<T> >& spOFT)
//		{
//			if (spOFT->m_spNext.GetPtr() != NULL)
//				ResetLink(spOFT->m_spNext);
//			spOFT.SetPtr(NULL);		// スマートポインタリセット		
//		}
//
//		// OFTをプッシュ
//		bool Push(sp<OBJECT_FOR_TREE<T> >& spOFT)
//		{
//			if (spOFT.GetPtr() == NULL) return false;	// 無効オブジェクトは登録しない
//			if (spOFT->m_pCell == this) return false;	// 2重登録チェック
//			if (m_spLatest.GetPtr() == NULL) {
//				m_spLatest = spOFT;	// 空間に新規登録
//			}
//			else
//			{
//				// 最新OFTオブジェクトを更新
//				spOFT->m_spNext = m_spLatest;
//				m_spLatest->m_spPre = spOFT;
//				m_spLatest = spOFT;
//			}
//			spOFT->RegistCell(this);	// 空間を登録
//			return true;
//		}
//
//		sp<OBJECT_FOR_TREE<T> >& GetFirstObj()
//		{
//			return m_spLatest;
//		}
//
//		// 削除されるオブジェクトをチェック
//		bool OnRemove(OBJECT_FOR_TREE<T>* pRemoveObj)
//		{
//			if (m_spLatest.GetPtr() == pRemoveObj) {
//				// 次のオブジェクトに挿げ替え
//				if (m_spLatest.GetPtr() != NULL)
//					m_spLatest = m_spLatest->GetNextObj();
//			}
//			return true;
//		}
//	};
//
//
//}  // end namespace IKD