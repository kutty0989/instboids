#pragma once
#include	"gameobject.h"
#include	"CModel.h"
#include	"dx11mathutil.h"
#include"myutil.h"
#include    "XAudio2.h"
#include"BoidsHp.h"
#include"CModelInstance.h"

//#include"UniqueEnemy.h"
//#include"UniqueEnemy_Bomb.h"

class UniqueEnemy_Bomb;
#define		ENEMYMAX		1
#define		ZOMBIEMAX		2
#define		ZOMBIE		    10
#define		HYUMANMAX		100


class Player :public GameObject {
private:


	CModel* m_model;						// �R�c���f��
	CModelInstance* m_instancemodel;						// �R�c���f��
	BoidsHp boidshp; //hpbar�̃r���{�[�h
	float anglecos;
	double col;//�v���C���[�̏ꏊ�̃J���[�������
	double gocol;//�����Ă�����̍������
	float defcol;//�v���C���[�̏ꏊ�ƍs��̍�
	float goangle;//�v���C���[�ƍs��̊p�x	

	float move_rig;
	XMFLOAT4 axisX;//X��
	XMFLOAT4 axisY;//Y��
	XMFLOAT4 axisZ;//Z��



	XMFLOAT3 screenpos;
	Pvector vel;
	Pvector ali_vel;//�t���b�N����̃x�N�g��

	


public:
	XMFLOAT2 angley;//�p�x�ۑ��p
	XMFLOAT4X4 rot = {};
	XMFLOAT4X4 scale = {};
	XMFLOAT4X4 trans = {};
	XMFLOAT4X4 world = {};
	float b_angle = 0.0f;

	XMFLOAT2 left_vec;//��������{90�x�̊p�x
	XMFLOAT2 right_vec;//��������-90�x�̊p�x
	XMFLOAT2 opposite_vec;//��������{180�x�̊p�x
	float left_angle;
	float right_angle;
	float opposite_angle;

	Pvector uedesired;//�v�Z�p�̕ϐ�
	Pvector uesteer;//�v�Z�p�̕ϐ�

	Pvector ueser = { 0,0 };
	Pvector uesep = { 0,0 };
	Pvector ueatt = { 0,0 };


	static Player* GetInstance()
	{
		static Player instance;
		return &instance;
	}

	void CheckBox();

	/// <summary>
	///�������Ă��邩�ǂ���
	/// </summary>
	/// <returns>Live Dead</returns>
	STATUS IsLive()
	{
		if (m_sts == STATUS::LIVE)
		{
			return STATUS::LIVE;
		}

		else if (m_sts == STATUS::DEAD)
		{
			return STATUS::DEAD;
		}
		else
		{
			STATUS::DEAD;
		}
	}

	int GetHp();

	enum class DIRECTION
	{
		NEUTRAL = 0,

		UP,
		DOWN,
		LEFT,
		RIGHT
	};


	bool Init();

	bool CharengerInit();

	void Draw(int animenum);

	void HyumanDrawAxis();

	void DrawWithAxis();

	void Update(bool input);

	void ZonbieUpdate(int animnum, int i);

	void FollowUpdate();


	void Finalize();

	XMFLOAT3 Screenpos(XMFLOAT3 World_Pos);

	/*CModel* GetModel()
	{
		return m_model;
	}*/
	CModelInstance* GetInstanceModel()
	{
		return m_instancemodel;
	}

	void SetScale(float x, float y, float z)
	{
		m_mtx._11 = x;
		m_mtx._22 = y;
		m_mtx._33 = z;
	}

	void SetModel(CModel* model)
	{
		m_model = model;
	}
	void SetInstanceModel(CModelInstance* model)
	{
		m_instancemodel = model;
	}
	void Loadanimation()
	{

	}
	void SetPos(XMFLOAT3 pos)
	{
		m_pos = pos;
	}

	void SetColor(XMFLOAT4 col)
	{
		m_color = col;
	}

	void SetAngle();

	XMFLOAT3 GetAngle();

	void  SetQutenion()
	{

		//X�������o��
		axisX.x = m_mtx._11;
		axisX.y = m_mtx._12;
		axisX.z = m_mtx._13;
		axisX.w = 0.0f;

		//X�������o��
		axisY.x = m_mtx._21;
		axisY.y = m_mtx._22;
		axisY.z = m_mtx._23;
		axisY.w = 0.0f;

		//Z�������o��
		axisZ.x = m_mtx._31;
		axisZ.y = m_mtx._32;
		axisZ.z = m_mtx._33;
		axisZ.w = 0.0f;
	}

