#pragma once
//=============================================================================
//
// 地形を実際に作り更新するクラス [ground.h]
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
	/// 高さ情報を取る
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

	float scaling = 2.0f;//画像を引き延ばす倍率

private:
	XMFLOAT3 m_scale = { 1.0f,1.0f,1.0f };
	XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };
	CHeight_Map* g_heightmap;


	double col = 0.0;//プレイヤーの場所のカラー高さ情報
	double gocol = 0.0;//向いてる方向の高さ情報
	double nowcol = 0.0;//向いてる方向の高さ情報
	double lgocol = 0.0;//向いてる方向の高さ情報
	double rgocol = 0.0;//向いてる方向の高さ情報
	double bgocol = 0.0;//向いてる方向の高さ情報
	double defcol = 0.0;//プレイヤーの場所と行先の差
	float goangle = 0.0f;//プレイヤーと行先の角度


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