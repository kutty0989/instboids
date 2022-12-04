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
//	NOTES_DIRECTION m_dir;//�m�[�c�̍��E�𔻒f
//	NOTES_NAME n_name;//���̃m�[�c��
//	CTex* m_texture;//�e�N�X�`��
//
//
//
//public:
//
//	int Change_UV = 0;//�m�[�c��uv�𔽓]������@long�m�[�c����
//	float start_notes = 0.0f;//�m�[�c���������ꂽ���̎���
//	NOTES_STATUS m_sts = NOTES_STATUS::DEAD;//�m�[�c�̃X�e�[�^�X
//	XMFLOAT3 m_pos = {};//�m�[�c�̃|�W�V����
//	XMFLOAT3 m_scale = {};//�m�[�c�̃X�P�[��
//	float m_Alpha = 1.0f;//�A���t�@�l
//	float m_rot = 0.0f;//�m�[�c�̉�]
//
//	//�m�[�c��UV
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
//	/// �e�N�X�`���̑傫���Əꏊ���Z�b�g
//	/// </summary>
//	/// <param name="notes_LR">true���Efalse �����̃m�[�c</param>
//	/// <param name="m_name">//�Z���m�[�c�����m�[�c�Ȃǂ��i�[</param>
//	/// <returns></returns>
//	bool Notes_Object_Initialize( CTex* m_texture);//�m�[�c�̍��E�Ɖ��̃m�[�c������
//
//   /// <summary>
//   /// BPM�̊�����float�l�ŕԂ��@�ړ��̐��`�⊮�Ŏg��
//   /// </summary>
//   /// <returns></returns>
//	float Notes_Object_Update();
//
//	/// <summary>
//	/// CTex�ɂ���Z�b�g�֐��Ƀm�[�c�̃X�e�[�^�X�����ĕ`��
//	/// </summary>
//	/// <param name="m_texture">�m�[�c�e�N�X�`���̃|�C���^�[</param>
//	void Notes_Object_Draw(CTex* m_texture);
//
//
//	void Notes_Object_Finish(CTex* m_texture);
//
//	/// <summary>
//	/// �V�U�[��`���g�����ǂ����̊֐�
//	/// </summary>
//	void ScissorLR()
//	{
//		if (m_dir == NOTES_DIRECTION::LEFT)
//		{
//			TurnOnLeftScissor();//�g��
//		}
//		else if (m_dir == NOTES_DIRECTION::RIGHT)
//		{
//			TurnOnRightScissor();//�g��Ȃ�
//		}
//	}
//
//
//
//	/// <summary>
//	/// �m�[�c�̃X�e�[�^�X��Ԃ�
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
//	/// �e�N�X�`���̃|�C���^�[���i�[
//	/// </summary>
//	/// <param name="tex"></param>
//	void SetTexture(CTex* tex)
//	{
//		m_texture = tex;
//	}
//};
