#include	"player.h"
#include	"drawaxis.h"
#include    "CCamera.h"
#include"Notes_Arrange.h"
#include <cstdlib>
#include"PlayerMgr.h"
#include"CHeight_Map.h"

#include"BoundingSphere.h"
#include<list>;
#include<math.h>
#include"CDirectInput.h"
#include"MouseCircle.h"
#include"ModelMgr.h"
#include"Scean.h"
#include"BulletMgr.h"
#include"UniqueEnemy_Bomb.h"
#include<random>

class Scean;

XAudio audio;						//音楽ならす


static float m_rig;//プレイヤーの現在の角度保存用
static float ay;
static float bay;

//float Player::accel = 0.0f;
#define debuglog(a) std::cout<<a<<std::endl;

float scaling = Ground::GetInstance()->scaling;


const int window_height = (CHeight_Map::GetInstance()->iPixSize - 60) * scaling;//マップの大きさ　縦
const int window_width = (CHeight_Map::GetInstance()->iPixSize - 60) * scaling;//マップの大きさ　横


#define w_height window_height 
#define w_width window_width
#define PI 3.141592635


bool Player::hsepflg = false;
 bool Player::haliflg = false;

 bool Player::slopeflg = false;
 bool Player::pocketflg = false;


 bool Player::zdashflg = false;
 bool Player::zscaflg = false;
 bool Player::zsepflg = false;
 bool Player::zcohflg = false;
 bool Player::zserflg = false;
 bool Player::zawaflg = false;

 bool Player::dmgflg = false;
 bool Player::changeflg = false;

 bool Player::bbombflg = false;
 bool Player::bserflg = false;
 
 
 bool Player::texspeedflg = false;


 //人間の速さ
  float Player:: hyumanmaxspeed;//1.5
  float Player:: hyumanrandspeed;//5

 //hyumanali
  float Player:: alidist;//40


 //hyumnsep
  float Player:: sepdist;//10
  float Player:: sepzonbiedist;//30
  float Player:: sepspeed;//2.0
  float Player:: septime;//30


  float Player:: zonbiehp;//２
  float Player:: zonbiemaxspeed;//8.5
  float Player:: zonbiedownspeed;//0.05f

 //zonbiedamage
  float Player:: bombdist;//100
 //zonbiesearch
  int Player::Searchcnt;//70
  float Player:: Seachspeed;//0.3f
  float Player:: Seachtime;//50

  float Player:: chasedist;//50
  float Player:: chasespeed;//1.5
  float Player:: chasetime;//30

  float Player:: Dashspeed;//3.5f
  float Player:: Dashtime;//40

 //zonbiesep
  float Player:: Sepdist;//10
  float Player:: Sepspeed;//1.0

 //集合速度
  float Player:: cohspeed;//１．０

  //zombieaway
  float Player::zombiawayspeed;//1.5
  float Player::zombieawaytime;//１０

 //ゾンビとのダメージ距離
  float Player:: zombirange;//15
  float Player:: damage;//１．０

   bool Player::save = false;
   bool Player::load = false;

//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}




bool Player::Init() {

	// 行列初期化
	DX11MtxIdentity(m_mtx);

	//XYZの軸を取り出し保管
	SetQutenion();

	float posx = rand() % 400 - 200;//初期値
	float posz = rand() % 400 - 200;//初期値
	SetPos(XMFLOAT3(posx, 0.0f, posz));//初期値
	
	angle.x = 0.0f;
	angle.z = 0.0f;
	angle.y = 0.0f;

	return true;
}


bool Player::CharengerInit()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	//XYZの軸を取り出し保管
	SetQutenion();

	float posx = rand() % 400;
	float posz = rand() % 400;
	posx -= 200;
	posz -= 200;
	SetPos(XMFLOAT3(0, 0.0f, 0));
	angle.x = -90.0f;
	angle.z = 0.0f;
	angle.y = -90.0f;
	SetAngle();
	champion = true;

	return true;
}



void Player::boid_Init(float x, float y)
{
	float xx = rand() % 100 - 50.0f;
	float yy = rand() % 100 - 50.0f;

	acceleration = Pvector(1, 1);
	velocity = Pvector(xx, yy);//加速度
	location = Pvector(x, y);//ポジション
	//float sp = rand() % 5;
	//sp *= 0.1f;
	maxSpeed = 1.0f; //+sp;
//	maxSpeed *= 0.5f;
	maxForce = 0.7f;

	boid_accel = 1.0f;
	follow = Follow::HYUMAN;
	SetScale(0.001f, 0.001f, 0.001f);
	champion = false;
	desSep = 15;
	desAli = 55;
	desCoh = 20;
	SepW = 1.0;
	AliW = 1.0;
	CohW = 0.2;

}

void Player::zonbie_Init(float x, float y, int nowzombiecnt)
{

	acceleration = Pvector(0, 0);

	location = Pvector(x / 10, y / 10);//ポジション
	maxSpeed = 3.5;
	maxForce = 2.5;
	hp = zonbiehp;
	follow = Follow::ZONBIE;
	predator = true;
	champion = false;
	desSep = 15;
	desAli = 40;
	desCoh = 50;
	SepW = 1.5;
	AliW = 1.0;
	CohW = 1.0;

	boidshp.Init();
	if (ZOMBIE >= nowzombiecnt)
	{
		bstatus = BSTATUS::LIVE;
		hp = zonbiehp;
	}
	else
	{
		hp = 0;
		bstatus = BSTATUS::DEAD;
	}
}



void Player::boid_player_Init(float x, float y)
{


	//acceleration = Pvector(0, 0);
	//velocity = Pvector(PlayerMgr::GetInstance()->StickXRig, PlayerMgr::GetInstance()->StickYRig);//加速度
	////velocity = Pvector(0, 0);//加速度
	//location = Pvector(x, y);//ポジション
	//maxSpeed = hyumanmaxspeed;
	//maxForce = 0.5;
	//follow = Follow::PLAYER;

	//champion = true;
	//desSep = 5;
	//desAli = 40;
	//desCoh = 50;
	//SepW = 1.0;
	//AliW = 1.0;
	//CohW = 0.2;

}

