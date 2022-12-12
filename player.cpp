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

	SetScale(0.001f, 0.001f, 0.001f);
	champion = false;
	desSep = 15;
	desAli = 55;
	desCoh = 20;
	SepW = 1.5;
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
	if (ZOMBIE <= nowzombiecnt)
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


	acceleration = Pvector(0, 0);
	velocity = Pvector(PlayerMgr::GetInstance()->StickXRig, PlayerMgr::GetInstance()->StickYRig);//加速度
	//velocity = Pvector(0, 0);//加速度
	location = Pvector(x, y);//ポジション
	maxSpeed = hyumanmaxspeed;
	maxForce = 0.5;
	follow = Follow::PLAYER;

	champion = true;
	desSep = 5;
	desAli = 40;
	desCoh = 50;
	SepW = 1.5;
	AliW = 1.0;
	CohW = 0.2;

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
	SepW = 1.5;
	AliW = 1.0;
	CohW = 1.0;
	boidshp.Init();
}


void Player::zombie_reborn(float x, float y)
{
	hp = zonbiehp;
	location = Pvector(x, y);//ポジション
}

void Player::Draw(int animenum) {
	if (this != nullptr)
	{
		if (follow == Follow::ZONBIE)
		{
			boidshp.Update(XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43));

			boidshp.Draw();
		//	m_model->Update2(zonbieanime, m_mtx);
		//	if (m_model->m_assimpfile.animationreset == true)
		//	{
		//		debuglog("sssssssssss");
		//	}
		}	
		if (follow != Follow::ZONBIE)
		{	// モデル描画
		//	m_model->Draw(m_mtx);
		}

	}
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
		Ground::GetInstance()->GetPlayerHeight(*this);

		boid_borders();


		if (awaycnt > 0)
		{
			awaycnt -= 1;
		}
		if (awaycnt == 0) {
			boid_accel -= 0.03f;
		}
		if (boid_accel < 1.0f)
		{
			boid_accel = 1.0f;
		}


		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

		scale._11 = 2.0f;
		scale._22 = 2.0f;
		scale._33 = 2.0f;

		angle.y = 0.0f;
		angle.y = -GetAtan(velocity.x, velocity.y);
		angle.y -= 90.0f;
		float ang = angle.y;
		SetAngle();
		angle.y -= b_angle;
		b_angle = ang;

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
		Ground::GetInstance()->GetPlayerHeight(*this);


		//Z軸を取り出す
		axisZ.x = m_mtx._31;
		axisZ.y = m_mtx._32;
		axisZ.z = m_mtx._33;
		axisZ.w = 0.0f;

		//float ease_cnt = 1-(ease_nowcnt / 60.0f);
		//ease_nowcnt--;

		//if (ease_nowcnt > 0)
		//{
		//	boid_accel = ease_out(ease_cnt, 2.0f, 0.1f, 10.0f);
		//}
		//if (ease_nowcnt <= 0)
		//{
		//	ease_nowcnt = 0;
		//}

		/*if (this->insideflg)
		{
			this->boid_accel = PlayerMgr::GetInstance()->accel;
			insideflg = false;

		}*/

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

		if (boid_accel > 8.5f)
		{
			boid_accel = 8.5f;
		}

		if (boid_accel > 0.5)
		{
			zonbieanime = 1;
		}
		else if (boid_accel <= 0.5)
		{
			zonbieanime = 0;
		}

		angle.y = 0.0f;

		angle.y = -GetKakudo(angley.x, angley.y);
		angle.y -= 90.0f;
		if (angle.y > 360)
		{
			angle.y -= 360.0f;
		}


		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

		scale._11 = 5.2f;
		scale._22 = 5.2f;
		scale._33 = 5.2f;



		float ang = angle.y;
		SetAngle();
		angle.y -= b_angle;
		b_angle = ang;

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
//使ってない
//void Player::FollowUpdate()
//{
//
//	Ground::GetInstance()->GetPlayerHeight(*this);
//	//Z軸を取り出す
//	axisZ.x = m_mtx._31;
//	axisZ.y = m_mtx._32;
//	axisZ.z = m_mtx._33;
//	axisZ.w = 0.0f;
//	//angle.y = -PlayerMgr::GetInstance()->pad_rig;
//
//	PlayerMgr::GetInstance()->accel *= 1.0f;//anglecos;
//	if (PlayerMgr::GetInstance()->accel > 6.5f) PlayerMgr::GetInstance()->accel = 6.5f;
//
//	boid_accel = PlayerMgr::GetInstance()->accel;
//
//
//	velocity.x = axisZ.x * boid_accel;
//	velocity.y = axisZ.z * boid_accel;
//
//	boid_borders();
//
//	m_pos.x = location.x;
//	m_pos.z = location.y;
//
//	//SetAngle();
//	m_mtx._41 = m_pos.x;
//	m_mtx._42 = m_pos.y + 4.0f;
//	m_mtx._43 = m_pos.z;
//}
//


