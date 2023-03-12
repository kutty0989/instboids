//// ColTrees.h (2007.3.25)
//
//// �Փ˔���p�c���[�N���X�錾��
//
//// �C�����
//// 2007. 5. 13
////  2�̋��ʋ�Ԃ��Z�o���鎞�Ɉ����Z�����Ă����o�O��
////  �r���I�_���a�ɕύX
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
//	// ���ؓo�^�I�u�W�F�N�g(OFT)
//	//////////////////////////////////
//	template< class T>
//	class OBJECT_FOR_TREE
//	{
//	public:
//		CCell<T>* m_pCell;			// �o�^���
//		T* m_pObject;				// ����ΏۃI�u�W�F�N�g
//		sp<OBJECT_FOR_TREE<T> > m_spPre;	// �O��OBJECT_FOR_TREE�\����
//		sp<OBJECT_FOR_TREE<T> > m_spNext;	// ����OBJECT_FOR_TREE�\����
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
//		// ���烊�X�g����O���
//		bool Remove() {
//			// ���łɈ�E���Ă��鎞�͏����I��
//			if (!m_pCell)
//				return false;
//
//			// ������o�^���Ă����ԂɎ��g��ʒm
//			if (!m_pCell->OnRemove(this))
//				return false;
//
//			// ��E����
//			// �O��̃I�u�W�F�N�g�����т���
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
//		// ��Ԃ�o�^
//		void RegistCell(CCell<T>* pCell)
//		{
//			m_pCell = pCell;
//		}
//
//		// ���̃I�u�W�F�N�g�ւ̃X�}�[�g�|�C���^���擾
//		sp<OBJECT_FOR_TREE<T> >& GetNextObj() {
//			return m_spNext;
//		}
//	};
//
//
//
//	/////////////////////////////////////
//	// ���`4���؋�ԊǗ��N���X
//	//////////////////////////////////
//#define CLINER4TREEMANAGER_MAXLEVEL		9
//	template <class T>
//	class CLiner4TreeManager
//	{
//	protected:
//	public:
//		unsigned int m_uiDim;
//		CCell<T>** ppCellAry;	// ���`��ԃ|�C���^�z��
//		unsigned int m_iPow[CLINER4TREEMANAGER_MAXLEVEL + 1];	// �ׂ��搔�l�z��
//		float m_fW;		// �̈��X����
//		float m_fH;		// �̈��Y����
//		float m_fLeft;	// �̈�̍����iX���ŏ��l�j
//		float m_fTop;	// �̈�̏㑤�iY���ŏ��l�j
//		float m_fUnit_W;		// �ŏ����x����Ԃ̕��P��
//		float m_fUnit_H;		// �ŏ����x����Ԃ̍��P��
//		DWORD m_dwCellNum;		// ��Ԃ̐�
//		unsigned int m_uiLevel;			// �ŉ��ʃ��x��
//
//	public:
//		// �R���X�g���N�^
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
//		// �f�X�g���N�^
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
//		// ���`4���ؔz����\�z����
//		bool Init(unsigned int Level, float left, float top, float right, float bottom)
//		{
//			// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
//			if (Level >= CLINER4TREEMANAGER_MAXLEVEL)
//				return false;
//
//			// �e���x���ł̋�Ԑ����Z�o
//			int i;
//			m_iPow[0] = 1;
//			for (i = 1;i < CLINER4TREEMANAGER_MAXLEVEL + 1;i++)
//				m_iPow[i] = m_iPow[i - 1] * 4;
//
//			// Level���x���i0��_�j�̔z��쐬
//			m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
//			ppCellAry = new CCell<T>*[m_dwCellNum];
//			ZeroMemory(ppCellAry, sizeof(CCell<T>*) * m_dwCellNum);
//
//			// �̈��o�^
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
//		// �I�u�W�F�N�g��o�^����
//		bool Regist(float left, float top, float right, float bottom, sp<OBJECT_FOR_TREE<T> >& spOFT)
//		{
//			// �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
//			DWORD Elem = GetMortonNumber(left, top, right, bottom);
//			if (Elem < m_dwCellNum) {
//				// ��Ԃ������ꍇ�͐V�K�쐬
//				if (!ppCellAry[Elem])
//					CreateNewCell(Elem);
//				return ppCellAry[Elem]->Push(spOFT);
//			}
//			return false;	// �o�^���s
//		}
//
//		// �Փ˔��胊�X�g���쐬����
//		DWORD GetAllCollisionList(vector<T*>& ColVect)
//		{
//			// ���X�g�i�z��j�͕K�����������܂�
//			ColVect.clear();
//
//			// ���[�g��Ԃ̑��݂��`�F�b�N
//			if (ppCellAry[0] == NULL)
//				return 0;	// ��Ԃ����݂��Ă��Ȃ�
//
//			// ���[�g��Ԃ�����
//			list<T*> ColStac;
//			GetCollisionList(0, ColVect, ColStac);
//
//			return (DWORD)ColVect.size();
//		}
//		// ��ԓ��ŏՓ˃��X�g���쐬����
//		bool GetCollisionList(DWORD Elem, vector<T*>& ColVect, list<T*>& ColStac)
//		{
//			// ���X�g�i�z��j�͕K�����������܂�
//			ColVect.clear();
//
//			// ���[�g��Ԃ̑��݂��`�F�b�N
//			if (ppCellAry[0] == NULL)
//				return 0;	// ��Ԃ����݂��Ă��Ȃ�
//
//
//			typename list<T*>::iterator it;
//			// �@ ��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
//			sp<OBJECT_FOR_TREE<T>> spOFT1 = ppCellAry[Elem]->GetFirstObj();
//			while (spOFT1.GetPtr() != NULL)
//			{
//				sp<OBJECT_FOR_TREE<T> > spOFT2 = spOFT1->m_spNext;
//				while (spOFT2 != NULL) {
//					// �Փ˃��X�g�쐬
//					ColVect.push_back(spOFT1->m_pObject);
//					ColVect.push_back(spOFT2->m_pObject);
//					spOFT2 = spOFT2->m_spNext;
//				}
//				// �A �Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
//				for (it = ColStac.begin(); it != ColStac.end(); it++) {
//					ColVect.push_back(spOFT1->m_pObject);
//					ColVect.push_back(*it);
//				}
//				spOFT1 = spOFT1->m_spNext;
//			}
//
//			bool ChildFlag = false;
//			// �B �q��ԂɈړ�
//			DWORD ObjNum = 0;
//			DWORD i, NextElem;
//			for (i = 0; i < 4; i++) {
//				NextElem = Elem * 4 + 1 + i;
//				if (NextElem < m_dwCellNum && ppCellAry[Elem * 4 + 1 + i]) {
//					if (!ChildFlag) {
//						// �C �o�^�I�u�W�F�N�g���X�^�b�N�ɒǉ�
//						spOFT1 = ppCellAry[Elem]->GetFirstObj();
//						while (spOFT1.GetPtr()) {
//							ColStac.push_back(spOFT1->m_pObject);
//							ObjNum++;
//							spOFT1 = spOFT1->m_spNext;
//						}
//					}
//					ChildFlag = true;
//					GetCollisionList(Elem * 4 + 1 + i, ColVect, ColStac);	// �q��Ԃ�
//				}
//			}
//
//			// �D �X�^�b�N����I�u�W�F�N�g���O��
//			if (ChildFlag) {
//				for (i = 0; i < ObjNum; i++)
//					ColStac.pop_back();
//			}
//
//			return true;
//		}
//
//
//		// ��Ԃ𐶐�
//		bool CreateNewCell(DWORD Elem)
//		{
//			// �����̗v�f�ԍ�
//			while (!ppCellAry[Elem])
//			{
//				// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
//				ppCellAry[Elem] = new CCell<T>;
//
//				// �e��ԂɃW�����v
//				Elem = (Elem - 1) >> 2;
//				if (Elem >= m_dwCellNum) break;
//			}
//			return true;
//		}
//
//		// ���W�����Ԕԍ����Z�o
//		DWORD GetMortonNumber(float left, float top, float right, float bottom)
//		{
//			// �ŏ����x���ɂ�����e���ʒu���Z�o
//			DWORD LT = GetPointElem(left, top);
//			DWORD RB = GetPointElem(right, bottom);
//
//			// ��Ԕԍ��������Z����
//			// �ŏ�ʋ�؂肩�珊�����x�����Z�o
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
//		// �r�b�g�����֐�
//		DWORD BitSeparate32(DWORD n)
//		{
//			n = (n | (n << 8)) & 0x00ff00ff;
//			n = (n | (n << 4)) & 0x0f0f0f0f;
//			n = (n | (n << 2)) & 0x33333333;
//			return (n | (n << 1)) & 0x55555555;
//		}
//
//		// 2D���[�g����Ԕԍ��Z�o�֐�
//		WORD Get2DMortonNumber(WORD x, WORD y)
//		{
//			return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
//		}
//
//		// ���W�����`4���ؗv�f�ԍ��ϊ��֐�
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
//	// ��ԃN���X
//	//////////////////////////////////
//	template <class T>
//	class CCell
//	{
//	protected:
//		sp<OBJECT_FOR_TREE<T> > m_spLatest;	// �ŐVOFL�ւ̃X�}�[�g�|�C���^
//
//	public:
//		// �R���X�g���N�^
//		CCell()
//		{
//		}
//
//		// �f�X�g���N�^
//		virtual ~CCell()
//		{
//			if (m_spLatest.GetPtr() != NULL)
//				ResetLink(m_spLatest);
//		}
//
//		// �����N��S�ă��Z�b�g����
//		void ResetLink(sp<OBJECT_FOR_TREE<T> >& spOFT)
//		{
//			if (spOFT->m_spNext.GetPtr() != NULL)
//				ResetLink(spOFT->m_spNext);
//			spOFT.SetPtr(NULL);		// �X�}�[�g�|�C���^���Z�b�g		
//		}
//
//		// OFT���v�b�V��
//		bool Push(sp<OBJECT_FOR_TREE<T> >& spOFT)
//		{
//			if (spOFT.GetPtr() == NULL) return false;	// �����I�u�W�F�N�g�͓o�^���Ȃ�
//			if (spOFT->m_pCell == this) return false;	// 2�d�o�^�`�F�b�N
//			if (m_spLatest.GetPtr() == NULL) {
//				m_spLatest = spOFT;	// ��ԂɐV�K�o�^
//			}
//			else
//			{
//				// �ŐVOFT�I�u�W�F�N�g���X�V
//				spOFT->m_spNext = m_spLatest;
//				m_spLatest->m_spPre = spOFT;
//				m_spLatest = spOFT;
//			}
//			spOFT->RegistCell(this);	// ��Ԃ�o�^
//			return true;
//		}
//
//		sp<OBJECT_FOR_TREE<T> >& GetFirstObj()
//		{
//			return m_spLatest;
//		}
//
//		// �폜�����I�u�W�F�N�g���`�F�b�N
//		bool OnRemove(OBJECT_FOR_TREE<T>* pRemoveObj)
//		{
//			if (m_spLatest.GetPtr() == pRemoveObj) {
//				// ���̃I�u�W�F�N�g�ɑ}���ւ�
//				if (m_spLatest.GetPtr() != NULL)
//					m_spLatest = m_spLatest->GetNextObj();
//			}
//			return true;
//		}
//	};
//
//
//}  // end namespace IKD