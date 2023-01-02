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


	CModel* m_model;						// ３Ｄモデル
	CModelInstance* m_instancemodel;						// ３Ｄモデル
	BoidsHp boidshp; //hpbarのビルボード
	float anglecos;
	double col;//プレイヤーの場所のカラー高さ情報
	double gocol;//向いてる方向の高さ情報
	float defcol;//プレイヤーの場所と行先の差
	float goangle;//プレイヤーと行先の角度	

	float move_rig;
	XMFLOAT4 axisX;//X軸
	XMFLOAT4 axisY;//Y軸
	XMFLOAT4 axisZ;//Z軸



	XMFLOAT3 screenpos;
	Pvector vel;
	Pvector ali_vel;//フリック操作のベクトル

	


public:
	XMFLOAT2 angley;//角度保存用
	XMFLOAT4X4 rot = {};
	XMFLOAT4X4 scale = {};
	XMFLOAT4X4 trans = {};
	XMFLOAT4X4 world = {};
	float b_angle = 0.0f;

	XMFLOAT2 left_vec;//自分から＋90度の角度
	XMFLOAT2 right_vec;//自分から-90度の角度
	XMFLOAT2 opposite_vec;//自分から＋180度の角度
	float left_angle;
	float right_angle;
	float opposite_angle;

	Pvector uedesired;//計算用の変数
	Pvector uesteer;//計算用の変数

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
	///生存しているかどうか
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

		//X軸を取り出す
		axisX.x = m_mtx._11;
		axisX.y = m_mtx._12;
		axisX.z = m_mtx._13;
		axisX.w = 0.0f;

		//X軸を取り出す
		axisY.x = m_mtx._21;
		axisY.y = m_mtx._22;
		axisY.z = m_mtx._23;
		axisY.w = 0.0f;

		//Z軸を取り出す
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
	int zonbieanime = 0;//現在のアニメーション番号
	int anglecnt = 0;//一定カウントごとに角度を変える
	int awaycnt = 0;//速度を落とさず動く時間
	int sepcnt = 0;
	float boid_accel;//速度倍率
	bool champion;//動かすキャラ
	bool predator;//敵かどうかのフラグ
	Pvector location;//ポジション
	Pvector velocity;//向きと距離　速度
	Pvector acceleration;//加速度
	float maxSpeed;//最高速度
	float maxForce;//曲がる力の強さ　多きればまっすぐ
	bool insideflg = false;//マウスで囲った中にいるかv
	bool awayflg = false;//追いかけてどこかへいくフラグ
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

	void boid_Init(float x, float y);//プレイヤー以外の初期化
	void zonbie_Init(float x, float y,int nowzombicnt);//ゾンビの初期化
	void boid_player_Init(float x, float y);//動かすキャラの初期化
	void follow_Init();
	//Boid(float x, float y, bool predCheck);

	void applyForce(const Pvector& force);//3法則を加速度に加える
	// Three Laws that boids follow

	/// <summary>
	///配列１から配列２に移動し、削除する
	/// </summary>
	/// <param name="arraynum">要素番号</param>
	/// <param name="Player_Vector1"></param>
	/// <param name="Player_Vector2"></param>
	void Move_And_Delete(float arraynum, std::vector<Player*> Player_Vector1, std::vector<Player*> Player_Vector2);

	void Delete(float arraynum, std::vector<Player*> Player_Vector1);

	/// <summary>
	/// 分離　近づきすぎたら離れるように
	/// </summary>
	/// <param name="Player_Vector">boidsの配列</param>
	/// <returns>方向ベクトル</returns>
	Pvector boid_Separation(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector);
	
	
	Pvector boid_Avoid(std::vector<Player*> player_vector);
	/// <summary>
	/// 分離　プレイヤーの範囲にいるboidsが近づきすぎないように
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	/// <returns></returns>
	Pvector boid_inSeparation(std::vector<Player*> player_vector);
	/// <summary>
	/// 整列 周りと速度と方向を合わせる
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <returns></returns>
	Pvector boid_Alignment(std::vector<Player*> player_vector);

	/// <summary>
		/// プレイヤーの範囲にいるboidsがプレイヤーの速度と方向を合わせる
		/// </summary>
		/// <param name="Player_Vector"></param>
		/// <param name="implayer"></param>
		/// <returns></returns>
	Pvector boid_zonbieAlignment(Pvector mousepos);

	/// <summary>
	/// 追跡　人間を追いかけ、追いつけずあきらめる
	/// </summary>
	/// <param name="player_vector"></param>
	/// <returns></returns>
	Pvector boid_zonbieAway(std::vector<Player*> human_vector);

	/// <summary>
	/// 探索　うろうろする
	/// </summary>
	/// <returns></returns>
	Pvector boid_zonbieSearch();

	/// <summary>
	/// 結合　周りにいるbboidsの中心へ向かおうとする
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <returns></returns>
	Pvector boid_Cohesion(std::vector<Player*> player_vector);

	/// <summary>
	/// 分散　ゾンビがマウスの場所から離れていく
	/// </summary>
	/// <returns></returns>
	Pvector zonbie_Scatter();
	/// <summary>
	/// 結合　プレイヤーの範囲にいるboidsがプレイヤーに向かう
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	/// <returns></returns>
	Pvector boid_inCohesion(std::vector<Player*> player_vector);
	//Functions involving SFML and visualisation linking

	/// <summary>
	/// 最高速度に制限し目的地へ向かう
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	Pvector boid_seek(const Pvector& v);
	/// <summary>
	/// 視野角を前方90度に
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	/// <returns></returns>
	Pvector boid_view(std::vector<Player*> player_vector);
	/// <summary>
	/// mgrクラスで呼び出す関数　updateを纏めた物
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	void boid_run(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector);

	/// <summary>
	/// mgrクラスで呼び出す関数　updateを纏めた物
	/// </summary>
	/// <param name="player_vector"></param>
	/// <param name="human_vector"></param>
	/// <param name="mousevec"></param>
	void zonbie_run(std::vector<Player*> player_vector, std::vector<Player*> human_vector, Pvector mousevec);
	/// <summary>
	/// 速度を元にboidsの位置を更新
	/// </summary>
	void boid_update();
	/// <summary>
	/// ３法則を纏め重みづけをする
	/// </summary>
	/// <param name="Player_Vector"></param>
	/// <param name="implayer"></param>
	void boid_flock(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector);

	/// <summary>
	/// ゾンビに各ルールを適用し重みづけ
	/// </summary>
	void zonbie_flock(std::vector<Player*> zonbie_vector, std::vector<Player*> human_vector, Pvector mousevec);
	/// <summary>
	/// 画面外に出たときに反対の画面から出るように
	/// </summary>
	void boid_borders();

	void zombie_reborn(float x, float y,float z);

	/// <summary>
	/// 角度を求める
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	float boid_angle(const Pvector& v);

	void boids_attack(std::vector<Player*>& player_vector, Player& zonbie, std::vector<UniqueEnemy_Bomb>& unique_enemy_vector);

	Pvector zonbie_damage();



	//グローバル変数の代わりに、ゲーム内の値と重みにアクセスするために使用され	float desSep;

	float desSep;//分離の視野
	float desAli;//整列の視野
	float desCoh;//結合の視野
	float SepW;//分離の重み
	float AliW;//整列の重み
	float CohW;//結合の重み

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
	
	//人間の速さ
	static float hyumanmaxspeed;//1.5
	static float hyumanrandspeed;//5

	//hyumanali
	static float alidist;//40


	//hyumnsep
	static float sepdist;//10
	static float sepzonbiedist;//30
	static float sepspeed;//2.0
	static float septime;//30


	static float zonbiehp;//２
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

	//集合速度
	static float cohspeed;//１．０

	//ゾンビとのダメージ距離
	static float zombirange;//15
	static float damage;//１．０


	//away
	static float zombiawayspeed;//1.5
	static float zombieawaytime;//１０

	static bool save;
	static bool load;

	void SetNum();
	void SaveNum();
	void LoadNum();
	void Gui();
};