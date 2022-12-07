#include	"player.h"
#include	"drawaxis.h"
#include    "CCamera.h"
#include"Notes_Arrange.h"
#include <cstdlib>
#include"PlayerMgr.h"
#include"CHeight_Map.h"
#include"ground.h"
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

static bool sepflg = false;
static bool aliflg = false;
static bool cohflg = false;
static bool awaflg = false;
static bool dmgflg = false;
static bool changeflg = false;

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
	float xx = rand() % 4 - 2.0f;
	float yy = rand() % 4 - 2.0f;

	acceleration = Pvector(0, 0);
	velocity = Pvector(xx, yy);//加速度
	location = Pvector(x, y);//ポジション
	float sp = rand() % 5;
	sp *= 0.1f;
	maxSpeed = 1.5f + sp;
	maxSpeed *= 0.5f;
	maxForce = 0.7f;

	boid_accel = 1.0f;


	champion = false;
	desSep = 15;
	desAli = 55;
	desCoh = 20;
	SepW = 1.5;
	AliW = 1.0;
	CohW = 0.2;
}

void Player::zonbie_Init(float x, float y)
{
	acceleration = Pvector(0, 0);

	location = Pvector(x / 10, y / 10);//ポジション
	maxSpeed = 3.5;
	maxForce = 2.5;

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



void Player::boid_player_Init(float x, float y)
{
	acceleration = Pvector(0, 0);
	velocity = Pvector(PlayerMgr::GetInstance()->StickXRig, PlayerMgr::GetInstance()->StickYRig);//加速度
	//velocity = Pvector(0, 0);//加速度
	location = Pvector(x, y);//ポジション
	maxSpeed = 3.5;
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
	SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::ONE)].modelname));
	maxSpeed = 3.5;
	maxForce = 0.5;
	hp = 2;
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
			// モデル描画
		m_model->Draw(m_mtx);	
		

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
	angle.y += 90.0f;
	float ang = angle.y;
	SetAngle();
	angle.y -= b_angle;
	b_angle = ang;

	DX11MtxMultiply(world,scale, rot);

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



void Player::ZonbieUpdate(int animenum ,int i)
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

	
	angle.y = -GetKakudo(angley.x, angley.y);
	angle.y += 180.0f;
	if (angle.y > 360)
	{
		angle.y -= 360.0f;
	}
	
	m_pos.x = location.x;
	m_pos.z = location.y;


	SetAngle();

	SetScale(0.1f, 0.1f, 0.1f);

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y + 4.0f;
	m_mtx._43 = m_pos.z;

}

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
	m_model->Uninit();
}



void Player::applyForce(const Pvector& force)
{
	acceleration.addVector(force);
}

void Player::Move_And_Delete(float arraynum, std::vector <std::shared_ptr<Player>>& player_vector1, std::vector <std::shared_ptr<Player>>& player_vector2)
{
	//1の配列へ２の配列の要素番号を移動
	player_vector1.push_back(std::move(player_vector2[arraynum]));

	//いた場所の配列を消す
	player_vector2.erase(player_vector2.begin() + arraynum);

}

void Player::Delete(float arraynum, std::vector<std::shared_ptr<Player>>& Player_Vector1)
{
	Player_Vector1.erase(Player_Vector1.begin() + arraynum);
}


