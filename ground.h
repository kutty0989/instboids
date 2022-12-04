#pragma once
#include"CHeight_Map.h"
#include"gameobject.h"
#include"player.h"
class Ground:public GameObject
{
public:

	bool Init();

	void Draw();

	void Update();

	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="player"></param>
	void GetPlayerHeight(Player& player);

	void DefangleAccel(Player& player,float accel);

	void Finalize();

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
	double defcol = 0.0;//�v���C���[�̏ꏊ�ƍs��̍�
	float goangle = 0.0f;//�v���C���[�ƍs��̊p�x
};