void Player::follow_Init()
{
	//SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::ONE)].modelname));
	SetScale(0.1f, 0.1f, 0.1f);

	maxSpeed = 3.5;
	maxForce = 0.5;
	hp = zonbiehp;
	follow = Follow::ZONBIE;
	predator = true;
	champion = false;
	desSep = 15;
	desAli = 40;
	desCoh = 50;
	SepW = 1.0;
	AliW = 1.0;
	CohW = 1.0;
	boidshp.Init();
}


void Player::zombie_reborn(float x, float y,float z)
{
	bstatus = Player::BSTATUS::LIVE;
	hp = zonbiehp;
	rebornpos.x= x;
	rebornpos.y =z;
	reborn_flg = true;
}

void Player::Draw(int animenum) {

	if (follow == Follow::ZONBIE)
	{
		boidshp.Update(XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43),hp);
		boidshp.Draw();
		
	}
}
void Player::HyumanDrawAxis() {
	drawaxis(m_mtx, 5.0f, XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43));
}


void Player::DrawWithAxis() {

	// モデル描画
	drawaxis(m_mtx, 200, m_pos);
//	Draw();

}

struct FLOAT3
{
	float x, y, z;
};



void Player::Update(bool input) {



	if (bstatus == BSTATUS::LIVE)
	{
		boid_borders();


		if (awaycnt > 0)
		{
			awaycnt -= 1;
		}
		if (awaycnt == 0) {
			if (boid_accel > 2.0f)
			{
				boid_accel -= 0.03f;
			}
		}
		if (boid_accel < 1.0f)
		{
			boid_accel = 1.0f;
		}
		if (boid_accel > 4.0f)boid_accel = 4.0f;

		//各行列を初期化
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

		scale._11 = 2.0f;
		scale._22 = 2.0f;
		scale._33 = 2.0f;

	
		Ground::GetInstance()->GetPlayerHeight(*this);
		//今回の角度を保存
		if (slopeflg)
		{
			boid_accel = Ground::GetInstance()->AccelBoid(*this);
		}
		velocity.mulScalar(boid_accel);
		location.addVector(velocity);


		angle.y = -GetAtan(velocity.x, velocity.y);
		//角度調整
		angle.y -= 90.0f;
	
		SetAngle();
	
	/*	angle.y -= b_angle;
		b_angle = ang;*/

		DX11MtxMultiply(world, scale, rot);

		m_pos.x = location.x;
		m_pos.z = location.y;

		trans._41 = m_pos.x;
		trans._42 = m_pos.y + 4.0f;
		trans._43 = m_pos.z;

		world._41 = trans._41;
		world._42 = trans._42;
		world._43 = trans._43;

		m_mtx = world;

	}
	else
	{
		m_mtx._41 = 10000;
	}
}



void Player::ZonbieUpdate(int animenum, int i)
{
	if (bstatus == BSTATUS::LIVE)
	{


		boid_borders();
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);


		//Z軸を取り出す
		axisZ.x = m_mtx._31;
		axisZ.y = m_mtx._32;
		axisZ.z = m_mtx._33;
		axisZ.w = 0.0f;

		angle.y = 0.0f;

		angle.y = -GetKakudo(angley.x, angley.y);
		angle.y -= 90.0f;
		if (angle.y > 360)
		{
			angle.y -= 360.0f;
		}


		if (reborn_flg)
		{
			location.x = rebornpos.x;
			location.y = rebornpos.y;
			m_pos.x = location.x;
			m_pos.z = location.y;
			Ground::GetInstance()->GetPlayerHeight(*this);
			reborn_flg = false;
		}
		else
		{
			Ground::GetInstance()->GetPlayerHeight(*this);
			if (awaycnt > 0)
			{
				awaycnt -= 1;
			}
			if (awaycnt == 0) {

				boid_accel -= 0.05f;

			}
			if (boid_accel < 0)
			{
				boid_accel = 0;
			}
			if (boid_accel < 0.5f)
			{
				zombie_scatterflg = false;
			}
			if (boid_accel > 2.5f)
			{
				boid_accel = 2.5f;
			}

			acceleration.normalize();

			acceleration.mulScalar(boid_accel);

			//  更新速度
			velocity.addVector(acceleration);

			location.addVector(velocity);
		

			m_pos.x = location.x;
			m_pos.z = location.y;

		}

//		Ground::GetInstance()->GetPlayerHeight(*this);

		trans._41 = m_pos.x;
		trans._42 = m_pos.y + 4.0f;
		trans._43 = m_pos.z;


	

		scale._11 = 5.2f;
		scale._22 = 5.2f;
		scale._33 = 5.2f;



		float ang = angle.y;
		SetAngle();
		angle.y -= b_angle;
		b_angle = ang;

		DX11MtxMultiply(world, scale, rot);
	


		world._41 = trans._41;
		world._42 = trans._42;
		world._43 = trans._43;


		m_mtx = world;
		
		

	}
	else
	{
	m_mtx._41 = 10000;
	}

}
//使ってない
void Player::FollowUpdate()
{

	Ground::GetInstance()->GetPlayerHeight(*this);
	//Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;
	//angle.y = -PlayerMgr::GetInstance()->pad_rig;

	PlayerMgr::GetInstance()->accel *= 1.0f;//anglecos;
	if (PlayerMgr::GetInstance()->accel > 6.5f) PlayerMgr::GetInstance()->accel = 6.5f;

	boid_accel = PlayerMgr::GetInstance()->accel;


	velocity.x = axisZ.x * boid_accel;
	velocity.y = axisZ.z * boid_accel;

	boid_borders();

	m_pos.x = location.x;
	m_pos.z = location.y;

	//SetAngle();
	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y + 4.0f;
	m_mtx._43 = m_pos.z;
}



void Player::Finalize() {
//	m_model->Uninit();
}



void Player::applyForce(const Pvector& force)
{
	acceleration.addVector(force);
}

void Player::Move_And_Delete(float arraynum, std::vector<Player*> player_vector1, std::vector<Player*> player_vector2)
{
	//1の配列へ２の配列の要素番号を移動
	player_vector1.push_back(std::move(player_vector2[arraynum]));

	//いた場所の配列を消す
	player_vector2.erase(player_vector2.begin() + arraynum);

}

void Player::Delete(float arraynum, std::vector<Player*> Player_Vector1)
{
	Player_Vector1.erase(Player_Vector1.begin() + arraynum);
}