void Player::Finalize() {
//	m_model->Uninit();
}



void Player::applyForce(const Pvector& force)
{
	acceleration.addVector(force);
}

void Player::Move_And_Delete(float arraynum, std::vector<Player>& player_vector1, std::vector<Player>& player_vector2)
{
	//1の配列へ２の配列の要素番号を移動
	player_vector1.push_back(std::move(player_vector2[arraynum]));

	//いた場所の配列を消す
	player_vector2.erase(player_vector2.begin() + arraynum);

}

void Player::Delete(float arraynum, std::vector<Player>& Player_Vector1)
{
	Player_Vector1.erase(Player_Vector1.begin() + arraynum);
}


void Player::boids_attack(std::vector<Player>& player_vector, Player& zonbie, std::vector<UniqueEnemy_Bomb>& unique_enemy_vector)
{
	if (changeflg)
	{
		for (auto& i : player_vector)
		{
			float dd = i.location.distance(zonbie.location);					

			//hp減産処理
			if (dd < zombirange)
			{
				i.hp -= damage;

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

//Pvector Player::boid_view(std::vector<Player>& player_vector, Player& implayer)
//{
//	// How far can it see?
//	float sightDistance = 100;
//	float periphery = PI / 4;
//
//	for (int i = 0; i < maxnum; i++) {
//		// A vector that points to another boid and that angle
//		desired ={0,0};
//		desired = desired.subTwoVector(it->location, location);
//
//		// How far is it
//		float d = location.distance(it->location);
//		
//		// What is the angle between the other boid and this one's current direction
//		float desireda = velocity.angleBetween(desired);
//
//		// If it's within the periphery and close enough to see it
//		if (desireda < periphery && d > 0 && d < sightDistance) {
//			//視野角にいるboidだけで３法則
//			//boid_flock(player_vector, implayer);
//		}
//	}
//	return Pvector();
//}
//
//

//std::vector<Player>> grid[100][100] = { {} };
void Player::boid_run(std::vector<Player>& player_vector, std::vector<Player>& zonbie_vector)
{
	boid_flock(player_vector,zonbie_vector);
	boid_update();

}

void Player::zonbie_run(std::vector<Player>& player_vector, std::vector<Player>& human_vector, Pvector mousevec)
{
	zonbie_flock(player_vector,human_vector, mousevec);
	boid_update();
}



Pvector sep = { 0,0 };
Pvector ali = { 0,0 };
Pvector coh = { 0,0 };
Pvector awa = { 0,0 };
Pvector dmg = { 0,0 };


//ボイドの群れに三法則を適用する
void Player::boid_flock(std::vector<Player>& player_vector, std::vector<Player>& zonbie_vector)
{
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	
	if (follow == Follow::FREE)
	{
		if (hsepflg)
		{
			sep = boid_Separation(player_vector, zonbie_vector);
		}
		if (haliflg)
		{
			ali = boid_Alignment(player_vector);
		}
		//if (hcohflg)
		//{
		////	coh = boid_Cohesion(player_vector);
		//}
		//
	}

	//これらの力を任意に重み付けする
	//cen.mulScalar(CohW);
	sep.mulScalar(SepW);
	ali.mulScalar(AliW); // さまざまな特性の重みを変更する必要がある場合があります
//	coh.mulScalar(CohW);
	
	//  力ベクトルを加速度に加える
	applyForce(sep);
	applyForce(ali);
	//applyForce(coh);
	//applyForce(cen);

}

void Player::zonbie_flock(std::vector<Player>& player_vector, std::vector<Player>& human_vector, Pvector mousevec)
{
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	awa = { 0,0 };
	dmg = { 0,0 };

	
	if ((boid_accel < 0.5f) || (PlayerMgr::GetInstance()->gatherflg))
	{
		if (zsepflg)
		{
			sep = boid_inSeparation(player_vector);
		}
	}

	if (PlayerMgr::GetInstance()->scatterflg)
	{
		if (zscaflg)
		{
			awaycnt = 0;
			coh = zonbie_Scatter();
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
			if (boid_accel < 0.4f)
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
	
	
	//これらの力を任意に重み付けする
	//cen.mulScalar(CohW);
	sep.mulScalar(SepW);
	ali.mulScalar(AliW); // さまざまな特性の重みを変更する必要がある場合があります
	coh.mulScalar(CohW);
	awa.mulScalar(1.0f);
	dmg.mulScalar(3.0f);
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
	if (follow == Follow::FREE)
	{
		//スローダウンを急激にしないために
		//acceleration.mulScalar(0.35f);
		//  更新速度
		velocity.addVector(acceleration);
		velocity.normalize();
		//  制限速度
		velocity.mulScalar(hyumanmaxspeed);
		//velocity.limit(hyumanmaxspeed);
		velocity.mulScalar(boid_accel);
		location.addVector(velocity);
		// 各サイクルで加速度を 0 にリセットする
		acceleration.mulScalar(0);
	}
	else if (follow != Follow::FREE)
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

			if (boid_accel <= 0.5f)
			{
				awayflg = false;
			}

			acceleration.normalize();

			acceleration.mulScalar(boid_accel);

			//  更新速度
			velocity.addVector(acceleration);


			//  制限速度
		//velocity.limit(maxSpeed);
		
			
				location.addVector(velocity);
			

		/*	if (boid_accel > 1.0)
			{
				velocity.normalize();
				angley.x = velocity.x;
				angley.y = velocity.y;
			}*/
			// 各サイクルで加速度を 0 にリセットする
			velocity.mulScalar(0);
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
Pvector Player::boid_Separation(std::vector<Player>& player_vector, std::vector<Player>& zonbie_vector)
{
	// ボイド間分離視野距離
	//float desiredseparation = 10;//視野　プレイヤーからの距離
	steer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します

	//for (int i = 0; i < sizeof(player_vector)/sizeof(player_vector[0]); i++)//0回
	for (auto& it : player_vector)
	{

		// 現在のboidから見ているboidまでの距離を計算する
		if (it.follow == Follow::FREE)
		{
			float d = location.distance(it.location);
			// これが仲間のボイドであり、近すぎる場合は、離れてください
			if ((d > 0) && (d < sepdist)) {
				desired = { 0,0 };
				desired = desired.subTwoVector(location, it.location);
				desired.normalize();
				desired.divScalar(d);      // Weight by distance
				steer.addVector(desired);
				count++;
			}
		}

	}
	for (auto& it : zonbie_vector)
	{

		float d = location.distance(it.location);
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
		if ((d > 0) && (d < sepzonbiedist) && it.predator == true) {
			desired = { 0,0 };
			desired = desired.subTwoVector(location, it.location);
			desired.mulScalar(900);
			steer.addVector(desired);
			count++;

			boid_accel = sepspeed;
			awaycnt = septime;
		}
	}
	

	// 位置の平均差を加速度に加算
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude2x() > 0) {
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(hyumanmaxspeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	
	}
	return steer;
}

Pvector Player::boid_inSeparation(std::vector<Player>& player_vector)
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
			if (Sepdist < 10.0f)
			{
				Sepdist = 10.0f;
			}
		}
		else if (!PlayerMgr::GetInstance()->gatherflg)
		{
			Sepdist += 0.2f;
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
		if (it.follow != Follow::FREE)
		{
			float d = location.distance(it.location);
			if ((d > 0) && (d < Sepdist)) {

				//desiredseparation /= count;
					// これが仲間のボイドであり、近すぎる場合は、離れてください
				if ((d > 0) && (d < Sepdist)) {
					desired = { 0,0 };
					desired = desired.subTwoVector(location, it.location);
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
Pvector Player::boid_Alignment(std::vector<Player>& player_vector)
{

	desired = { 0,0 };
	int count = 0;
	for (auto& it : player_vector)
	{

		if (it.follow == Follow::FREE)
		{
			float d = location.distance(it.location);
			if ((d > 0) && (d < alidist)) { // 0 < d < 50
				desired.addVector(it.velocity);
				count++;
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


Pvector Player::boid_zonbieAlignment(Pvector mousepos)
{

	if (insideflg)
	{
		if (PlayerMgr::GetInstance()->velocityflg)
		{
			vel = { 0,0 };
			desired = { 0,0 };

			ali_vel = mousepos;
			acceleration = { ali_vel.x,ali_vel.y };
			acceleration.mulScalar(-1);

			angley.x = acceleration.x;
			angley.y = acceleration.y;

			ali_vel.normalize();
			ali_vel.mulScalar(-1.0f);
			///velocity = mousepos;
			this->boid_accel =Dashspeed;
			insideflg = false;
			awaycnt = Dashtime;
		}
	}

	return ali_vel;
}

Pvector Player::boid_zonbieAway(std::vector<Player>& player_vector)
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
			float d = location.distance(it.location);
			if (d < before_distanse) {
				before_distanse = d;
				nearplayer = it.location;
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


			this->boid_accel =1.5f;
			awayflg = true;
			awaycnt = 30;
		}
	}
	return desired;
}

Pvector Player::boid_zonbieSearch()
{
	int cnt = rand() % Searchcnt;
	if (cnt == 0)
	{
		vel = { 0,0 };
		desired = { 0,0 };

		ali_vel ={0,0};

		float x = rand() % 100-50.0f;
		float y = rand() % 100-50.0f;
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
Pvector Player::boid_Cohesion(std::vector<Player>& player_vector)
{
	float neighbordist = desCoh;
	desired = { 0,0 };
	int count = 0;
	for (auto& it : player_vector)
	{
		float d = it.location.distance(this->location);
		if ((d > 0) && (d < neighbordist)) {
			desired.addVector(it.location);
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
Pvector Player::zonbie_Scatter()
{
	ali_vel = { 0,0 };
	velocity = { 0,0 };
	acceleration = { 0,0 };
	
	vel = { 0,0 };
	desired = { 0,0 };
	boid_accel =1.0f;
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

				this->hp -= 2;
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
Pvector Player::boid_inCohesion(std::vector<Player>& player_vector)
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
	 hyumanmaxspeed = 1.5f;//1.5
	 hyumanrandspeed = 5.0f;//5

	//hyumanali
	 alidist = 40.0f;//40

	//hyumnsep
	 sepdist = 10.0f;//10
	 sepzonbiedist = 30.0f;//30
	 sepspeed = 2.0f;//2.0
	 septime = 30.0f;//30


	 zonbiehp =2.0f;//２
	 zonbiemaxspeed = 8.5f;//8.5
	 zonbiedownspeed= 0.05f;//0.05f

	//zonbiedamage
	 bombdist = 100.0f;//100
	//zonbiesearch
	 Searchcnt = 70;//70
	 Seachspeed = 0.3f;//0.3f
	 Seachtime = 50.0f;//50

	 chasedist = 50.0f;//50
	 chasespeed = 1.5f;//1.5
	 chasetime = 30.0f;//30

	 Dashspeed = 2.5f;//3.5f
	 Dashtime = 20.0f;//40

	//zonbiesep
	 Sepdist = 10.0f;//10
	 Sepspeed = 1.0f;//1.0

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
