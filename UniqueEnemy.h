#pragma once
#include"player.h"

class UniqueEnemy :public Player
{
	


	XMFLOAT4 axisX;//XŽ²
	XMFLOAT4 axisY;//YŽ²
	XMFLOAT4 axisZ;//ZŽ²



public:
	XMFLOAT2 angley;

	bool attackflg = false;
	
	int b_animecnt = 0;
	bool animereset = false;
	CModel* um_model;						// ‚R‚cƒ‚ƒfƒ‹
	
	bool Init();

	void Draw(std::vector<shared_ptr<Player>>& zonbie_vector);

	void Update();

	void UEnemy_run(std::vector<Player>& zonbie_vector);

	void UEnemy_flock(std::vector<Player>& zonbie_vector);

	void UEnemy_update();

	Pvector UEnemy_Search();

	Pvector UEnemy_Separation(std::vector<Player>& zonbie_vector);
	
	Pvector UEnemy_Attack(std::vector<Player>& zonbie_vector);

	int UEnemy_GetAnime();


	void SetModel(CModel* model)
	{
		um_model = model;
	}


	enum class UNIQUE_ENEMY_ANIME
	{
		IDLE,
		MOVE,
		ATTACK
	};

	struct modelanime
	{
		int m_cnt =0;
		int m_Frame;
		int m_preFrame;
		float m_factor;
		int animecnt = 0;
	};

	modelanime manime;
	UNIQUE_ENEMY_ANIME unique_enemy_anime = UNIQUE_ENEMY_ANIME::IDLE;
};