void Player::boids_attack(std::vector<Player*>& player_vector, Player& zonbie, std::vector<UniqueEnemy_Bomb>& unique_enemy_vector)
{
	if (changeflg)
	{
		for (auto& i : player_vector)
		{
			float dd = i->location.distance(zonbie.location);					

			//hp減産処理
			if (dd < zombirange)
			{
				i->hp = 0;

			}
		}

		for (auto& u : unique_enemy_vector)
		{
			float dd = u.location.distance(zonbie.location);

			if (dd < 25)
			{
				u.hp -= 1;
			}
		}
	}
}

Pvector desired;//計算用の変数
Pvector des;//計算用の変数

// maxSpeed を制限し、必要な操舵力を見つけ、
//ベクトルを正規化します
Pvector Player::boid_seek(const Pvector& v)
{
	desired = { 0,0 };
	desired = desired.subTwoVector(v, location);  //位置からターゲットを指すベクトル
	// 必要な正規化と最大速度へのスケーリング
	desired.normalize();
	desired.mulScalar(hyumanmaxspeed);

	//ステアリング = 望ましいマイナス速度
	acceleration = acceleration.subTwoVector(desired, velocity);
	acceleration.normalize();
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

Pvector Player::boid_view(std::vector<Player*> player_vector)
{
	// How far can it see?
	float sightDistance = 100;
	float periphery = PI / 2;

	for (int i = 0; i < player_vector.size(); i++) {
		// A vector that points to another boid and that angle
		desired ={0,0};
		desired = desired.subTwoVector(player_vector.at(i)->location, location);

		// How far is it
		float d = location.distance(player_vector.at(i)->location);
		
		// What is the angle between the other boid and this one's current direction
		float desireda = velocity.angleBetween(desired);

		// If it's within the periphery and close enough to see it
		if (desireda < periphery && d > 0 && d < sightDistance) {
			//視野角にいるboidだけで３法則
			//boid_flock(player_vector,zonbie_vector);
		}
	}
	return Pvector();
}



//std::vector<Player>> grid[100][100] = { {} };
void Player::boid_run(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector)
{
	boid_flock(player_vector, zonbie_vector);
	boid_update();

}

void Player::zonbie_run(std::vector<Player*> player_vector, std::vector<Player*> human_vector, Pvector mousevec)
{
	zonbie_flock(player_vector,human_vector, mousevec);
	boid_update();
}



Pvector sep = { 0,0 };
Pvector ali = { 0,0 };
Pvector coh = { 0,0 };
Pvector awa = { 0,0 };
Pvector dmg = { 0,0 };
Pvector avo = { 0,0 };
Pvector down = { 0,0 };


//ボイドの群れに三法則を適用する
void Player::boid_flock(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector)
{
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	avo = { 0,0 };
	down = { 0,0 };
	

	if (follow == Follow::HYUMAN)
	{
		alifalse_cnt -= 1;
	
		if (alifalse_cnt < -10000)alifalse_cnt = -40;
		if (hsepflg)
		{
			
			{
				sep = boid_Separation(player_vector, zonbie_vector);
			}
			
			

		}

		//avo = boid_Avoid(zonbie_vector);

		if (haliflg)
		{
			if (alifalse_cnt < 0)
			{
				ali = boid_Alignment(player_vector);
		
			
			}
		}
		if (pocketflg)
		{
			down = boid_Down();
		}
		//if (hcohflg)
		//{
		////	coh = boid_Cohesion(player_vector);
		//}
		//
		
	}

	//これらの力を任意に重み付けする
	//cen.mulScalar(CohW);
	sep.mulScalar(1.5f);
	ali.mulScalar(1.0f); // さまざまな特性の重みを変更する必要がある場合があります
	avo.mulScalar(1.0f); // さまざまな特性の重みを変更する必要がある場合があります
	down.mulScalar(1.0f);
	
	//  力ベクトルを加速度に加える

	applyForce(sep);
	applyForce(avo);
	applyForce(ali);
	applyForce(down);
	//applyForce(coh);
	//applyForce(cen);

}

void Player::zonbie_flock(std::vector<Player*> player_vector, std::vector<Player*> human_vector, Pvector mousevec)
{
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	awa = { 0,0 };
	dmg = { 0,0 };

	

	if (PlayerMgr::GetInstance()->scatterflg)
	{
		if (zscaflg)
		{
			awaycnt = 0;
			coh = Zombie_Scatter();
		}
	}

	//分散している時以外は行う
	if (!zombie_scatterflg)
	{
		if ((boid_accel < 0.5f) || (PlayerMgr::GetInstance()->gatherflg))
		{
			if (zsepflg)
			{
				sep = boid_inSeparation(player_vector);
			}
		}

		if (PlayerMgr::GetInstance()->gatherflg)
		{
			if (zcohflg)
			{
				awaycnt = 0;
				coh = boid_inCohesion(player_vector);
			}
		}
		if ((!PlayerMgr::GetInstance()->gatherflg) && (!PlayerMgr::GetInstance()->scatterflg))
		{
			if (zserflg)
			{
				if (boid_accel < 0.2f)
				{
					awa = boid_zonbieSearch();
				}
			}
		}
		if (!PlayerMgr::GetInstance()->gatherflg) {
			if (zawaflg)
			{
				if (boid_accel < 0.4f)
				{
					awa = boid_zonbieAway(human_vector);
				}
			}
		}
		if (zdashflg)
		{
			ali = boid_zonbieAlignment(mousevec);
		}

		dmg = zonbie_damage();
	}
	
	//これらの力を任意に重み付けする
	//cen.mulScalar(CohW);
	sep.mulScalar(SepW);

	coh.mulScalar(CohW);
	awa.mulScalar(1.0f);
	dmg.mulScalar(3.0f);
	ali.mulScalar(AliW); // さまざまな特性の重みを変更する必要がある場合があります
	//
	//  力ベクトルを加速度に加える
	if (zexplosionflg)
	{
		applyForce(dmg);
	}
	zexplosionflg = false;
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
	applyForce(awa);
	
}


// 速度、位置を変更し、加速度を次の値でリセットします
// 三法則で与えられる。
void Player::boid_update()
{
	if (follow == Follow::HYUMAN)
	{
		//スローダウンを急激にしないために
	//	acceleration.mulScalar(0.35f);
		//  更新速度
		velocity.addVector(acceleration);
		velocity.normalize();
		//  制限速度
		velocity.mulScalar(hyumanmaxspeed);
		//velocity.limit(hyumanmaxspeed);
	

		// 各サイクルで加速度を 0 にリセットする
		acceleration.mulScalar(0);
	}
	else if (follow != Follow::HYUMAN)
	{
		if (!champion)
		{


			if (PlayerMgr::GetInstance()->gatherflg)
			{
				this->boid_accel = cohspeed;
			}
			//else if (PlayerMgr::GetInstance()->scatterflg)
			//{
			//	//acceleration.mulScalar(0);

			////	this->boid_accel = PlayerMgr::GetInstance()->accel;
			//}

			//スローダウンを急激にしないために
			//acceleration.mulScalar(0.35f);

			//velocity.mulScalar(boid_accel);



			velocity.mulScalar(0);
			if (boid_accel <= 0.2f)
			{
				awayflg = false;
			}
		}
	}	
}



void Player::boid_borders()
{

	if (location.x < -window_width * 0.5f)	location.x += window_width;
	if (location.y < -window_width * 0.5f)	location.y += window_height;
	if (location.x > window_height * 0.5f)	location.x -= window_width;
	if (location.y > window_height * 0.5f)	location.y -= window_height;
}

Pvector steer(0, 0);

// 分離
// ボイド同士が近づきすぎないようにする
Pvector Player::boid_Separation(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector)
{
	// ボイド間分離視野距離
	//float desiredseparation = 10;//視野　プレイヤーからの距離
	steer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します

	//for (int i = 0; i < sizeof(player_vector)/sizeof(player_vector[0]); i++)//0回
	if (boid_accel < 2.0f)
	{
		for (auto& it : player_vector)
		{

			// 現在のboidから見ているboidまでの距離を計算する
			if (it->follow == Follow::HYUMAN)
			{
				float d = location.distance(it->location);
				// これが仲間のボイドであり、近すぎる場合は、離れてください
				if ((d > 0) && (d < sepdist)) {
					desired = { 0,0 };
					desired = desired.subTwoVector(location, it->location);
					desired.normalize();
					desired.divScalar(d);      // Weight by distance
					steer.addVector(desired);
					count++;
				}
			}
		}
	}
	for (auto& it : zonbie_vector)
	{

		float d = location.distance(it->location);
		//// 現在のボイドが捕食者であり、私たちが見ているボイドも捕食者である場合
		//// 捕食者は近づいて、その後わずかに分離
		//if ((d > 0) && (d < desiredseparation) && predator == true
		//	&& it->predator == true) {
		//	desired = { 0,0 };
		//	desired = desired.subTwoVector(location, it->location);
		//	desired.normalize();
		//	desired.divScalar(d);
		//	steer.addVector(desired);
		//	count++;
		//}
		// 現在のボイドが捕食者ではなく、私たちが見ているボイドが
		// 捕食者、次に大きな分離 Pvector を作成します
		if ((d > 0) && (d < sepzonbiedist) && it->predator == true) {
			desired = { 0,0 };
			desired = desired.subTwoVector(location, it->location);
			desired.mulScalar(900);
			steer.addVector(desired);
			count++;
			alifalse_cnt = 25;
		//	alifalse_flg = true;
			boid_accel = sepspeed;
		//	awaycnt = septime;
		}
	}
	

	// 位置の平均差を加速度に加算
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude2x() > 0) {
		// Steering = Desired - Velocity
		steer.normalize();
		//steer.mulScalar(hyumanmaxspeed);
		steer.subVector(velocity);
		//steer.limit(maxForce);
	
	}
	return steer;
}

