//// SmartPtr.h: sp �N���X�̃C���^�[�t�F�C�X
////
////////////////////////////////////////////////////////////////////////
//
//#if !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
//#define AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
//
//#include <windows.h>
//
//// sp�N���X�i�e���v���[�g�X�}�[�g�|�C���^�N���X�j
////  Created by IKD (2005. 9. 2) v1.00
////  �ŏI�X�V (2007. 3. 6) v2.02
//
//// 2007. 3. 6
//// vector�ɑ���ł��Ȃ��o�O���C���i�R�s�[�R���X�g���N�^�̃~�X���C���j
//
//// 2007. 3. 1
//// ���`�R�s�[�ŃR�s�[�R���X�g���N�^���Ă΂�Ȃ��s����C��
//// �����I�A�b�v�L���X�g�y�шÖٓI�A�b�v�L���X�g�Ń_�u���|�C���^���������Ȃ��s����C��
//
//// 2007. 2. 11
////   �X���b�v�ɑΉ�
//
//// �E �o�^���ꂽ�I�u�W�F�N�g�|�C���^�̎g�p�҂����Ȃ��Ȃ����玩���I��delete
//// �E �ʏ�̃|�C���^���쉉�Z�q�u*�v�u->�v�u[ ]�v���g����B
//// �E �قȂ�I�u�W�F�N�g�|�C���^���o�^���ꂽ��ԂŃA�b�v�L���X�g���ł���
//// �E DownCast���\�b�h�ɂ����S�ȃ_�E���L���X�g�T�|�[�g
//// �E SwapPtr���\�b�h�ɂ��|�C���^����ւ��̃T�|�[�g
//
//
//template <class T>
//class sp
//{
//private:
//    unsigned int* m_pRefCnt;   // �Q�ƃJ�E���^�ւ̃|�C���^
//    T** m_ppPtr;             // T�^�̃I�u�W�F�N�g�̃_�u���|�C���^
//    static T* m_NullPtr;		// NULL�|�C���^�l
//
//private:
//    /////////////////
//    // �Q�ƃJ�E���^����
//    /////
//    void AddRef() { (*m_pRefCnt)++; }
//
//    /////////////////
//    // �Q�ƃJ�E���^����
//    /////
//    void Release()
//    {
//        if (--(*m_pRefCnt) == 0) {
//            delete* m_ppPtr;
//            delete m_ppPtr;
//            delete m_pRefCnt;
//        }
//    }
//
//public:
//    ///////////////////////
//     // �f�t�H���g�R���X�g���N�^
//     /////
//    explicit sp(T* src = NULL, int add = 0)
//    {
//        m_pRefCnt = new unsigned int;
//        *m_pRefCnt = add;
//        m_ppPtr = new T*;
//        m_NullPtr = NULL;
//        if (src)
//            *m_ppPtr = src;
//        else
//            *m_ppPtr = m_NullPtr;   // NULL�|�C���^�����Ă���
//        AddRef();       // �Q�ƃJ�E���^����
//    }
//
//
//    //////////////////////////////////////
//    // �R�s�[�R���X�g���N�^�i���^�R�s�[�j
//    /////
//    sp(const sp<T>& src)
//    {
//        // ����̃|�C���^�����ׂăR�s�[
//        m_pRefCnt = src.m_pRefCnt;   // �Q�ƃJ�E���^�|�C���^
//        m_ppPtr = src.m_ppPtr;       // T�^�_�u���|�C���^
//
//        // �������g�̎Q�ƃJ�E���^�𑝉�
//        AddRef();
//    }
//
//
//    //////////////////////////////////////
//    // �R�s�[�R���X�g���N�^�i�ÖٓI�A�b�v�L���X�g�j
//    /////
//    template<class T2> sp(sp<T2>& src)
//    {
//        // ����̃_�u���|�C���^���R�s�[
//        m_pRefCnt = src.GetRefPtr();
//        m_ppPtr = (T**)src.GetPtrPtr();
//
//        // �^�`�F�b�N�R�s�[
//        *m_ppPtr = src.GetPtr();
//
//        // �������g�̎Q�ƃJ�E���^�𑝉�
//        AddRef();
//    }
//
//
//    //////////////////////////////////////
//    // �R�s�[�R���X�g���N�^�iNULL�����p�j
//    /////
//    sp(const int nullval)
//    {
//        m_pRefCnt = new UINT;
//        *m_pRefCnt = 0;
//        m_ppPtr = new T*;
//        *m_ppPtr = m_NullPtr;
//        AddRef();       // �Q�ƃJ�E���^����
//    }
//
//
//    ///////////////
//    // �f�X�g���N�^
//    /////
//    virtual ~sp()
//    {
//        Release();
//    }
//
//
//    //���������Z�q�̃I�[�o�[���[�h����������������������
//
//
//       /////////////////////////////////
//       // =������Z�q�i�����I�R�s�[�j
//       /////
//    sp<T>& operator =(const sp<T>& src)
//    {
//        // �������g�ւ̑���͕s���ňӖ��������̂�
//        // �s��Ȃ��B
//        if (*src.m_ppPtr == *m_ppPtr)
//            return (*this);
//
//        // �����͑��l�ɂȂ��Ă��܂��̂�
//       // �Q�ƃJ�E���^��1����
//        Release();
//
//        // ����̃|�C���^���R�s�[
//        m_pRefCnt = src.m_pRefCnt;
//        m_ppPtr = src.m_ppPtr;
//
//        // �V�����������g�̎Q�ƃJ�E���^�𑝉�
//        AddRef();
//
//        return (*this);
//    }
//
//
//    /////////////////////////////////
//    // =������Z�q�i�����I�A�b�v�L���X�g�j
//    /////
//    template<class T2> sp<T>& operator =(sp<T2>& src)
//    {
//        // �������g�ւ̑���͕s���ňӖ��������̂�
//        // �s��Ȃ��B
//        if (src.GetPtr() == *m_ppPtr)
//            return (*this);
//
//        // �����͑��l�ɂȂ��Ă��܂��̂�
//       // �Q�ƃJ�E���^��1����
//        Release();
//
//        // ����̃|�C���^���R�s�[
//        m_pRefCnt = src.GetRefPtr();
//        m_ppPtr = (T**)src.GetPtrPtr();
//
//        // �^�`�F�b�N�R�s�[
//        *m_ppPtr = src.GetPtr();
//
//        // �V�����������g�̎Q�ƃJ�E���^�𑝉�
//        AddRef();
//
//        return (*this);
//    }
//
//
//    /////////////////////////////////
//    // =������Z�q(NULL����ɂ�郊�Z�b�g�j
//    /////
//    sp<T>& operator =(const int nullval)
//    {
//        // �����͋�Ȑl�ɂȂ��Ă��܂��̂�
//        // �Q�ƃJ�E���^��1����
//        Release();
//
//        // �V�K�Ɏ������g�����
//        m_pRefCnt = new unsigned int(1);
//        m_ppPtr = new T*;
//        m_ppPtr = m_NullPtr;
//
//        return (*this);
//    }
//
//
//    ///////////////
//    // *�Ԑډ��Z�q
//    /////
//    T& operator *() { return **m_ppPtr; }
//
//    //////////////////////
//    // ->�����o�I�����Z�q
//    /////
//    T* operator ->() { return *m_ppPtr; }
//
//    /////////////////
//    // ==��r���Z�q
//    /////
// /*      bool operator ==(int val){
//          if((int)m_pPtr == val)
//             return TRUE;
//          return FALSE;
//       }
// */
//    bool operator ==(T* val) {
//        if (*m_ppPtr == val)
//            return true;
//        return false;
//    }
//
//    /////////////////
//    // !=��r���Z�q
//    /////
// /*      bool operator !=(int val){
//          if((int)m_pPtr != val)
//             return TRUE;
//          return FALSE;
//       }
// */
//    bool operator !=(T* val) {
//        if (*m_ppPtr != val)
//            return true;
//        return false;
//    }
//
//
//    //������ �����o�֐� ����������������������
//
//public:
//    //////////////////////////
//    // �|�C���^�̖����I�ȓo�^
//    /////
//    void SetPtr(T* src = NULL, int add = 0)
//    {
//        // �Q�ƃJ�E���^�����炵����ɍď�����
//        Release();
//        m_pRefCnt = new unsigned int;
//        *m_pRefCnt = add;
//        m_ppPtr = new T*;
//        if (src)
//            *m_ppPtr = src;
//        else
//            *m_ppPtr = m_NullPtr;
//        AddRef();
//    }
//
//    /////////////////////
//    // �|�C���^�݂̑��o��
//    /////
//    T* GetPtr() { return *m_ppPtr; }
//    T** GetPtrPtr() { return m_ppPtr; }
//
//
//    ///////////////////////////////
//    // �Q�ƃJ�E���^�ւ̃|�C���^���擾
//    /////
//    unsigned int* GetRefPtr() { return m_pRefCnt; }
//
//    //////////////////////////
//    // �_�E���L���X�g�R�s�[
//    /////
//    template <class T2> bool DownCast(sp<T2>& src)
//    {
//        // �����̃X�}�[�g�|�C���^�̎��|�C���^���A
//        // �����̓o�^���Ă���|�C���^��
//        // �_�E���L���X�g�\�ȏꍇ�̓_�E���L���X�g�R�s�[�����s
//        T* castPtr = dynamic_cast<T*>(src.GetPtr());
//        if (castPtr) {
//            // �_�E���L���X�g����
//            // �����͈Ⴄ�l�ɂȂ�̂�
//            // �����̎Q�ƃJ�E���^��1����
//            Release();
//            // �V�����|�C���^�ƎQ�ƃJ�E���^�����L
//            m_ppPtr = (T**)src.GetPtrPtr();
//            *m_ppPtr = castPtr;
//            m_pRefCnt = src.GetRefPtr();
//            // �Q�ƃJ�E���^����
//            AddRef();
//            return true;
//        }
//
//        return false;
//    }
//
//    ///////////////////////
//    // �|�C���^�X���b�v�i�����j
//    ///////
//    void SwapPtr(sp<T>& src)
//    {
//        T* pTmp = src.GetPtr();
//        *src.m_ppPtr = *m_ppPtr;   // �|�C���^�̌���
//        *m_ppPtr = pTmp;
//    }
//};
//
//template <class T>
//T* sp<T>::m_NullPtr = NULL;
//
//
//#endif // !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
