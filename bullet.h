//=============================================================================
//
// ���̒e�̐����N���X [bullet.h]
//
//=============================================================================

#pragma once
#include<DirectXMath.h>
#include<vector>
#include<memory>
#include"gameobject.h"

//�O���錾
class CModel;

//�e�X�e�[�^�X
enum class BULLETSTATUS {
	LIVE,
	DEAD
};

class Bullet :public GameObject {
private:
	
	//�e�̍s��
	XMFLOAT4X4 rot = {};
	XMFLOAT4X4 scale = {};
	XMFLOAT4X4 trans = {};
	XMFLOAT4X4 world = {};

	XMFLOAT3 angle{ 0,0,0 };//��]�p

	CModel* m_pmodel;//�RD���f��
	DirectX::XMFLOAT3 m_direction;//���˕���
	DirectX::XMFLOAT3 m_pos;

	float m_speed = 2.0f;//�e�̃X�s�[�h

	DirectX::XMFLOAT3 m_scale;

	XMFLOAT3 enemypos;//�W�I�̏ꏊ
	
	bool goalpoint = false;//�ړI�n�ɂ������̔��f
	
public:

	XMFLOAT3 nowpos;
	bool explosion = false;//�������Ă������̕ϐ�
	BULLETSTATUS  m_sts;//�X�e�[�^�X
	float m_life = 0;//�e�̏��ł܂ł̎���
	float explocnt = 0;//�����܂ł̕ϐ�

	//�e�̏�����
	bool Init();

	//�e�̍Đ���
	void Remake(XMFLOAT3 pos);

	//�e�̕`��
	void Draw();

	//�X�V
	void Update();

	//�I������
	void Finalize(){};

	//�e�̃��f�����Z�b�g
	void SetModel(CModel* p) {
		m_pmodel = p;
	}

	//�e�̃��f��������Ă���
	CModel* GetModel() {
		return m_pmodel;
	}

	//�������Z�b�g����
	void SetDirection(DirectX::XMFLOAT4X4 mtx) {
		m_mtx = mtx;
		m_direction = DirectX::XMFLOAT3(mtx._31, mtx._32, mtx._33);
	}

	//�����Ă��邩���f����֐�
	bool isLive() {
		if (m_sts == BULLETSTATUS::LIVE) {
			return true;
		}
		else {
			return false;
		}
	}

	//�����l���Z�b�g����֐�
	void SetInitialPos(float x, float y, float z)
	{
		m_pos = { x,y,z };
	}

	//�傫�����Z�b�g����֐�
	void SetScale(float x, float y, float z)
	{
		m_scale = { x,y,z };
	}

	//�����̃r���{�[�h��`�悷��ׂ̊֐�
	void BillBoardExplosion();

};