Pvector Player::boid_Avoid(std::vector<Player*> player_vector)
{
	Pvector stt = { 0,0 };
	for (auto& it : player_vector)
	{
		XMFLOAT3 diff = XMFLOAT3(it->GetPos().x-this->GetPos().x , 0.0f, it->GetPos().z-this->GetPos().z);//障害物との距離

		//差を出す
		float distance;
		DX11Vec3Dot(distance,diff, diff);
	
		sqrt(distance);
		float aboidrange = 450.0f;
		float escaperange = 50.0f;

		//避ける範囲内化
		if (distance > aboidrange)  // 障害物を避ける範囲内にいるか？
		{
			return desired = { 0, 0 };
		}
		if (escaperange > distance)
		{
			return desired = { 0, 0 };
		}

		XMFLOAT3 target2ObstacleDirection;
		DX11Vec3Normalize(target2ObstacleDirection, diff);

		XMFLOAT3 forward= XMFLOAT3(this->angley.x,1.0f,this->angley.y);
		
		DX11Vec3Normalize(forward, forward);

		float directionDot;
		DX11Vec3Dot(directionDot, target2ObstacleDirection, forward);
		
		//
		if (directionDot < 0) // 前方向に障害物がないか
		{
			return desired = { 0, 0 };
		}

		XMFLOAT3 forward2DiffCross;
		XMFLOAT3 forward2DiffCrossv;
	//	DX11Vec3Normalize(diff, diff);
		DX11Vec3Cross(forward2DiffCross, diff,forward);
		DX11Vec3Cross(forward2DiffCrossv, forward,diff);

		float forward2ObstacleDistance;
		DX11Vec3Length(forward2DiffCross, forward2ObstacleDistance);

		if (forward2ObstacleDistance> escaperange) // 障害物から逃げる範囲と速度ベクトルの直線が重なっていないか
		{
			return desired = { 0, 0 };
		}

		const float crossElementSum = forward2DiffCross.x + forward2DiffCross.y + forward2DiffCross.z;
		//const XMFLOAT3 axis;

		if (crossElementSum != 0)
		{
			DX11Vec3Normalize(forward2DiffCross, forward2DiffCross);
			DX11Vec3Normalize(forward2DiffCrossv, forward2DiffCrossv);
		}
		else
		{
			return desired = { 0, 0 };
		}

		desired = { forward2DiffCross.x,forward2DiffCross.z };

		XMFLOAT4X4 vec;
		float aa = GetKakudo(forward2DiffCross.x,forward2DiffCross.z);
		DX11MtxRotationAxis(forward2DiffCross,aa,vec);
		
	//	stt = stt.subTwoVector(velocity, desired); //sum = desired(average)

	}
	//	const float3x3 avoidTorque = CalcAvoidObstacleTorque(boidData.position, velocity);
//	const float3 avoidVelocity = mul(velocity, avoidTorque);
	return desired;
	
}

