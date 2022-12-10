#pragma once
#pragma once
#include"player.h"
#include"CModelInstance.h"

class UniqueEnemy_Bomb :public Player
{

	XMFLOAT4 axisX;//Xé≤
	XMFLOAT4 axisY;//Yé≤
	XMFLOAT4 axisZ;//Zé≤

	Pvector nearplayer;//àÍî‘ãﬂÇ¢ë∂ç›Çï€ë∂Ç∑ÇÈïœêî
	XMFLOAT3 zpos;
	bool zonbienearflg = false;
	int bombcnt = 0;
public:
	XMFLOAT2 angley;

	bool attackflg = false;

	int b_animecnt = 0;
	bool animereset = false;
	CModel* um_model;						// ÇRÇcÉÇÉfÉã
	CModelInstance* um_instancemodel;						// ÇRÇcÉÇÉfÉã

	bool Init();

	void Draw(std::vector<shared_ptr<Player>>& zonbie_vector);

	void Update();

	void UEnemy_run(std::vector<shared_ptr<Player>>& zonbie_vector);

	void UEnemy_flock(std::vector<shared_ptr<Player>>& zonbie_vector);

	void UEnemy_update();

	Pvector UEnemy_Search();

	Pvector UEnemy_Separation(std::vector<shared_ptr<Player>>& zonbie_vector);

	Pvector UEnemy_Attack(std::vector<shared_ptr<Player>>& zonbie_vector);
	
	void UEnemy_Dmg(std::vector<shared_ptr<Player>>& zonbie_vector);

	int UEnemy_GetAnime();

	void  UEDelete(float arraynum, std::vector<std::shared_ptr< UniqueEnemy_Bomb>>& Player_Vector1);


	void SetModel(CModel* model)
	{
		um_model = model;
	}

	void SetModel(CModelInstance* model)
	{
		um_instancemodel = model;
	}

	enum class UNIQUE_ENEMY_ANIME
	{
		IDLE,
		MOVE,
		ATTACK
	};

	struct modelanime
	{
		int m_cnt = 0;
		int m_Frame;
		int m_preFrame;
		float m_factor;
		int animecnt = 0;
	};

	modelanime manime;
	UNIQUE_ENEMY_ANIME unique_enemy_anime = UNIQUE_ENEMY_ANIME::IDLE;
};