#pragma once
#include"player.h"
#include<list>
#include<vector>
#include<iostream>
#include <stdlib.h>
#include "myutil.h"
#include"SmartPtr.h"
#include"ColTrees.h"
#include"build.h"
#include"myutil.h"
#include"UniqueEnemy.h"
#include"UniqueEnemy_Bomb.h"

const int boids_num = 200;//全体のboidsの初期数
const int zonbbie_num = 10;//ゾンビの初期数
const int unique_enemy_num = 0;//近接の初期数
const int unique_enemy_bomb_num = 10;//遠距離の初期数
using namespace IKD;

class PlayerMgr
{
public:

	std::vector<shared_ptr<Player>> player_vector;//範囲外のbodis
	std::vector<shared_ptr<Player>> in_player_vector;//範囲内のboids
	std::vector<shared_ptr<Player>> zonbie_vector;//ゾンビ
	std::vector<shared_ptr<UniqueEnemy>> unique_enemy_vector;//ゾンビ
	std::vector<shared_ptr<UniqueEnemy_Bomb>> unique_enemy_bomb_vector;//ゾンビ
	std::vector<shared_ptr<Player>> in_enemy_vector;//敵の範囲内のboids
	std::vector <Player*> instance_vector;//敵の範囲内のboids
	std::vector<shared_ptr<Build>> build_vector;//建物
	
	std::vector<shared_ptr<Player>> buf_vec; 
	std::vector<shared_ptr<Player>> buf_pvec;
	std::shared_ptr<Player> ImPlayer;
	std::shared_ptr<Player> ImEnemy;

	

	void Init();

	void Update();

	void Draw();

	void Finsh();

	void BoidsCreate(float x,float z);

	void PlayerCreate();

	void EnemyCreate();
	
	void BuildCreate(XMFLOAT3 pos);
	
	void ZonbieCreate();

	void UEnemyCreate();

	void UEnemyBombCreate();

	void PlayerUpdate();

	bool CheckImnput();

	void oneplayerUpdate();

	void Releace();

	static PlayerMgr* GetInstance()
	{
		static PlayerMgr instance;
		return &instance;
	}

	/// <summary>
	/// パッド移動　Lステックが傾けられていて、Ｒ１をおされたらtrue
	/// </summary>
	/// <returns></returns>
	bool Pat_Short_Move();
	

	enum class DIRECTION
	{
		NEUTRAL = 0,

		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum class FRICK_STS
	{
		NETURAL = 0,
		START,
		NZEROTIME,
		GOTIMING,
		END,
	};

	FRICK_STS frick_sts = FRICK_STS::NETURAL;


	enum class Together_state
	{
		NOT,//デフォルト状態
		READY,//ロングノーツキーが押された状態
		READY_ZERO,//ノーツが真ん中にないとき
		NOW,//離さなければならない状態
		COH,//中心に集まる時間
		END
	};

	Together_state together_state = Together_state::NOT;


	enum class Long_Notes_State
	{
		Not,
		Push,
		Push_Now,
		Push_Zero,
		Releace_Time,
		Success,
		Miss
	};

	Long_Notes_State long_notes_state = Long_Notes_State::Not;

	enum class Billding_state
	{
		NOT,//デフォルト状態
		READY,//ロングノーツキーが押された状態
		READY_ZERO,//ノーツが真ん中にないとき
		NOW,//離さなければならない状態
		MISS,//離すタイミングを過ぎた
		END
	};

	Billding_state billding_state = Billding_state::NOT;


	float accel = 0.0f;
	float maxaccel = 6.0f;

	///////////////////////////////
	//ノーツ用の変数
	//////////////////////////
	bool turn_flg = false;						//連打阻止用のフラグ
	bool judge_flg = false;			        	//1拍に1回行動にするために必要
	int turn_cnt = 0;//何番目のノーツかを判断　1~6短ノーツ　7～8　ロングノーツ
	bool step_flg = false;//ロングノーツの
	bool blink_flg = false;//ブリンク判定が全て通ったかの成否
	bool rhythm_checker = false;//リズムが取れた判定
	bool building_flg = false;//建築するフラグ
	bool buildlv_flg = false;//建築にリソースを注ぐフラグ
	bool ZeroSen_flg = false; //０～1000秒の間
	bool Minus_Sen_Zero_flg = false;//-1000から０の間
	float seconds = 0.0f;//曲の秒数
	int iseconds = 0;//曲の秒の10000倍
	int judge_seconds = 0;//ｂｐｍの10000倍
	float beat = 0.0f;//１ｂｐｍ当たりの秒数
	static bool miss_flg_flg;			//ミスを一度だけにするフラグ
	static bool miss_flg;//失敗したときのフラグ

	//////////////////////
	
	///////////////////
	//スティック
	/////////////////////
	static int RStickRigX;//LスティックのXの傾き　-100～100
	static int RStickRigY;//LスティックのYの傾き　-100～100
	static int StickXRig;//パッドの角度ｘ
	static int StickYRig;//パッドの角度ｙ
	float pad_rig = 0.0f;//Lスティックの角度
	/////////////////////

	
	static int player_vector_num;//プレイヤーの外側配列の要素数
	static int in_player_vector_num;//プレイヤーの内側配列の要素数
	static int in_enemy_vector_num;//エネミーーの内側配列の要素数
	static int zonbie_vector_num;//ゾンビーの配列の要素数
	static int unique_enemy_vector_num;//ゾンビーの配列の要素数
	static int unique_enemy_bomb_vector_num;//ゾンビーの配列の要素数
	
	////////////////////////
	//マウスの座標
	/////////////////////////
	float mousex;
	float bmousex;
	float mousey;
	float bmousey;
	Pvector r_mousepos;
	Pvector p_mousepos;
	Pvector now_mousepos;
	Pvector mousevelocity;
	int mousecnt=0;//マウスを押してからの時間を取る
	int	scattercnt = 0;

	//////////////////////////

	bool gatherflg = false;
	bool velocityflg = false;
	bool scatterflg = false;//分散の処理
	
	enum class Mouse_state
	{
		None,
		Push_One,
		Push,
		Release
	};
	Mouse_state mousestate = Mouse_state::None;

	/// <summary>
	/// パッドを傾けているかどうか
	/// </summary>
	bool player_pad_flg = false;


	bool Getpad_rig_flg()
	{
		return player_pad_flg;
	}

	XMFLOAT2 Getpad_rig()
	{
		return XMFLOAT2(StickXRig, StickYRig);
	}

	XMFLOAT3 Screenpos(XMFLOAT3 World_Pos);
private:

public:
	
};