Pvector Player::boid_inSeparation(std::vector<Player*> player_vector)
{
	// ボイド間分離視野距離
//	this->desSep;//視野　プレイヤーからの距離

	if (this->follow == Follow::ZONBIE)
	{
	///	acceleration = { 0,0 };
		velocity = { 0,0 };


		if (PlayerMgr::GetInstance()->gatherflg)
		{
			Sepdist -= 0.1f;
			//Sepdist = max(Sepdist, 10.0f);

			if (Sepdist < 10.0f)
			{
				Sepdist = 10.0f;
			}
		}
		else if (!PlayerMgr::GetInstance()->gatherflg)
		{
			Sepdist += 0.2f;
		///	Sepdist = min(Sepdist, 25.0f);
			if (Sepdist > 25.0f)
			{
				Sepdist = 25.0f;
			}
		}
	}

	steer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します
	for (auto& it : player_vector)
	{

		// 現在のboidから見ているboidまでの距離を計算する
		if (it->follow != Follow::HYUMAN)
		{
			float d = location.distance(it->location);
			if ((d > 0) && (d < Sepdist)) {

				//desiredseparation /= count;
					// これが仲間のボイドであり、近すぎる場合は、離れてください
				if ((d > 0) && (d < Sepdist)) {
					desired = { 0,0 };
					desired = desired.subTwoVector(location, it->location);
					desired.normalize();
					desired.divScalar(d);      // Weight by distance
					steer.addVector(desired);
					count++;

				}
			}
		}


	}


	// 位置の平均差を加速度に加算
	if (count > 0)
	{
		steer.divScalar((float)count);
	}

	if (steer.magnitude2x() > 0) {
		steer.normalize();
		

		if (boid_accel < 0.5f)
		{
			angley.x = steer.x;
			angley.y = steer.y;
		}
		boid_accel = 1.0f;
	}
	return steer;
}

// 整列
//視野内のボイドの平均速度を計算し、
// 一致するように現在のボイドの速度を操作します
Pvector Player::boid_Alignment(std::vector<Player*> player_vector)
{

	desired = { 0,0 };
	int count = 0;
	for (auto& it : player_vector)
	{

		if (it->follow == Follow::HYUMAN)
		{
			float d = location.distance(it->location);
			if ((d > 0) && (d < alidist)) { // 0 < d < 50
				if (it->boid_accel < 2.0f)
				{
					desired.addVector(it->velocity);
					count++;
				}
			}
		}

	}
	// 整列するのに十分近いボイドがある場合...
	if (count > 0) {
		desired.divScalar((float)count);// 合計を近いボイドの数で割ります (速度の平均)
		desired.normalize();            // 合計を単位ベクトルに変換し、
		desired.mulScalar(hyumanmaxspeed);    //maxSpeed を掛ける
		// Steer = Desired - Velocity
		steer = { 0,0 };
		steer = steer.subTwoVector(desired, velocity); //sum = desired(average)
		steer.limit(maxForce);
		return steer;
	}
	else {
		desired = { 0,0 };
		return desired;
	}

}

Pvector Player::boid_Down()
{
	angle.y = 0.0f;//角度リセット

//	velocity.addVector(acceleration);
	velocity.normalize();

	//ベクトル保存
	angley.x = velocity.x;
	angley.y = velocity.y;

	//boids計算から出た速度を元に向きを変更
	angle.y = GetAtan(velocity.x, velocity.y);


	/*	if (angle.y > 360)angle.y -= 360.0f;
		else if (angle.y < 0)angle.y += 360.f;
		velocity.x = -cosf(((angle.y) * 3.14159265358979323846 / 180.0f));
		velocity.y = -sinf(((angle.y) * 3.14159265358979323846 / 180.0f));*/



		//左回転用の角度
	left_angle = angle.y + 45.f;
	if (left_angle > 360)left_angle -= 360.0f;
	else if (left_angle < 0)left_angle += 360.f;
	//右回転用の角度
	right_angle = angle.y - 45.f;
	if (right_angle > 360)right_angle -= 360.0f;
	else if (right_angle < 0)right_angle += 360.f;
	//180度回転用の角度
	opposite_angle = angle.y + 180.f;
	if (opposite_angle > 360)opposite_angle -= 360.0f;
	else if (opposite_angle < 0)opposite_angle += 360.f;

	//それぞれの角度のベクトルを算出
	left_vec.x = cosf(((left_angle) * 3.14159265358979323846 / 180.0f));
	left_vec.y = sinf(((left_angle) * 3.14159265358979323846 / 180.0f));
	right_vec.x = cosf(((right_angle) * 3.14159265358979323846 / 180.0f));
	right_vec.y = sinf(((right_angle) * 3.14159265358979323846 / 180.0f));
	opposite_vec.x = cosf(((opposite_angle) * 3.14159265358979323846 / 180.0f));
	opposite_vec.y = sinf(((opposite_angle) * 3.14159265358979323846 / 180.0f));

	return Ground::GetInstance()->DownBoid(*this);

}


Pvector Player::boid_zonbieAlignment(Pvector mousepos)
{

	if (insideflg)
	{
		if (PlayerMgr::GetInstance()->velocityflg)
		{
			vel = { 0,0 };
			desired = { 0,0 };
			velocity = { 0,0 };

			ali_vel = mousepos;
			acceleration = { ali_vel.x,ali_vel.y };
			acceleration.mulScalar(-1);

			angley.x = acceleration.x;
			angley.y = acceleration.y;

			ali_vel.normalize();
			ali_vel.mulScalar(-1.0f);
			///velocity = mousepos;
			this->boid_accel = Dashspeed;
			insideflg = false;
			awaycnt = Dashtime;
		}
	}

	return ali_vel;
}

Pvector Player::boid_zonbieAway(std::vector<Player*> player_vector)
{// ボイド間分離視野距離
	//float desiredseparation = chasedist;//視野　プレイヤーからの距離
	steer = { 0.0f,0.0f };
	int count = 0;
	
	float before_distanse = 50.0f;//一番近い距離保存用
	
	Pvector nearplayer;//一番近い存在を保存する変数
	
	if (awayflg == false) {

		// 現在のボイドが捕食者であり、私たちが見ているボイドも捕食者である場合
		// 捕食者は近づいて、その後わずかに分離
		for (auto& it : player_vector)
		{
			float d = location.distance(it->location);
			if (d < before_distanse) {
				before_distanse = d;
				nearplayer = it->location;
			}
		}
		if ((before_distanse > 0) && (before_distanse < chasedist))
		{
	

			desired = { 0,0 };
			desired = desired.subTwoVector(location, nearplayer);
			desired.normalize();
			desired.mulScalar(-1);
			desired.divScalar(before_distanse);

			acceleration = desired;
			angley.x = acceleration.x;
			angley.y = acceleration.y;


			this->boid_accel = zombiawayspeed;
			awayflg = true;
			awaycnt = zombieawaytime;
		}
	}
	return desired;
}

