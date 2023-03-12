//=============================================================================
//
// ���̒e�̐����N���X [bullet.cpp]
//
//=============================================================================

#include  <memory>
#include  "bullet.h"
#include  "dx11mathutil.h"
#include  "CModel.h"
#include  "CDirectInput.h"
#include  "ModelMgr.h"
#include <time.h>
#include "DX11Settransform.h"
#include<iostream>
#include"CCamera.h"
#include"billboardMgr.h"

constexpr float BULLETSPEED = 15.0f;//�o���b�g�̑���
constexpr uint32_t BULLETLIFE = 60;//��������
#define debuglog(a) std::cout<<a<<std::endl;

/// <summary>
/// �e�̏���������
/// </summary>
/// <returns>����</returns>
bool Bullet::Init() {
	bool sts = true;

	//�s��̏�����
	DX11MtxIdentity(m_mtx);
	m_life = 0;
	//cpu_time = clock();
	//sec = (double)cpu_time / CLOCKS_PER_SEC;*/
	m_sts = BULLETSTATUS::DEAD;

	XMFLOAT4X4 s_mtx;//�X�P�[���p�̕ϐ�

	SetScale(1.1f, 1.1f, 1.1f);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);//�X�P�[���s��
	
	//�s��|���Z
	DX11MtxMultiply(m_mtx, m_mtx, s_mtx);
	return sts;
}

/// <summary>
/// �e�̍Đ����֐��@�Ăяo���ƈ����̏ꏊ�ɐ���
/// </summary>
/// <param name="pos">�����������ꏊ</param>
void Bullet::Remake(XMFLOAT3 pos)
{
	m_life = 60;
	m_sts = BULLETSTATUS::LIVE;
	enemypos = pos;
	nowpos = m_pos;
}

/// <summary>
/// �`��
/// </summary>
void Bullet::Draw() {

	//�����Ă���e�����`��
	if (m_sts == BULLETSTATUS::LIVE) {
	
		m_pmodel->Draw(m_mtx);
	}
}
//go ���̍��W�l
//to�@�s��̍��W�l
//ratio�@���݂̐i�s�����@0.0f�`1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

/// <summary>
/// �e�̍X�V
/// </summary>
void Bullet::Update()
{
	//�����G�t�F�N�g�̍X�V
	BillBoardExplosion();
	explosion = false;

	//�����Ă���e�����X�V
	if (m_sts == BULLETSTATUS::LIVE) {

		//�s��v�Z
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

		//�X�P�[���Z�b�g
		scale._11 = 2.2f;
		scale._22 = 2.2f;
		scale._33 = 2.2f;

		//�����܂ł̃J�E���g�_�E��
		m_life--;
		explocnt -= 1;

		//�e�������Ă����
		if (m_life > 0) {
			//���˕����Ɍ����ăX�s�[�h���@�����^��

			float time = m_life / 60.0f;

			//�ꏊ��ړI�n�܂ŕ⊮
			time = abs(1 - time);
			float posx = LeapID<float>(nowpos.x, enemypos.x, time);
			float posy = LeapID<float>(nowpos.y, enemypos.y, time);
			float posz = LeapID<float>(nowpos.z, enemypos.z, time);

			//�ꏊ���X�V
			trans._41 = posx;
			trans._42 = posy + 4.0f;
			trans._43 = posz;

			//�����x�N�g�����擾
			XMFLOAT2 angley;
			angley.x = enemypos.x - nowpos.x;
			angley.y = enemypos.z - nowpos.z;

			angle.y = 0.0f;

			//������ύX
			angle.y = -GetKakudo(angley.x, angley.y);
			angle.y -= 90.0f;

			float ang = angle.y;

			XMFLOAT4 qty = {};//�N�H�[�^�j�I��
	
			XMFLOAT4 axisY;//Y��
	

			//X�������o��
			axisY.x = m_mtx._21;
			axisY.y = m_mtx._22;
			axisY.z = m_mtx._23;
			axisY.w = 0.0f;

			//�w�莲��]�̃N�H�[�^�j�I���𐶐�
			DX11QtRotationAxis(qty, axisY, angle.y);

			//�N�H�[�^�j�I�����m�[�}���C�Y
			DX11QtNormalize(qty, qty);

			SetRotation(qty);

			//�N�H�[�^�j�I������s����쐬
			DX11MtxFromQt(rot, qty);

			DX11MtxMultiply(world, scale, rot);

			//�s����Z�b�g
			world._41 = trans._41;
			world._42 = trans._42;
			world._43 = trans._43;

			m_mtx = world;
		}
		if (m_life == 1)
		{
			//��������
			explocnt = 100;
			goalpoint = true;
		}
		if (goalpoint)
		{
			if (explocnt < 0)
			{
				m_sts = BULLETSTATUS::DEAD;
				goalpoint = false;
				explosion = true;
			}
		}
	}
}

/// <summary>
/// �������Ăяo���ׂ̊֐�
/// </summary>
void Bullet::BillBoardExplosion()
{
	if (explosion)
	{
		CCamera::GetInstance()->blowflg = true;
		BillBoardMgr::GetInstance()->GranateCreate(XMFLOAT3(m_mtx._41,m_mtx._42,m_mtx._43));
		
	}
}