	void SetAPower(float power)
	{
		anglecos = power;
	}

	
public:
	int groundcnt = 0;
	float beforeangley;
	XMFLOAT3 angle{ 0,0,0 };
	int hp = 3;
	int zonbieanime = 0;//���݂̃A�j���[�V�����ԍ�
	int anglecnt = 0;//���J�E���g���ƂɊp�x��ς���
	int awaycnt = 0;//���x�𗎂Ƃ�����������
	int sepcnt = 0;
	float boid_accel;//���x�{��
	bool champion;//�������L����
	bool predator;//�G���ǂ����̃t���O
	Pvector location;//�|�W�V����
	Pvector velocity;//�����Ƌ����@���x
	Pvector acceleration;//�����x
	float maxSpeed;//�ō����x
	float maxForce;//�Ȃ���͂̋����@������΂܂�����
	bool insideflg = false;//�}�E�X�ň͂������ɂ��邩v
	bool awayflg = false;//�ǂ������Ăǂ����ւ����t���O
	bool zexplosionflg = false;
	int initZombie;
	bool reborn_flg = false;
	bool alifalse_flg = false;
	float alifalse_cnt = -10;
	XMFLOAT3 rebornpos;
	enum class Follow
	{
		
	
		ZONBIE,
		HYUMAN,
		ENEMY
	};
	enum class BSTATUS
	{
		LIVE,
		DEAD,
		ASPHTXIA
	};

	BSTATUS bstatus;
	Follow follow;

	void boid_Init(float x, float y);//�v���C���[�ȊO�̏�����
	void zonbie_Init(float x, float y,int nowzombicnt);//�]���r�̏�����
	void boid_player_Init(float x, float y);//�������L�����̏�����
	void follow_Init();
	//Boid(float x, float y, bool predCheck);

	void applyForce(const Pvector& force);//3�@���������x�ɉ�����
	// Three Laws that boids follow

	/// <summary>
	///�z��P����z��Q�Ɉړ����A�폜����
	/// </summary>
	/// <param name="arraynum">�v�f�ԍ�</param>
	/// <param name="Player_Vector1"></param>
	/// <param name="Player_Vector2"></param>
	void Move_And_Delete(float arraynum, std::vector<Player*> Player_Vector1, std::vector<Player*> Player_Vector2);

	void Delete(float arraynum, std::vector<Player*> Player_Vector1);

	/// <summary>
	/// �����@�߂Â��������痣���悤��
	/// </summary>
	/// <param name="Player_Vector">boids�̔z��</param>
	/// <returns>�����x�N�g��</returns>
	Pvector boid_Separation(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector);
	
	
	Pvector boid_Avoid(std::vector<Player*> player_vector);
	/// <summary>
	/// �����@�v���C���[�͈̔͂ɂ���boids���߂Â������Ȃ��悤��
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	/// <returns></returns>
	Pvector boid_inSeparation(std::vector<Player*> player_vector);
	/// <summary>
	/// ���� ����Ƒ��x�ƕ��������킹��
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <returns></returns>
	Pvector boid_Alignment(std::vector<Player*> player_vector);

	/// <summary>
		/// �v���C���[�͈̔͂ɂ���boids���v���C���[�̑��x�ƕ��������킹��
		/// </summary>
		/// <param name="Player_Vector"></param>
		/// <param name="implayer"></param>
		/// <returns></returns>
	Pvector boid_zonbieAlignment(Pvector mousepos);

	/// <summary>
	/// �ǐՁ@�l�Ԃ�ǂ������A�ǂ�����������߂�
	/// </summary>
	/// <param name="player_vector"></param>
	/// <returns></returns>
	Pvector boid_zonbieAway(std::vector<Player*> human_vector);

	/// <summary>
	/// �T���@���낤�낷��
	/// </summary>
	/// <returns></returns>
	Pvector boid_zonbieSearch();

	/// <summary>
	/// �����@����ɂ���bboids�̒��S�֌��������Ƃ���
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <returns></returns>
	Pvector boid_Cohesion(std::vector<Player*> player_vector);