void Player::boids_attack(std::vector<shared_ptr<Player>>& player_vector, std::shared_ptr<Player>& zonbie, std::vector<shared_ptr<UniqueEnemy_Bomb>>& unique_enemy_vector)
{
	if(changeflg)
	{ 
	for (auto& i : player_vector)
	{
		float dd = i->location.distance(zonbie->location);

		//hp減産処理
		if (dd < 8)
		{
			i->hp = 0;
		}
	}
	for (auto& u : unique_enemy_vector)
	{
		float dd = u->location.distance(zonbie->location);

		if (dd < 18)
		{
			u->hp -= 1;
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
	desired.mulScalar(maxSpeed);

	//ステアリング = 望ましいマイナス速度
	acceleration = acceleration.subTwoVector(desired, velocity);
	acceleration.normalize();
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

//Pvector Player::boid_view(std::vector<shared_ptr<Player>>& player_vector, std::shared_ptr<Player>& implayer)
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

//std::vector<std::shared_ptr<Player>> grid[100][100] = { {} };
void Player::boid_run(std::vector<shared_ptr<Player>>& player_vector, std::vector<shared_ptr<Player>>& zonbie_vector)
{
	boid_flock(player_vector,zonbie_vector);
	boid_update();

}

void Player::zonbie_run(std::vector<shared_ptr<Player>>& player_vector, std::vector<shared_ptr<Player>>& human_vector, Pvector mousevec)
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
void Player::boid_flock(std::vector<shared_ptr<Player>>& player_vector, std::vector<shared_ptr<Player>>& zonbie_vector)
{
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	
	if (follow == Follow::FREE)
	{
		if (sepflg)
		{
			sep = boid_Separation(player_vector, zonbie_vector);
		}
		if (aliflg)
		{
			ali = boid_Alignment(player_vector);
		}
		if (cohflg)
		{
			coh = boid_Cohesion(player_vector);
		}
		
	}

	//これらの力を任意に重み付けする
	//cen.mulScalar(CohW);
	sep.mulScalar(SepW);
	ali.mulScalar(AliW); // さまざまな特性の重みを変更する必要がある場合があります
	coh.mulScalar(CohW);
	
	//  力ベクトルを加速度に加える
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
	//applyForce(cen);

}

void Player::zonbie_flock(std::vector<shared_ptr<Player>>& player_vector, std::vector<shared_ptr<Player>>& human_vector, Pvector mousevec)
{
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	awa = { 0,0 };
	dmg = { 0,0 };

	
	if ((boid_accel < 0.5f) || (PlayerMgr::GetInstance()->gatherflg))
	{
		if (sepflg)
		{
			sep = boid_inSeparation(player_vector);
		}
	}

	if (PlayerMgr::GetInstance()->scatterflg)
	{
		if (sepflg)
		{
			awaycnt = 0;
			coh = zonbie_Scatter();
		}
	}

	if (PlayerMgr::GetInstance()->gatherflg)
	{
		if (cohflg)
		{
			awaycnt = 0;
			coh = boid_inCohesion(player_vector);
		}
	}
	if ((!PlayerMgr::GetInstance()->gatherflg) && (!PlayerMgr::GetInstance()->scatterflg))
	{
		if (awaflg)
		{
			if (boid_accel < 0.4f)
			{
				awa = boid_zonbieSearch();
			}
		}
	}
	if (!PlayerMgr::GetInstance()->gatherflg) {
		if (awaflg)
		{
			awa = boid_zonbieAway(human_vector);
		}
	}
	if (aliflg)
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
		acceleration.mulScalar(0.35f);
		//  更新速度
		velocity.addVector(acceleration);
		//  制限速度
		velocity.limit(maxSpeed);
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
				this->boid_accel =1.0f;
			}
			//else if (PlayerMgr::GetInstance()->scatterflg)
			//{
			//	//acceleration.mulScalar(0);

			////	this->boid_accel = PlayerMgr::GetInstance()->accel;
			//}

			//スローダウンを急激にしないために
			//acceleration.mulScalar(0.35f);

			//velocity.mulScalar(boid_accel);

			if (boid_accel == 0.5f)
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
Pvector Player::boid_Separation(std::vector<shared_ptr<Player>>& player_vector, std::vector<shared_ptr<Player>>& zonbie_vector)
{
	// ボイド間分離視野距離
	float desiredseparation = 10;//視野　プレイヤーからの距離
	steer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します

	//for (int i = 0; i < sizeof(player_vector)/sizeof(player_vector[0]); i++)//0回
	for (auto& it : player_vector)
	{
		if (it != nullptr)
		{
			// 現在のboidから見ているboidまでの距離を計算する
			if (it->follow == Follow::FREE)
			{
				float d = location.distance(it->location);
				// これが仲間のボイドであり、近すぎる場合は、離れてください
				if ((d > 0) && (d < desiredseparation)) {
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
		if (it != nullptr)
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
			 if ((d > 0) && (d < desiredseparation + 20) && it->predator == true) {
				desired = { 0,0 };
				desired = desired.subTwoVector(location, it->location);
				desired.mulScalar(900);
				steer.addVector(desired);
				count++;

				boid_accel = 2.0f;
				awaycnt = 30;
			}
		}
	}

	// 位置の平均差を加速度に加算
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude2x() > 0) {
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	
	}
	return steer;
}

Pvector Player::boid_inSeparation(std::vector<shared_ptr<Player>>& player_vector)
{
	// ボイド間分離視野距離
	this->desSep;//視野　プレイヤーからの距離

	if (this->follow == Follow::ZONBIE)
	{
	///	acceleration = { 0,0 };
		velocity = { 0,0 };
		/*	if (PlayerMgr::GetInstance()->accel > 0)
			{
				desiredseparation += 0.002f;
				if (des >= 10.0f)
				{
					des = 10.0f;
				}
			}
			else
			{
				des += 0.001f;
				if (des >= 20.0f)
				{
					des = 20.0f;
				}
			}*/

	

		if (PlayerMgr::GetInstance()->gatherflg)
		{
			this->desSep -= 0.1f;
			if (this->desSep < 10.0f)
			{
				this->desSep = 10.0f;
			}
		}
		else if (!PlayerMgr::GetInstance()->gatherflg)
		{
			this->desSep += 0.2f;
			if (this->desSep > 25.0f)
			{
				this->desSep = 25.0f;
			}
		}
	}

	steer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します
	for (auto& it : player_vector)
	{
		if (it != nullptr)
		{
			// 現在のboidから見ているboidまでの距離を計算する
			if (it->follow != Follow::FREE)
			{
				float d = location.distance(it->location);
				if ((d > 0) && (d < this->desSep)) {

					//desiredseparation /= count;
						// これが仲間のボイドであり、近すぎる場合は、離れてください
					if ((d > 0) && (d < this->desSep)) {
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
Pvector Player::boid_Alignment(std::vector<shared_ptr<Player>>& player_vector)
{
	float neighbordist = desAli; // Field of vision

	desired = { 0,0 };
	int count = 0;
	for (auto& it : player_vector)
	{

		if (it->follow == Follow::FREE)
		{
			float d = location.distance(it->location);
			if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
				desired.addVector(it->velocity);
				count++;
			}
		}

	}
	// 整列するのに十分近いボイドがある場合...
	if (count > 0) {
		desired.divScalar((float)count);// 合計を近いボイドの数で割ります (速度の平均)
		desired.normalize();            // 合計を単位ベクトルに変換し、
		desired.mulScalar(maxSpeed);    //maxSpeed を掛ける
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
			this->boid_accel =3.5f;
			insideflg = false;
			awaycnt = 40;
		}
	}

	return ali_vel;
}

Pvector Player::boid_zonbieAway(std::vector<shared_ptr<Player>>& player_vector)
{// ボイド間分離視野距離
	float desiredseparation = 50.0f;//視野　プレイヤーからの距離
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
		if ((before_distanse > 0) && (before_distanse < desiredseparation))
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
	int cnt = rand() % 70;
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
		this->boid_accel = 0.5f;
		awaycnt = 50;
	}
	return desired;
}

// 結合
// 近くのボイドの平均位置を見つけ、
// その方向に移動する操舵力。
Pvector Player::boid_Cohesion(std::vector<shared_ptr<Player>>& player_vector)
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
			float desiredseparation = 100;//視野　プレイヤーからの距離
		
		
			
			ali_vel.x = b->GetMtx()._41;
			ali_vel.y = b->GetMtx()._43;

			float d = location.distance(ali_vel);
			if (d < desiredseparation)
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
Pvector Player::boid_inCohesion(std::vector<shared_ptr<Player>>& player_vector)
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
		ImGui::Begin("Zonbie Rule");

		ImGui::SetNextWindowSize(ImVec2(300, 400));
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;
		ImGui::Checkbox("Separation", &sepflg);
		ImGui::Checkbox("Ali", &aliflg);
		ImGui::Checkbox("Cohesion", &cohflg);
		ImGui::Checkbox("Away", &awaflg);
		ImGui::Checkbox("Dmg", &dmgflg);
		ImGui::Checkbox("change", &changeflg);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}
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
