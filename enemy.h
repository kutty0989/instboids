//#pragma once
//#include<random>
//#include"gameobject.h"
//#include"CModel.h"
//#include"dx11mathutil.h"
//#include"CDirectInput.h"
//
//class Enemy : public GameObject {
//private:
//	CModel *m_model;//�R�����f��
//
//	//���
//	enum class STATUS {
//		S1_MOVE_FLY = 0,
//		S1_MOVE_BOMB,
//	};
//
//	enum class ACTION {
//		ACT_LEFT = 0,
//		ACT_RIGHT,
//		ACT_UP,
//		ACT_DOWN,
//		ACT_ROLLP,
//		ACT_ROLLM,
//		ACT_STRAIGHT,
//
//		MAX_ACTION
//	};
//
//	float m_speed = 0.01f;//�X�s�[�h
//
//	XMFLOAT3  m_angle;//��]�p
//
//	std::mt19937  m_mt;//���������p
//	std::mt19937  m_mt2;
//
//	ACTION   m_action;//�A�N�V�������
//	unsigned int  m_actionKeepTime; //�A�N�V�����J�E���^
//
//
//public:
//
//	
//	bool Init();
//
//	void Draw();
//
//	void DrawWithAxis();
//
//	void Update();
//
//	void Finalize();
//
//	void AutoPilot();
//
//	STATUS enemystatus = STATUS::S1_MOVE_FLY;
//
//	bool isLive() {
//		if (enemystatus == STATUS::S1_MOVE_FLY) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//
//	void isDead()
//	{
//		enemystatus = STATUS::S1_MOVE_BOMB;
//	}
//
//	void LiveOrDead(XMFLOAT3 target);
//
//	CModel* GetModel() {
//		return m_model;
//	}
//
//	void SetModel(CModel* model)
//	{
//		m_model = model;
//	}
//
//	void SetPos(float x, float y, float z)
//	{
//		m_pos.x = x;
//		m_pos.y = y;
//		m_pos.z = z;
//	}
//
//	XMFLOAT3 GetPos()
//	{
//		return(XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43));
//	}
//
//};