Pvector Player::boid_zonbieSearch()
{
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution<int32_t> rand4(0,10000);
	std::uniform_int_distribution<int32_t> rand5(-150,150);
	
	int cnt = rand4(seed_gen)% Searchcnt;
	if (cnt == 0)
	{
		vel = { 0,0 };
		desired = { 0,0 };

		ali_vel ={0,0};

		float x = rand5(seed_gen);
		float y = rand5(seed_gen);
		desired = { 0,0 };
		desired = { x,y };
		desired.normalize();
		desired.mulScalar(-1);
		desired.divScalar(15);

		acceleration = desired;
		angley.x = acceleration.x;
		angley.y = acceleration.y;
		this->boid_accel = Seachspeed;
		awaycnt = Seachtime;
	}
	return desired;
}

// 結合
// 近くのボイドの平均位置を見つけ、
// その方向に移動する操舵力。
Pvector Player::boid_Cohesion(std::vector<Player*> player_vector)
{
	float neighbordist = desCoh;
	desired = { 0,0 };
	int count = 0;
	for (auto& it : player_vector)
	{
		float d = it->location.distance(this->location);
		if ((d > 0) && (d < neighbordist)) {
			desired.addVector(it->location);
			count++;
		}
	}
	if (count > 0) {
		this->location;
		desired.divScalar(count);
		return boid_seek(desired);
	}
	else {
		desired = { 0,0 };
		return desired;
	}
}

/// <summary>
/// 分散していく
/// </summary>
/// <returns></returns>
Pvector Player::Zombie_Scatter()
{
	if (zombie_scatterflg)
	{
		if (PlayerMgr::GetInstance()->scatterflg)
		{
			ali_vel = { 0,0 };
			velocity = { 0,0 };
			acceleration = { 0,0 };

			vel = { 0,0 };
			desired = { 0,0 };
			boid_accel = 2.0f;
			XMFLOAT3 pos = {};
			Pvector now_mousepos = { 0,0 };
			now_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
			now_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
			now_mousepos.x -= Application::CLIENT_WIDTH / 2 * 1.0f;
			now_mousepos.y = Application::CLIENT_HEIGHT / 2 * 1.0f - now_mousepos.y;

			pos = Screenpos(this->GetPos());
			pos.x -= Application::CLIENT_WIDTH / 2;
			pos.y = Application::CLIENT_HEIGHT / 2 - pos.y;

			vel.x = pos.x;
			vel.y = pos.y;

			desired = desired.subTwoVector(now_mousepos, vel); //sum = desired(average)
			desired.normalize();
			desired.mulScalar(-1);

			angley.x = desired.x;
			angley.y = desired.y;
			velocity = desired;

			awaycnt = 10;
		}
	}
	return desired;
}

Pvector Player::zonbie_damage()
{
	for (auto& b : BulletMgr::GetInstance()->g_bullets) {
		if (b->explosion == true)
		{
			bombdist = 100;//視野　プレイヤーからの距離
		
		
			
			ali_vel.x = b->GetMtx()._41;
			ali_vel.y = b->GetMtx()._43;

			float d = location.distance(ali_vel);
			if (d < bombdist)
			{
				//aa
				//ali_vel = { 0,0 };
				//velocity = { 0,0 };
				acceleration = { 0,0 };

				vel = { 0,0 };
				desired = { 0,0 };

				this->hp -= 1;
				desired = desired.subTwoVector(location,ali_vel); //sum = desired(average)
				desired.normalize();
			

				angley.x = desired.x;
				angley.y = desired.y;
				velocity = desired;

				boid_accel = 3.5f;
				zexplosionflg = true;

			}

		}
	}
	ali_vel = { 0,0 };
	return desired;
}



//集合
Pvector Player::boid_inCohesion(std::vector<Player*> player_vector)
{

	desired = { 0,0 };
	ali_vel = { 0,0 };
	acceleration = { 0,0 };



	if (this->follow == Follow::ZONBIE)
	{

		this->boid_accel = 0;
		vel = { 0,0 };
		//	ali_vel = { 0,0 };
		desired = { 0,0 };
		acceleration = { 0,0 };
		XMFLOAT3 pos = {};
		Pvector now_mousepos = { 0,0 };
		now_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
		now_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
		now_mousepos.x -= Application::CLIENT_WIDTH / 2 * 1.0f;
		now_mousepos.y = Application::CLIENT_HEIGHT / 2 * 1.0f - now_mousepos.y;

		pos = Screenpos(this->GetPos());
		pos.x -= Application::CLIENT_WIDTH / 2;
		pos.y = Application::CLIENT_HEIGHT / 2 - pos.y;

		vel.x = pos.x;
		vel.y = pos.y;



		desired = desired.subTwoVector(now_mousepos, vel); //sum = desired(average)
		desired.normalize();

		if (anglecnt == 0) {
			angley.x = desired.x;
			angley.y = desired.y;
		}
		anglecnt++;
		if (anglecnt > 3)
		{
			anglecnt = 0;
		}

		//this->boid_accel = 1.2f;

	}

	return desired;

}


