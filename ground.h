#pragma once
//=============================================================================
//
// �n�`�����ۂɍ��X�V����N���X [ground.h]
//
//=============================================================================
#include"CHeight_Map.h"
#include"gameobject.h"
#include"BoidsAI.h"
class Ground:public GameObject
{
public:

	bool Init();

	void Draw();

	void Update();

	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="BoidsAI"></param>
	void GetBoidsAIHeight(BoidsAI& BoidsAI);


	Pvector DownBoid(BoidsAI& BoidsAI);

	float AccelBoid(BoidsAI& BoidsAI);


	void DefangleAccel(BoidsAI& BoidsAI,float accel);

	void Finalize();

	float TexSpeed(float boid_accel);

	XMFLOAT3 GetPos();
	float GetWidthHeight();
	
	static Ground* GetInstance()
	{
		static Ground instance;
		return &instance;
	}

	float scaling = 2.0f;//�摜���������΂��{��

private:
	XMFLOAT3 m_scale = { 1.0f,1.0f,1.0f };
	XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };
	CHeight_Map* g_heightmap;


	double col = 0.0;//�v���C���[�̏ꏊ�̃J���[�������
	double gocol = 0.0;//�����Ă�����̍������
	double nowcol = 0.0;//�����Ă�����̍������
	double lgocol = 0.0;//�����Ă�����̍������
	double rgocol = 0.0;//�����Ă�����̍������
	double bgocol = 0.0;//�����Ă�����̍������
	double defcol = 0.0;//�v���C���[�̏ꏊ�ƍs��̍�
	float goangle = 0.0f;//�v���C���[�ƍs��̊p�x


	int anglecnt = 0;
	int anglechangecnt = 0;

	enum class Angle_Direction
	{
		Normal,
		Left,
		Right,
	};

	Angle_Direction angle_direction = Angle_Direction::Normal;

};