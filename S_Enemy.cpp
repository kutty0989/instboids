//#include	"S_Enemy.h"
//#include	"drawaxis.h"
//#include    "CCamera.h"
//#include    "DX11Settransform.h"
//#include"IMgui/imgui.h"
//#include<iostream>
//#include"PlayerMgr.h"
////�L�����̈ړ�����
////S_Enemy::DIRECTION g_direction = S_Enemy::DIRECTION::NEUTRAL;
//
//#define debuglog(a) std::cout<<a<<std::endl;
//
//static bool enemy_turn_flg;//�G���^�[������������ǂ����@true������@f�܂�
//
//bool e = false;
//
//
//bool S_Enemy::Init() {
//
//	// �s�񏉊���
//	DX11MtxIdentity(m_mtx);
//	return true;
//
//	//�V�[�h�l���藐��
//	std::random_device rand_dev;
//
//	//�V�[�h�l�Z�b�g
//	m_mt.seed(rand_dev());
//	m_mt2.seed(rand_dev());
//	enemy_turn_flg = false;
//	m_action = S_Enemy::ACTION::ACT_NEUTRAL;
//	
//	
//}
//
//void S_Enemy::Draw() {
//
//	// ���f���`��
//	//m_model->Draw(m_mtx);
//
//}
//
//void S_Enemy::DrawWithAxis() {
//
//	// ���f���`��
//	drawaxis(m_mtx, 200, m_pos);
//	Draw();
//
//}
//
//struct FLOAT3
//{
//	float x, y, z;
//};
//
////
////void S_Enemy::AutoMove()
////{
////	
////	//��������
////	std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(S_Enemy::ACTION::MAX_ACTION) - 1);
////
////	if (PlayerMgr::GetInstance()->Player_List.at(0)->judge_flg == false)//�v���C���[�̈ړ����肪�I������t���O
////	{
////		
////		if (m_action == S_Enemy::ACTION::ACT_NEUTRAL)
////		{
////		
////		
////			g_nowrotcnt = 0;
////			//�s��쐬�i�P�t���[�����̉�]��\���s����쐬�j
////			//DX11MakeWorldMatrix(g_mtxframe, g_angle, trans);
////
////
////			//�J�n�ʒu��ۑ�
////			g_startpos.x = m_mtx._41;//X���W��ۑ�
////			g_startpos.y = m_mtx._42;//Y���W��ۑ�
////			g_startpos.z = m_mtx._43;//Z���W��ۑ�
////
////			m_action = static_cast<ACTION>(rand4(m_mt));
////
////			
////		}
////		//debuglog((int)m_action);
////		//debuglog(e);
////		if((m_action != S_Enemy::ACTION::ACT_NEUTRAL) && (enemy_turn_flg == false))
////		{
////			//�ړ��ʂ̌v�Z
////			XMFLOAT3 pos = { g_startpos.x,0.0f,g_startpos.z };
////
////			float t;
////			float s;
////
////			t = static_cast<float>(g_nowrotcnt + 1) / static_cast<float>(g_rotcnt);
////			s = 1 / static_cast<float>(g_rotcnt);
////
////
////			
////
////			//�A�N�V�����ɂ���]���Z�b�g
////			switch (m_action) {
////
////			case S_Enemy::ACTION::ACT_LEFT://����]�iY���j
////			//�I���ʒu���v�Z
////				endpos.x = g_startpos.x - 15.0f;
////				//���`�ۊǂ̎���X���W���v�Z
////				pos.x = g_startpos.x * (1.0f - t) + endpos.x * t;
////				break;
////			case S_Enemy::ACTION::ACT_RIGHT://�E��]�iY���j
////
////		//�I���ʒu���v�Z
////				endpos.x = g_startpos.x + 15.0f;
////				//���`�ۊǂ̎���X���W���v�Z
////				pos.x = g_startpos.x * (1.0f - t) + endpos.x * t;
////				break;
////			case S_Enemy::ACTION::ACT_UP://���]�iX���j
////
////				//�I���ʒu���v�Z
////				endpos.z = g_startpos.z + 15.0f;
////				//���`�ۊǂ̎���X���W���v�Z
////				pos.z = g_startpos.z * (1.0f - t) + endpos.z * t;
////				break;
////
////			case S_Enemy::ACTION::ACT_DOWN://���]�iX���j
////
////				//�I���ʒu���v�Z
////				endpos.z = g_startpos.z - 15.0f;
////				//���`�ۊǂ̎���X���W���v�Z
////				pos.z = g_startpos.z * (1.0f - t) + endpos.z * t;
////				break;
////			}
////		//	////��]�����J�E���g�A�b�v
////			g_nowrotcnt++;
////			if (g_nowrotcnt >= g_rotcnt) {
////				m_action = S_Enemy::ACTION::ACT_NEUTRAL;
////				enemy_turn_flg = true;
////
////			}
////
////			m_mtx._41 = pos.x;
////			m_mtx._42 = pos.y;
////			m_mtx._43 = pos.z;
////
////		}
////	}
////	//if (PlayerMgr::GetInstance()->Player_List.at(0)->judge_flg)
////	//{
////	//	if (enemy_turn_flg == true)
////	//	{
////	//		enemy_turn_flg = false;
////	//	}
////	//}
////
////
////}
////
//
//void S_Enemy::Action()
//{
//
//}
//
//void S_Enemy::Update() {
//	//if (m_sts == S_ENEMY_STATUS::S_ENEMY_LIVE)
//	//{
//	////	SetPos(XMFLOAT3(0.0f,0.0f,-150.0f));
//	//	AutoMove();
//	//}
//}
//
//void S_Enemy::Finalize() {
//	m_model->Uninit();
//
//}
