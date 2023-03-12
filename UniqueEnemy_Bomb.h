#pragma once
#pragma once
#include"BoidsAI.h"
#include"CModelInstance.h"
#include"UniqueBombHp.h"
class UniqueEnemy_Bomb :public BoidsAI
{

	XMFLOAT4 axisX;//Xé≤
	XMFLOAT4 axisY;//Yé≤
	XMFLOAT4 axisZ;//Zé≤
	UniqueBombHp uniquebombhp;
	Pvector nearBoidsAI;//àÍî‘ãﬂÇ¢ë∂ç›Çï€ë∂Ç∑ÇÈïœêî
	XMFLOAT3 zpos;
	bool zonbienearflg = false;
	int bombcnt = 0;
	int escapecnt = 0;
	int maxhp = 25;
public:
	XMFLOAT2 angley;

	bool attackflg = false;

	int b_animecnt = 0;
	bool animereset = false;
	CModel* um_model;						// ÇRÇcÉÇÉfÉã
	CModelInstance* um_instancemodel;						// ÇRÇcÉÇÉfÉã

	bool Init();

	void Draw(std::vector<BoidsAI>& zonbie_vector);

	void Update(std::vector<BoidsAI*>& pvec, std::vector<ZombieBullet*>& zbvec);

	void UEnemy_run(std::vector<BoidsAI*>& zonbie_vector);

	void UEnemy_flock(std::vector<BoidsAI*>& zonbie_vector);

	void UEnemy_update();

	Pvector UEnemy_Search();

	Pvector UEnemy_Separation(std::vector<BoidsAI>& zonbie_vector);

	Pvector UEnemy_Attack(std::vector<BoidsAI*>& zonbie_vector);
	
	Pvector UEnemy_Escape(std::vector<BoidsAI>& zonbie_vector);
	
	void UEnemy_Dmg(std::vector<BoidsAI*>& zonbie_vector);

	int UEnemy_GetAnime();

	void  UEDelete(float arraynum, std::vector<UniqueEnemy_Bomb>& BoidsAI_Vector1);

	void UpdateHP();

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

	enum class UBSTATUS
	{
		LIVE,
		DEAD,
		ASPHTXIA
	};

	UBSTATUS ubstatus;
};