XMFLOAT3 Player::Screenpos(XMFLOAT3 World_Pos) {

	XMFLOAT4X4 g_view = CCamera::GetInstance()->GetViewMatrix();//ビュー変換取得
	XMFLOAT4X4 g_projection = CCamera::GetInstance()->GetProjectionMatrix();//プロジェクション取得

	//計算の為に変換
	XMMATRIX view = XMLoadFloat4x4(&g_view);
	XMMATRIX proj = XMLoadFloat4x4(&g_projection);

	//tビューポート設定
	float w = (float)Application::CLIENT_WIDTH / 2.0f;
	float h = (float)Application::CLIENT_HEIGHT / 2.0f;
	XMMATRIX viewport = {
	w, 0, 0, 0,
	0, -h, 0, 0,
	0, 0, 1, 0,
	w, h, 0, 1
	};

	//変更したいキャラの座標を取得し変換
	XMFLOAT3 temp = World_Pos;
	XMVECTOR tmp = XMLoadFloat3(&temp);


	// ビュー行列とプロジェクション行列を掛ける
	tmp = XMVector3Transform(tmp, view);
	tmp = XMVector3Transform(tmp, proj);

	//float値に
	DirectX::XMStoreFloat3(&temp, tmp);

	// zで割って-1~1の範囲に収める
	// スクリーン変換
	const XMVECTOR view_vec = XMVectorSet(temp.x / temp.z, temp.y / temp.z, 1.0f, 1.0f);
	tmp = XMVector3Transform(view_vec, viewport);

	//float値にして戻り値
	DirectX::XMStoreFloat3(&temp, tmp);
	return temp;
}


void Player::SetAngle()
{
	XMFLOAT4 qtx = {};//クォータニオン
	XMFLOAT4 qty = {};//クォータニオン
	XMFLOAT4 qtz = {};//クォータニオン
	

	//DX11GetQtfromMatrix(m_mtx, qt);

	//指定軸回転のクォータニオンを生成
	DX11QtRotationAxis(qtx, axisX, angle.x);
	DX11QtRotationAxis(qty, axisY, angle.y);
	DX11QtRotationAxis(qtz, axisZ, angle.z);


	//クォータニオンを合成
	XMFLOAT4 tempqt1;
	DX11QtMul(tempqt1, qtx, qty);

	XMFLOAT4 tempqt2;
	DX11QtMul(tempqt2, qtz, tempqt1);

	//クォータニオンをノーマライズ
	DX11QtNormalize(tempqt2, tempqt2);

	SetRotation(tempqt2);

	//クォータニオンから行列を作成
	DX11MtxFromQt(rot, tempqt2);
}

XMFLOAT3 Player::GetAngle()
{
	return angle;
}



void Player::CheckBox()
{
	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
		ImGui::Begin("Rule");

		ImGui::SetNextWindowSize(ImVec2(300, 400));

		if (ImGui::CollapsingHeader(u8"Hyuman"))
		{
			ImGui::Checkbox("Hyuman_Separation", &hsepflg);
			ImGui::Checkbox("Hyuman_Ali", &haliflg);
			ImGui::Checkbox("Hyuman_TexSpeed", &texspeedflg);
			ImGui::Checkbox("Hyuman_Slope", &slopeflg);
			ImGui::Checkbox("Hyuman_Pocket", &pocketflg);

		}
		if (ImGui::CollapsingHeader(u8"Zombie"))
		{
			ImGui::Checkbox("Zombie_Dash", &zdashflg);
			ImGui::Checkbox("Zombie_Cohesion", &zcohflg);
			ImGui::Checkbox("Zombie_Away", &zawaflg);
			ImGui::Checkbox("Zombie_Sca", &zscaflg);
			ImGui::Checkbox("Zombie_Serch", &zserflg);
			ImGui::Checkbox("Zombie_Sep", &zsepflg);
		}
	
		if (ImGui::CollapsingHeader(u8"E_Bomb"))
		{

			ImGui::Checkbox("BombE_bomb", &bbombflg);
			ImGui::Checkbox("BombE_Ser", &bserflg);
		}
		if (ImGui::CollapsingHeader(u8"Base_Rule"))
		{
			ImGui::Checkbox("Dmg", &dmgflg);
			ImGui::Checkbox("change", &changeflg);
		}

		if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_M))
		{

			hsepflg = true;
			haliflg = true;
			texspeedflg = true;
			slopeflg = true;
			pocketflg = true;

			zdashflg = true;
			zscaflg = true;
			zsepflg = true;
			zcohflg = true;
			zserflg = true;
			zawaflg = true;

			dmgflg = true;
			
			changeflg = true;

			bbombflg = true;
			bserflg = true;
		}
		



		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}
}

void Player::SaveNum()
{


	Save::GetInstance()->save2.data1 = hyumanmaxspeed;
	Save::GetInstance()->save2.data2 = hyumanrandspeed;
	Save::GetInstance()->save2.data3 = alidist;
	Save::GetInstance()->save2.data4 = sepdist;
	Save::GetInstance()->save2.data5 = sepzonbiedist;
	Save::GetInstance()->save2.data6 = sepspeed;
	Save::GetInstance()->save2.data7 = septime;
	Save::GetInstance()->save2.data8 = hp;
	Save::GetInstance()->save2.data9 = zonbiemaxspeed;
	Save::GetInstance()->save2.data10 = zonbiedownspeed;
	Save::GetInstance()->save2.data11= bombdist;
	Save::GetInstance()->save2.data12 = Seachspeed;
	Save::GetInstance()->save2.data13 = Seachtime;
	Save::GetInstance()->save2.data14 = chasedist;
	Save::GetInstance()->save2.data15 = chasespeed;
	Save::GetInstance()->save2.data16 = chasetime;
	Save::GetInstance()->save2.data17 = Dashspeed;
	Save::GetInstance()->save2.data18 = Dashtime;
	Save::GetInstance()->save2.data19 = Sepdist;
	Save::GetInstance()->save2.data20 = Sepspeed;
	Save::GetInstance()->save2.data21 = cohspeed;
	Save::GetInstance()->save2.data22 = zombirange;
	Save::GetInstance()->save2.data23 = damage;
	Save::GetInstance()->save2.data24 = zombieawaytime;
	Save::GetInstance()->save2.data25 = zombiawayspeed;
	Save::GetInstance()->save2.data50 = Searchcnt;


	Save::GetInstance()->Savevin2("assets/boids.dat", Save::GetInstance()->save2);

}



