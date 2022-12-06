#pragma once
#include	<assert.h>
#include	<random>
#include	<stdlib.h>
#include	"gameobject.h"
#include	"CModel.h"
#include	"DX11util.h"
#include"CModelInstance.h"
#include	"DX11Settransform.h"

class enemy : public GameObject {
	CModelInstance* m_model;
	float				m_speed = 1.0f;			// �X�s�[�h

	DirectX::XMFLOAT3	m_angle = { 0.0f, 0.0f, 0.0f };
	std::mt19937		m_mt;
	std::mt19937		m_mt2;
	enum STS {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ROLLP,
		ROLLM,
		STRAIGHT,
		ACTIONMAX
	};
	unsigned int		m_action = STRAIGHT;
	unsigned int		m_counter;
public:
	void Init(CModelInstance* pmodel) {
		m_model = pmodel;

		std::random_device  m_rnd;     // �񌈒�I�ȗ���������
									   // �V�[�h�l��^����
		m_mt.seed(m_rnd());
		m_mt2.seed(m_rnd());

		m_action = 3;
		m_counter = 10;

		//GameObject::Init();
	}

	void Exit() {
	}

	void Update() {
		// �p�����擾
		XMFLOAT4X4 mat;
		XMFLOAT4 axisx, axisy, axisz;
		XMFLOAT4 qtx, qty, qtz;

		Autopilot();				// �������c

		DX11MtxFromQt(mat, m_rotation);		// �N�I�[�^�j�I�����s��ɂ���

		// �������擾
		axisx.x = mat._11;
		axisx.y = mat._12;
		axisx.z = mat._13;
		axisx.w = 0.0f;

		axisy.x = mat._21;
		axisy.y = mat._22;
		axisy.z = mat._23;
		axisy.w = 0.0f;

		axisz.x = mat._31;
		axisz.y = mat._32;
		axisz.z = mat._33;
		axisz.w = 0.0f;

		// ���𒆐S�ɉ�]����N�I�[�^�j�I���𐶐�����
		DX11QtRotationAxis(qtx, axisx, m_angle.x);
		DX11QtRotationAxis(qty, axisy, m_angle.y);
		DX11QtRotationAxis(qtz, axisz, m_angle.z);

		// ���݂̎p�������]�������N�I�[�^�j�I�������߂�
		// �N�I�[�^�j�I��������
		XMFLOAT4 tempqt1;
		DX11QtMul(tempqt1, m_rotation, qtx);

		XMFLOAT4 tempqt2;
		DX11QtMul(tempqt2, qty, qtz);

		DX11QtMul(m_rotation, tempqt1, tempqt2);

		// �N�I�[�^�j�I�����m�[�}���C�Y
		DX11QtNormalize(m_rotation, m_rotation);

		DX11MtxFromQt(mat, m_rotation);		// �N�I�[�^�j�I�����s��ɂ���

		// �y�������o��
		axisz.x = mat._31;
		axisz.y = mat._32;
		axisz.z = mat._33;
		axisz.w = 0.0f;

		// �i�s�����ɐi��
		m_pos.x = rand() % 1000;
		m_pos.y += axisz.y * m_speed;
		m_pos.z = rand() % 1000;
	}

	void Autopilot() {
		std::uniform_int_distribution<int> rand4(0, ACTIONMAX - 1);
		std::uniform_int_distribution<int> rand10(10, 50);

		m_angle.x = m_angle.y = m_angle.z = 0.0f;

		switch (m_action) {
		case LEFT:
			m_angle.y = 1.0f;
			break;
		case RIGHT:
			m_angle.y = -1.0f;
			break;
		case UP:
			m_angle.x = 1.0f;
			break;
		case DOWN:
			m_angle.x = -1.0f;
			break;
		case ROLLP:
			m_angle.z = -1.0f;
			break;
		case ROLLM:
			m_angle.z = 1.0f;
			break;
		case STRAIGHT:
			m_angle.x = m_angle.y = m_angle.z = 0.0f;
			break;
		}

		m_counter--;

		if (m_counter <= 0) {
			m_action = rand4(m_mt);
			m_counter = rand10(m_mt2);
		}
	}

	XMFLOAT3& GetPos() {
		return m_pos;
	}

	void Draw() {
		XMFLOAT4X4	world;
		DX11MtxFromQt(world, m_rotation);
		world._41 = m_pos.x;
		world._42 = m_pos.y;
		world._43 = m_pos.z;

		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, world);
		// ��s�@�`��
		m_model->Draw();
	}
};