	/// <summary>
	/// ���U�@�]���r���}�E�X�̏ꏊ���痣��Ă���
	/// </summary>
	/// <returns></returns>
	Pvector zonbie_Scatter();
	/// <summary>
	/// �����@�v���C���[�͈̔͂ɂ���boids���v���C���[�Ɍ�����
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	/// <returns></returns>
	Pvector boid_inCohesion(std::vector<Player*> player_vector);
	//Functions involving SFML and visualisation linking

	/// <summary>
	/// �ō����x�ɐ������ړI�n�֌�����
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	Pvector boid_seek(const Pvector& v);
	/// <summary>
	/// ����p��O��90�x��
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	/// <returns></returns>
	Pvector boid_view(std::vector<Player*> player_vector);
	/// <summary>
	/// mgr�N���X�ŌĂяo���֐��@update��Z�߂���
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	void boid_run(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector);

	/// <summary>
	/// mgr�N���X�ŌĂяo���֐��@update��Z�߂���
	/// </summary>
	/// <param name="player_vector"></param>
	/// <param name="human_vector"></param>
	/// <param name="mousevec"></param>
	void zonbie_run(std::vector<Player*> player_vector, std::vector<Player*> human_vector, Pvector mousevec);
	/// <summary>
	/// ���x������boids�̈ʒu���X�V
	/// </summary>
	void boid_update();
	/// <summary>
	/// �R�@����Z�ߏd�݂Â�������
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	void boid_flock(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector);

	/// <summary>
	/// �]���r�Ɋe���[����K�p���d�݂Â�
	/// </summary>
	void zonbie_flock(std::vector<Player*> zonbie_vector, std::vector<Player*> human_vector, Pvector mousevec);
	/// <summary>
	/// ��ʊO�ɏo���Ƃ��ɔ��΂̉�ʂ���o��悤��
	/// </summary>
	void boid_borders();

	void zombie_reborn(float x, float y,float z);

	/// <summary>
	/// �p�x�����߂�
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	float boid_angle(const Pvector& v);

	void boids_attack(std::vector<Player*>& player_vector, Player& zonbie, std::vector<UniqueEnemy_Bomb>& unique_enemy_vector);

	Pvector zonbie_damage();



	//�O���[�o���ϐ��̑���ɁA�Q�[�����̒l�Əd�݂ɃA�N�Z�X���邽�߂Ɏg�p����	float desSep;

	float desSep;//�����̎���
	float desAli;//����̎���
	float desCoh;//�����̎���
	float SepW;//�����̏d��
	float AliW;//����̏d��
	float CohW;//�����̏d��

	float getDesSep() const;
	float getDesAli() const;
	float getDesCoh() const;
	float getSepW() const;
	float getAliW() const;
	float getCohW() const;

	void setDesSep(float x);
	void setDesAli(float x);
	void setDesCoh(float x);
	void setSepW(float x);
	void setAliW(float x);
	void setCohW(float x);


public:

	static bool hsepflg;
	static bool haliflg;


	static bool zdashflg;
	static bool zscaflg;
	static bool zsepflg;
	static bool zcohflg;
	static bool zserflg;
	static bool zawaflg;

	static bool dmgflg;
	static bool changeflg;

	static bool bbombflg;
	static bool bserflg;
	
	//�l�Ԃ̑���
	static float hyumanmaxspeed;//1.5
	static float hyumanrandspeed;//5

	//hyumanali
	static float alidist;//40


	//hyumnsep
	static float sepdist;//10
	static float sepzonbiedist;//30
	static float sepspeed;//2.0
	static float septime;//30


	static float zonbiehp;//�Q
	static float zonbiemaxspeed;//8.5
	static float zonbiedownspeed;//0.05f
	
	//zonbiedamage
	static float bombdist;//100
	//zonbiesearch
	static int Searchcnt;//70
	static float Seachspeed;//0.3f
	static float Seachtime;//50

	static float chasedist;//50
	static float chasespeed;//1.5
	static float chasetime;//30

	static float Dashspeed;//3.5f
	static float Dashtime;//40

	//zonbiesep
	static float Sepdist;//10
	static float Sepspeed;//1.0

	//�W�����x
	static float cohspeed;//�P�D�O

	//�]���r�Ƃ̃_���[�W����
	static float zombirange;//15
	static float damage;//�P�D�O


	//away
	static float zombiawayspeed;//1.5
	static float zombieawaytime;//�P�O

	static bool save;
	static bool load;

	void SetNum();
	void SaveNum();
	void LoadNum();
	void Gui();
};