void Player::LoadNum()
{
	Save::GetInstance()->save2 = Save::GetInstance()->Loadvin2("assets/boids.dat");

	hyumanmaxspeed = Save::GetInstance()->save2.data1;
	hyumanrandspeed = Save::GetInstance()->save2.data2;
	alidist = Save::GetInstance()->save2.data3;
	sepdist = Save::GetInstance()->save2.data4;
	sepzonbiedist = Save::GetInstance()->save2.data5;
	sepspeed = Save::GetInstance()->save2.data6;
	septime = Save::GetInstance()->save2.data7;
	zonbiehp = Save::GetInstance()->save2.data8;
	zonbiemaxspeed = Save::GetInstance()->save2.data9;
	zonbiedownspeed = Save::GetInstance()->save2.data10;
	bombdist = Save::GetInstance()->save2.data11;
	Seachspeed = Save::GetInstance()->save2.data12;
	Seachtime = Save::GetInstance()->save2.data13;
	chasedist = Save::GetInstance()->save2.data14;
	chasespeed = Save::GetInstance()->save2.data15;
	chasetime = Save::GetInstance()->save2.data16;
	Dashspeed = Save::GetInstance()->save2.data17;
	Dashtime = Save::GetInstance()->save2.data18;
	Sepdist = Save::GetInstance()->save2.data19;
	Sepspeed = Save::GetInstance()->save2.data20;
	cohspeed = Save::GetInstance()->save2.data21;
	zombirange = Save::GetInstance()->save2.data22;
	damage = Save::GetInstance()->save2.data23;
	zombieawaytime = Save::GetInstance()->save2.data24;
	zombiawayspeed = Save::GetInstance()->save2.data25;
	Searchcnt = Save::GetInstance()->save2.data50;
}

void Player::Gui()
{
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::Begin("Hyuman_Paramater");

	ImGui::SetNextWindowSize(ImVec2(300, 400));

	if (ImGui::CollapsingHeader(u8"Hyuman_Stance"))
	{
		ImGui::DragFloat("maxspeed", &hyumanmaxspeed);
		ImGui::DragFloat("rand_speed", &hyumanrandspeed);
		if (ImGui::CollapsingHeader(u8"Alignment"))
		{
			ImGui::DragFloat("ali_dist", &alidist);
		}
		if (ImGui::CollapsingHeader(u8"Separation"))
		{
			ImGui::DragFloat("sep_dist", &sepdist);
			ImGui::DragFloat("sep_zonbiedist", &sepzonbiedist);
			ImGui::DragFloat("sep_speed ", &sepspeed);
			ImGui::DragFloat("sep_time", &septime);

		}
	}
	if (ImGui::CollapsingHeader(u8"Zombie_Stance"))
	{
		ImGui::DragFloat("hp", &zonbiehp);
		ImGui::DragFloat("max_speed", &zonbiemaxspeed);
		ImGui::DragFloat("down_speed", &zonbiedownspeed);
		ImGui::DragFloat("attack_range", &zombirange);
		ImGui::DragFloat("damage", &damage);
	
		if (ImGui::CollapsingHeader(u8"bomb_range"))
		{
			ImGui::DragFloat("bomb_range", &bombdist);
		}
		if (ImGui::CollapsingHeader(u8"Search"))
		{
			ImGui::DragInt("CD_randtime", &Searchcnt);
			ImGui::DragFloat("Ser_speed", &Seachspeed);
			ImGui::DragFloat("Ser_time", &Seachtime);
		}
		if (ImGui::CollapsingHeader(u8"Chase"))
		{
			ImGui::DragFloat("chase_dist", &chasedist);
			ImGui::DragFloat("chase_speed", &chasespeed);
			ImGui::DragFloat("chase_time", &chasetime);
		}
		if (ImGui::CollapsingHeader(u8"Dash"))
		{
			ImGui::DragFloat("Dash_speed", &Dashspeed);
			ImGui::DragFloat("Dash_time", &Dashtime);
		}
		if (ImGui::CollapsingHeader(u8"Separation"))
		{
			ImGui::DragFloat("Sep_dist", &Sepdist);
			ImGui::DragFloat("Sep_speed", &Sepspeed);
		}
		if (ImGui::CollapsingHeader(u8"togather"))
		{
			ImGui::DragFloat("tog_speed", &cohspeed);
		}
		if (ImGui::CollapsingHeader(u8"away"))
		{
			ImGui::DragFloat("away_time", &zombieawaytime);
			ImGui::DragFloat("away_speed", &zombiawayspeed);
		}
	}
	ImGui::Checkbox("Paramater_Save", &save);
	ImGui::Checkbox("Paramater_Load", &load);

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void Player::SetNum()
{

	//人間の速さ
	 hyumanmaxspeed = 0.5f;//0.5
	 hyumanrandspeed = 5.0f;//5

	//hyumanali
	 alidist = 40.0f;//40

	//hyumnsep
	 sepdist = 10.0f;//10
	 sepzonbiedist = 40.0f;//30
	 sepspeed = 2.5f;//2.5
	 septime = 30.0f;//30


	 zonbiehp = 5.0f;//２
	 zonbiemaxspeed = 8.5f;//8.5
	 zonbiedownspeed= 0.05f;//0.05f

	//zonbiedamage
	 bombdist = 100.0f;//100
	//zonbiesearch
	 Searchcnt = 70;//70
	 Seachspeed = 0.2f;//0.3f
	 Seachtime = 50.0f;//50

	 chasedist = 50.0f;//50
	 chasespeed = 1.5f;//1.5
	 chasetime = 30.0f;//30

	 Dashspeed = 2.5f;//3.5f
	 Dashtime = 20.0f;//40

	//zonbiesep
	 Sepdist = 10.0f;//10
	 Sepspeed = 1.0f;//1.0

	 zombiawayspeed = 1.3f;//1.5
	 zombieawaytime = 15.0f;//１０

	//集合速度
	 cohspeed = 1.0f;//１．０

	//ゾンビとのダメージ距離
	 zombirange = 15.0f;//15
	 damage = 1.0f;//１．０
}

int Player::GetHp()
{
	return hp;
}

float Player::boid_angle(const Pvector& v)
{
	// 内積の定義から
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

float Player::getDesSep() const
{
	return desSep;
}

float Player::getDesAli() const
{
	return desAli;
}

float Player::getDesCoh() const
{
	return desCoh;
}

float Player::getSepW() const
{
	return SepW;
}

float Player::getAliW() const
{
	return AliW;
}

float Player::getCohW() const
{
	return CohW;
}

void Player::setDesSep(float x)
{
	desSep += x;
}

void Player::setDesAli(float x)
{
	desAli += x;
}

void Player::setDesCoh(float x)
{
	desCoh += x;
}

void Player::setSepW(float x)
{
	SepW += x;
}

void Player::setAliW(float x)
{
	AliW += x;
}

void Player::setCohW(float x)
{
	CohW += x;
}
