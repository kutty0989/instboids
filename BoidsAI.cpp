#include	"BoidsAI.h"
#include	"drawaxis.h"
#include    "CCamera.h"
#include"Notes_Arrange.h"
#include <cstdlib>
#include"BoidsAIMgr.h"
#include"CHeight_Map.h"
#include"billboardMgr.h"
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

#define w_height window_height 
#define w_width window_width
#define PI 3.141592635
#define debuglog(a) std::cout<<a<<std::endl;

class Scean;
XAudio audio;						//音楽ならす


static float m_rig;//プレイヤーの現在の角度保存用

/// <summary>
/// AIのパラメーターのstatic変数
/// </summary>
/////////////////////////////////////////////////////////

//地形のスケール	
float scaling = Ground::GetInstance()->scaling;
	
/// <summary>
/// 小さく赤いAIの適応するかどうかのルール
/// </summary>

//分離
bool BoidsAI::hsepflg = false;
//整列
bool BoidsAI::haliflg = false;
//スロープ
bool BoidsAI::slopeflg = false;
//ポケット
bool BoidsAI::pocketflg = false;
//最高速度
float BoidsAI::hyumanmaxspeed;//1.5

float BoidsAI::hyumanrandspeed;//5
//整列の範囲
float BoidsAI::alidist;//40
//分離の範囲
float BoidsAI::sepdist;//10
//逃避範囲
float BoidsAI::sepzonbiedist;//30
//分離速度
float BoidsAI::sepspeed;//2.0
//逃げる時間
float BoidsAI::septime;//30

/// <summary>
/// 操作プレイヤーの変数
/// </summary>
bool BoidsAI::zdashflg = false;
bool BoidsAI::zscaflg = false;
bool BoidsAI::zsepflg = false;
bool BoidsAI::zcohflg = false;
bool BoidsAI::zserflg = false;
bool BoidsAI::zawaflg = false;

bool BoidsAI::dmgflg = false;
bool BoidsAI::changeflg = false;

bool BoidsAI::bbombflg = false;
bool BoidsAI::bserflg = false;
bool BoidsAI::texspeedflg = false;
bool BoidsAI::shootflg = false;


float BoidsAI::zonbiehp;//２
float BoidsAI::zonbiemaxspeed;//8.5
float BoidsAI::zonbiedownspeed;//0.05f
//////////////////////////////////////////////

//ユニークな敵の変数
float BoidsAI::bombdist;//100
//zonbiesearch
int BoidsAI::Searchcnt;//70
float BoidsAI::Seachspeed;//0.3f
float BoidsAI::Seachtime;//50

float BoidsAI::chasedist;//50
float BoidsAI::chasespeed;//1.5
float BoidsAI::chasetime;//30
float BoidsAI::Dashspeed;//3.5f
float BoidsAI::Dashtime;//40

//zonbiesep
float BoidsAI::Sepdist;//10
float BoidsAI::Sepspeed;//1.
					   
//集合速度
float BoidsAI::cohspeed;//１．０

//zombieaway
float BoidsAI::zombiawayspeed;//1.5
float BoidsAI::zombieawaytime;//１０

//ゾンビとのダメージ距離
float BoidsAI::zombirange;//15
float BoidsAI::damage;//１．０

bool BoidsAI::save = false;
bool BoidsAI::load = false;

float length = 200;
///////////////////////////////////////////////////////////




//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

bool BoidsAI::Init() {

	// 行列初期化
	DX11MtxIdentity(m_mtx);

	//XYZの軸を取り出し保管
	SetQutenion();

	float posx = rand() % 400 - 200;//初期値
	float posz = rand() % 400 - 200;//初期値
	SetPos(XMFLOAT3(posx, 0.0f, posz));//初期値
	
	//角度の初期
	angle.x = 0.0f;
	angle.z = 0.0f;
	angle.y = 0.0f;

	return true;
}


bool BoidsAI::CharengerInit()
{
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	//XYZの軸を取り出し保管
	SetQutenion();

	//場所の初期値
	float posx = rand() % 400;
	float posz = rand() % 400;
	posx -= 200;
	posz -= 200;
	//場所を０に
	SetPos(XMFLOAT3(0, 0, 0));
	//角度を調整
	angle.x = -90.0f;
	angle.z = 0.0f;
	angle.y = -90.0f;
	SetAngle();

	champion = true;

	return true;
}

/// <summary>
/// 小さく赤いAIの初期化
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void BoidsAI::boid_Init(float x, float y)
{
	//初期値
	float xx = rand() % 100 - 50.0f;
	float yy = rand() % 100 - 50.0f;
	//生存している状態に
	BSTATUS::LIVE;
	acceleration = Pvector(1, 1);
	velocity = Pvector(xx, yy);//加速度
	location = Pvector(x, y);//ポジション
	maxSpeed = 1.0f; //+sp;
	maxForce = 0.7f;
	hp = 1;
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

/// <summary>
/// 操作するAIの初期値
/// </summary>
/// <param name="x">初期場所</param>
/// <param name="y"></param>
/// <param name="nowzombiecnt"></param>
void BoidsAI::zonbie_Init(float x, float y, int nowzombiecnt)
{

	acceleration = Pvector(0, 0);
	bulletcreatecnt = rand() % 10 + 60;
	velocity = { 0,0 };
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
	boid_accel = 0.0f;

	//hpUIの初期化
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

void BoidsAI::boid_BoidsAI_Init(float x, float y)
{


}

void BoidsAI::follow_Init()
{
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

}


/// <summary>
/// AI再生成の関数
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void BoidsAI::zombie_reborn(float x, float y,float z)
{
	bstatus = BoidsAI::BSTATUS::LIVE;
	hp = zonbiehp;
	rebornpos.x= x;
	rebornpos.y =z;
	reborn_flg = true;
}

/// <summary>
/// ｈｐの更新
/// </summary>
void BoidsAI::UpdateHp() {

	//生きてるＡｉだけ
	if (follow == Follow::ZONBIE)
	{
		boidshp.UpdateHp(hp);
		boidshp.Update(XMFLOAT3(this->GetMtx()._41,this->GetMtx()._42,this->GetMtx()._43));
		boidshp.Draw();
	}
}

/// <summary>
/// ｘｙｚ軸にラインを引く
/// </summary>
void BoidsAI::HyumanDrawAxis() {
	drawaxis(m_mtx, 5.0f, XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43));
}

/// <summary>
/// /モデルを描画とラインをxyzに引く
/// </summary>
void BoidsAI::DrawWithAxis() {
	// モデル描画
	drawaxis(m_mtx, 200, m_pos);
}

struct FLOAT3
{
	float x, y, z;
};




void BoidsAI::Update(bool input, std::vector<ZombieBullet*> zbvec) {

	//ＡＩを倒したときの流れ
	if (bstatus == BSTATUS::LIVE)
	{
		for (int i = 0; i < zbvec.size(); i++)
		{
			if (zbvec.at(i)->m_sts == ZOMBIEBSTS::LIVE)
			{
				float disx = this->GetMtx()._41 - zbvec.at(i)->GetMtx()._41;
				float disy = this->GetMtx()._43 - zbvec.at(i)->GetMtx()._43;
				float dist = disx * disx + disy * disy;
			//弾と当たったら
				if (length > dist)
				{
					this->hp = 0;
					this->m_sts = BoidsAI::STATUS::DEAD;
					zbvec.at(i)->m_sts = ZOMBIEBSTS::DEAD;
					//スコアを足す
					BoidsAIMgr::GetInstance()->ScoreNum += 10;
					//爆発演出
					BillBoardMgr::GetInstance()->ExplsionCreate(XMFLOAT3(this->GetMtx()._41, this->GetMtx()._42, this->GetMtx()._43));
				}
			}
		}
	}

	if (bstatus == BSTATUS::LIVE)
	{
		//マップから出ないように
		boid_borders();

		///減速処理
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
		//一定以下の遅さにしないように
		if (boid_accel < 1.0f)
		{
			boid_accel = 1.0f;
		}
		if (boid_accel > 4.0f)boid_accel = 4.0f;
		///////////

		//各行列を初期化
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);


		scale._11 = 2.0f;
		scale._22 = 2.0f;
		scale._33 = 2.0f;

	
		Ground::GetInstance()->GetBoidsAIHeight(*this);
		//今回の角度を保存
		if (slopeflg)
		{
			boid_accel = Ground::GetInstance()->AccelBoid(*this);
		}
		velocity.mulScalar(boid_accel);
		location.addVector(velocity);

		//向き調整
		angle.y = -GetAtan(velocity.x, velocity.y);
		//角度調整
		angle.y -= 90.0f;
		SetAngle();
	
		//mtx計算
		DX11MtxMultiply(world, scale, rot);

		m_pos.x = location.x;
		m_pos.z = location.y;

		trans._41 = m_pos.x;
		trans._42 = m_pos.y + 4.0f;
		trans._43 = m_pos.z;

		world._41 = trans._41;
		world._42 = trans._42;
		world._43 = trans._43;

		//行列適応
		m_mtx = world;

	}
	else
	{
		//死んでいる処理
		m_mtx._41 = 10000;
	}
}


/// <summary>
/// 操作するAIの更新
/// </summary>
/// <param name="animenum"></param>
/// <param name="i"></param>
void BoidsAI::BoidsAIAIUpdate(int animenum, int i)
{
	if (bstatus == BSTATUS::LIVE)
	{
		//ノックバック処理
		if (knockbackcnt > 0)
		{
			knockbackflg = true;
		}
		knockbackcnt -= 1;

		if (knockbackcnt <= 0)
		{
			knockbackflg = false;
			knockbackcnt = 0;
		}

		//地形から出ないように
		boid_borders();
		//行列初期化
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
		//角度調整
		angle.y = -GetKakudo(angley.x, angley.y);
		angle.y -= 90.0f;
		if (angle.y > 360)
		{
			angle.y -= 360.0f;
		}

		//再生成関数
		if (reborn_flg)
		{
			
		}
		else
		{
			//高さを求める関数
			Ground::GetInstance()->GetBoidsAIHeight(*this);
			
			//速度を落とさず移動する
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
			/////////////


			//加速度ノーマライズ
			acceleration.normalize();

			acceleration.mulScalar(boid_accel);

			//  更新速度
			velocity.addVector(acceleration);

			location.addVector(velocity);


			m_pos.x = location.x;
			m_pos.z = location.y;

		}


		//場所調整
		trans._41 = m_pos.x;
		trans._42 = m_pos.y + 4.0f;
		trans._43 = m_pos.z;

		scale._11 = 5.2f;
		scale._22 = 5.2f;
		scale._33 = 5.2f;


		//角度調整
		float ang = angle.y;
		SetAngle();
		angle.y -= b_angle;
		b_angle = ang;

		DX11MtxMultiply(world, scale, rot);

		world._41 = trans._41;
		world._42 = trans._42;
		world._43 = trans._43;

		m_mtx = world;

		//バレットを打つ処理
		if (shootflg == true)
		{
			bulletcnt++;
			if (bulletcnt == 30)
			{
				//バレット生成
				BoidsAIMgr::GetInstance()->ZombieBulletRemake(this->GetMtx(), XMFLOAT3(this->GetMtx()._41, this->GetMtx()._42, this->GetMtx()._43));
				bulletcnt = 0;
			}
		}
	}
	else
	{
	//死んだときの処理
	m_mtx._41 = 10000;
	}

}

/// <summary>
/// メインキャラの更新　
/// </summary>
void BoidsAI::FollowUpdate()
{

	Ground::GetInstance()->GetBoidsAIHeight(*this);
	//Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;
	//angle.y = -BoidsAIMgr::GetInstance()->pad_rig;

	BoidsAIMgr::GetInstance()->accel *= 1.0f;//anglecos;
	if (BoidsAIMgr::GetInstance()->accel > 6.5f) BoidsAIMgr::GetInstance()->accel = 6.5f;

	boid_accel = BoidsAIMgr::GetInstance()->accel;


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



void BoidsAI::Finalize() {
	m_model->Uninit();
}


//加速度を追加
void BoidsAI::applyForce(const Pvector& force)
{
	acceleration.addVector(force);
}

/// <summary>
/// 小さいAIの配列から移動と消去
/// </summary>
/// <param name="arraynum"></param>
/// <param name="BoidsAI_vector1"></param>
/// <param name="BoidsAI_vector2"></param>
void BoidsAI::Move_And_Delete(float arraynum, std::vector<BoidsAI*> BoidsAI_vector1, std::vector<BoidsAI*> BoidsAI_vector2)
{
	//1の配列へ２の配列の要素番号を移動
	BoidsAI_vector1.push_back(std::move(BoidsAI_vector2[arraynum]));

	//いた場所の配列を消す
	BoidsAI_vector2.erase(BoidsAI_vector2.begin() + arraynum);

}

void BoidsAI::Delete(float arraynum, std::vector<BoidsAI*> BoidsAI_Vector1)
{
	BoidsAI_Vector1.erase(BoidsAI_Vector1.begin() + arraynum);
}

//攻撃関数
void BoidsAI::boids_attack(std::vector<BoidsAI*>& BoidsAI_vector, BoidsAI& zonbie, std::vector<UniqueEnemy_Bomb*>& unique_enemy_vector)
{
	if (changeflg)
	{
		
	}
}

Pvector desired;//計算用の変数
Pvector des;//計算用の変数

// maxSpeed を制限し、必要な操舵力を見つけ、
//ベクトルを正規化します
Pvector BoidsAI::boid_seek(const Pvector& v)
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

/// <summary>
/// 視界の範囲を前方90度だけにする
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <returns></returns>
Pvector BoidsAI::boid_view(std::vector<BoidsAI*> BoidsAI_vector)
{
	// How far can it see?
	float sightDistance = 100;
	float periphery = PI / 2;

	for (int i = 0; i < BoidsAI_vector.size(); i++) {
		// A vector that points to another boid and that angle
		desired ={0,0};
		desired = desired.subTwoVector(BoidsAI_vector.at(i)->location, location);

		// How far is it
		float d = location.distance(BoidsAI_vector.at(i)->location);
		
		// What is the angle between the other boid and this one's current direction
		float desireda = velocity.angleBetween(desired);

		// If it's within the periphery and close enough to see it
		if (desireda < periphery && d > 0 && d < sightDistance) {
			//視野角にいるboidだけで３法則
			//boid_flock(BoidsAI_vector,zonbie_vector);
		}
	}
	return Pvector();
}



//std::vector<BoidsAI>> grid[100][100] = { {} };
void BoidsAI::boid_run(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> zonbie_vector)
{
	boid_flock(BoidsAI_vector, zonbie_vector);
	boid_update();

}

/// <summary>
/// 操作するAIの全更新
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <param name="human_vector"></param>
/// <param name="mousevec"></param>
/// <param name="uniquebomb"></param>
void BoidsAI::zonbie_run(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> human_vector, Pvector mousevec, std::vector<UniqueEnemy_Bomb*>& uniquebomb)
{
	zonbie_flock(BoidsAI_vector,human_vector, mousevec,uniquebomb);
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
void BoidsAI::boid_flock(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> zonbie_vector)
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
			sep = boid_Separation(BoidsAI_vector, zonbie_vector);
		}

		if (haliflg)
		{
			if (alifalse_cnt < 0)
			{
				ali = boid_Alignment(BoidsAI_vector);
			}
		}
		if (pocketflg)
		{
			down = boid_Down();
		}
	}

	//これらの力を任意に重み付けする
	sep.mulScalar(1.5f);
	ali.mulScalar(1.0f); // さまざまな特性の重みを変更する必要がある場合があります
	avo.mulScalar(1.0f); // さまざまな特性の重みを変更する必要がある場合があります
	down.mulScalar(1.0f);

	//  力ベクトルを加速度に加える
	applyForce(sep);
	applyForce(avo);
	applyForce(ali);
	applyForce(down);

}

void BoidsAI::zonbie_flock(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> human_vector, Pvector mousevec, std::vector<UniqueEnemy_Bomb*>& uniquebomb)
{
	//ルールのベクトルの初期化
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	awa = { 0,0 };
	dmg = { 0,0 };

	//分散処理
	if (BoidsAIMgr::GetInstance()->scatterflg)
	{
		if (zscaflg)
		{
			awaycnt = 0;
			coh = Zombie_Scatter();
		}
	}

	//分散している時とノックバック以外は行う
	if ((!zombie_scatterflg) && (!knockbackflg))
	{
		if ((boid_accel < 0.5f) || (BoidsAIMgr::GetInstance()->gatherflg))
		{
			if (zsepflg)
			{
				sep = boid_inSeparation(BoidsAI_vector);
			}
		}
		//集合処理
		if (BoidsAIMgr::GetInstance()->gatherflg)
		{
			if (zcohflg)
			{
				awaycnt = 0;
				coh = boid_Gather(BoidsAI_vector);
			}
		}
		//探索処理
		if ((!BoidsAIMgr::GetInstance()->gatherflg) && (!BoidsAIMgr::GetInstance()->scatterflg))
		{
			if (zserflg)
			{
				if (boid_accel < 0.2f)
				{
					awa = boid_zonbieSearch();
				}
			}
		}
		//アウェイ処理
		if (!BoidsAIMgr::GetInstance()->gatherflg) {
			if (zawaflg)
			{
				if (boid_accel < 0.4f)
				{
					awa = boid_zonbieAway(human_vector);
				}
			}
		}
		//ダッシュ処理
		if (zdashflg)
		{
			ali = boid_zonbieAlignment(mousevec);
		}
		if (dmgflg)
		{
			dmg = zonbie_damage(uniquebomb);
		}
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
void BoidsAI::boid_update()
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

		// 各サイクルで加速度を 0 にリセットする
		acceleration.mulScalar(0);
	}
	else if (follow != Follow::HYUMAN)
	{
		if (!champion)
		{


			if (BoidsAIMgr::GetInstance()->gatherflg)
			{
				this->boid_accel = cohspeed;
			}
			velocity.mulScalar(0);
			if (boid_accel <= 0.2f)
			{
				awayflg = false;
			}
		}
	}	
}


/// <summary>
/// マップの外に出ないようにする処理
/// </summary>
void BoidsAI::boid_borders()
{

	if (location.x < -BoidsAIMgr::GetInstance()->window_width * 0.5f)	location.x += BoidsAIMgr::GetInstance()->window_width;
	if (location.y < -BoidsAIMgr::GetInstance()->window_width * 0.5f)	location.y += BoidsAIMgr::GetInstance()->window_height;
	if (location.x > BoidsAIMgr::GetInstance()->window_height * 0.5f)	location.x -= BoidsAIMgr::GetInstance()->window_width;
	if (location.y > BoidsAIMgr::GetInstance()->window_height * 0.5f)	location.y -= BoidsAIMgr::GetInstance()->window_height;
}

Pvector steer(0, 0);

// 分離
// ボイド同士が近づきすぎないようにする
Pvector BoidsAI::boid_Separation(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> zonbie_vector)
{
	// ボイド間分離視野距離
	//float desiredseparation = 10;//視野　プレイヤーからの距離
	steer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します

	//for (int i = 0; i < sizeof(BoidsAI_vector)/sizeof(BoidsAI_vector[0]); i++)//0回
	if (boid_accel < 2.0f)
	{
		for (auto& it : BoidsAI_vector)
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

/// <summary>
/// 避ける関数
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <returns></returns>
Pvector BoidsAI::boid_Avoid(std::vector<BoidsAI*> BoidsAI_vector)
{
	Pvector stt = { 0,0 };
	for (auto& it : BoidsAI_vector)
	{
		XMFLOAT3 diff = XMFLOAT3(it->GetPos().x - this->GetPos().x, 0.0f, it->GetPos().z - this->GetPos().z);//障害物との距離

		//差を出す
		float distance;
		DX11Vec3Dot(distance, diff, diff);

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
		//ターゲットとのベクトルを正規化
		XMFLOAT3 target2ObstacleDirection;
		DX11Vec3Normalize(target2ObstacleDirection, diff);

		XMFLOAT3 forward = XMFLOAT3(this->angley.x, 1.0f, this->angley.y);

		DX11Vec3Normalize(forward, forward);

		//内角を求める
		float directionDot;
		DX11Vec3Dot(directionDot, target2ObstacleDirection, forward);

		//
		if (directionDot < 0) // 前方向に障害物がないか
		{
			return desired = { 0, 0 };
		}

		XMFLOAT3 forward2DiffCross;
		XMFLOAT3 forward2DiffCrossv;
		
		DX11Vec3Cross(forward2DiffCross, diff, forward);
		DX11Vec3Cross(forward2DiffCrossv, forward, diff);

		float forward2ObstacleDistance;
		DX11Vec3Length(forward2DiffCross, forward2ObstacleDistance);

		if (forward2ObstacleDistance > escaperange) // 障害物から逃げる範囲と速度ベクトルの直線が重なっていないか
		{
			return desired = { 0, 0 };
		}

		const float crossElementSum = forward2DiffCross.x + forward2DiffCross.y + forward2DiffCross.z;
		//const XMFLOAT3 axis;

		//距離が近すぎないか判断
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
		float aa = GetKakudo(forward2DiffCross.x, forward2DiffCross.z);
		DX11MtxRotationAxis(forward2DiffCross, aa, vec);

	}
	return desired;
	
}

/// <summary>
/// 分離関数
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <returns></returns>
Pvector BoidsAI::boid_inSeparation(std::vector<BoidsAI*> BoidsAI_vector)
{
	// ボイド間分離視野距離
	if (this->follow == Follow::ZONBIE)
	{
	///	acceleration = { 0,0 };
		velocity = { 0,0 };


		if (BoidsAIMgr::GetInstance()->gatherflg)
		{
			Sepdist -= 0.1f;
			

			if (Sepdist < 10.0f)
			{
				Sepdist = 10.0f;
			}
		}
		else if (!BoidsAIMgr::GetInstance()->gatherflg)
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
	for (auto& it : BoidsAI_vector)
	{

		// 現在のboidから見ているboidまでの距離を計算する
		if (it->follow != Follow::HYUMAN)
		{
			float d = location.distance(it->location);
			if ((d > 0) && (d < Sepdist)) {

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
Pvector BoidsAI::boid_Alignment(std::vector<BoidsAI*> BoidsAI_vector)
{

	desired = { 0,0 };
	int count = 0;
	if (boid_accel < 2.0f)
	{
		for (auto& it : BoidsAI_vector)
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

Pvector BoidsAI::boid_Down()
{
	angle.y = 0.0f;//角度リセット

//	velocity.addVector(acceleration);
	velocity.normalize();

	//ベクトル保存
	angley.x = velocity.x;
	angley.y = velocity.y;

	//boids計算から出た速度を元に向きを変更
	angle.y = GetAtan(velocity.x, velocity.y);


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

/// <summary>
/// AIのダッシュ関数
/// </summary>
///マウスで囲ったキャラをスワイプで操作する
/// <param name="mousepos"></param>
/// <returns></returns>
Pvector BoidsAI::boid_zonbieAlignment(Pvector mousepos)
{

	//マウスの中にいるか
	if (insideflg)
	{
		if (BoidsAIMgr::GetInstance()->velocityflg)
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

Pvector BoidsAI::boid_zonbieAway(std::vector<BoidsAI*> BoidsAI_vector)
{// ボイド間分離視野距離
	//float desiredseparation = chasedist;//視野　プレイヤーからの距離
	steer = { 0.0f,0.0f };
	int count = 0;
	
	float before_distanse = 100.0f;//一番近い距離保存用
	
	Pvector nearBoidsAI;//一番近い存在を保存する変数
	
	if (awayflg == false) {

		// 現在のボイドが捕食者であり、私たちが見ているボイドも捕食者である場合
		// 捕食者は近づいて、その後わずかに分離
		for (auto& it : BoidsAI_vector)
		{
			float d = location.distance(it->location);
			if (d < before_distanse) {
				before_distanse = d;
				nearBoidsAI = it->location;
			}
		}
		//一定範囲内か
		if ((before_distanse > 0) && (before_distanse < chasedist))
		{
	
			desired = { 0,0 };
			desired = desired.subTwoVector(location, nearBoidsAI);
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

/// <summary>
/// 近くのAIを探す動きをする
/// </summary>
/// <returns></returns>
Pvector BoidsAI::boid_zonbieSearch()
{
	//ランダム初期化
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution<int32_t> rand4(0,10000);
	std::uniform_int_distribution<int32_t> rand5(-150,150);
	
	
	int cnt = rand4(seed_gen)% Searchcnt;
	if (cnt == 0)
	{
		//ランダムに出された数値を向きに使う
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
Pvector BoidsAI::boid_Cohesion(std::vector<BoidsAI*> BoidsAI_vector)
{
	float neighbordist = desCoh;
	desired = { 0,0 };
	int count = 0;
	for (auto& it : BoidsAI_vector)
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
Pvector BoidsAI::Zombie_Scatter()
{
	if (zombie_scatterflg)
	{
		if (BoidsAIMgr::GetInstance()->scatterflg)
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

/// <summary>
/// 爆弾によるダメージを受けるかどうか
/// </summary>
/// <param name="uniquebomb"></param>
/// <returns></returns>
Pvector BoidsAI::zonbie_damage(std::vector<UniqueEnemy_Bomb*>& uniquebomb)
{
	for (auto& b : BulletMgr::GetInstance()->g_bullets) {
		if (b->explosion == true)
		{
			bombdist = 50;//視野　プレイヤーからの距離
		
			ali_vel.x = b->GetMtx()._41;
			ali_vel.y = b->GetMtx()._43;

			float d = location.distance(ali_vel);
			//爆弾のレンジ
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
				knockbackcnt = 40;
				
			}

		}
	}
	//全てのユニークな敵の存在を確認
	for (auto& b : uniquebomb){
		if (b->ubstatus== UniqueEnemy_Bomb::UBSTATUS::LIVE)
		{
			bombdist = 30;//視野　プレイヤーからの距離

			ali_vel.x = b->GetMtx()._41;
			ali_vel.y = b->GetMtx()._43;

			float d = location.distance(ali_vel);
			if (d < bombdist)
			{
			
				acceleration = { 0,0 };

				vel = { 0,0 };
				desired = { 0,0 };

				this->hp -= 1;
				desired = desired.subTwoVector(location, ali_vel); //sum = desired(average)
				desired.normalize();


				angley.x = desired.x;
				angley.y = desired.y;
				velocity = desired;

				boid_accel = 3.5f;
				zexplosionflg = true;
				knockbackcnt = 40;
			}

		}
	}
	ali_vel = { 0,0 };
	return desired;
}

/// <summary>
/// AIの集合操作
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <returns></returns>
Pvector BoidsAI::boid_Gather(std::vector<BoidsAI*> BoidsAI_vector)
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

		//マウスで長押しした場所を取得
		now_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
		now_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
		now_mousepos.x -= Application::CLIENT_WIDTH / 2 * 1.0f;
		now_mousepos.y = Application::CLIENT_HEIGHT / 2 * 1.0f - now_mousepos.y;

		//スクリーン座標に変換
		pos = Screenpos(this->GetPos());
		pos.x -= Application::CLIENT_WIDTH / 2;
		pos.y = Application::CLIENT_HEIGHT / 2 - pos.y;

		vel.x = pos.x;
		vel.y = pos.y;

		desired = desired.subTwoVector(now_mousepos, vel); 
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


	}

	return desired;

}

/// <summary>
/// スクリーン座標上に変換
/// </summary>
/// <param name="World_Pos"></param>
/// <returns></returns>
XMFLOAT3 BoidsAI::Screenpos(XMFLOAT3 World_Pos) {

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


void BoidsAI::SetAngle()
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

XMFLOAT3 BoidsAI::GetAngle()
{
	return angle;
}


/// <summary>
/// guiの変数を表示する
/// </summary>
void BoidsAI::CheckBox()
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
			ImGui::Checkbox("Zombie_Shoot", &shootflg);
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
			shootflg = true;

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

//ルールを初期化する
void BoidsAI::UnCheckBox()
{
	hsepflg = false;
	haliflg = false;
	texspeedflg = false;
	slopeflg = false;
	pocketflg = false;
	
	shootflg = false;
	zdashflg = false;
	zscaflg = false;
	zsepflg = false;
	zcohflg = false;
	zserflg = false;
	zawaflg = false;

	dmgflg = false;

	changeflg = false;

	bbombflg = false;
	bserflg = false;
}

/// <summary>
/// ルールのセーブ機能
/// </summary>
void BoidsAI::SaveNum()
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


//aiの値のロード
void BoidsAI::LoadNum()
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

void BoidsAI::Gui()
{
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::Begin("Hyuman_Paramater");

	ImGui::SetNextWindowSize(ImVec2(300, 400));

	if (ImGui::CollapsingHeader(u8"Hyuman_Stance"))
	{
		ImGui::SliderFloat("maxspeed", &hyumanmaxspeed, 0.0f, 3.0f);
		ImGui::SliderFloat("rand_speed", &hyumanrandspeed, 0.0f, 5.0f);

		if (ImGui::CollapsingHeader(u8"Alignment"))
		{
			ImGui::SliderFloat("ali_dist", &alidist, 0.0f, 100.0f);
	
		}
		if (ImGui::CollapsingHeader(u8"Separation"))
		{
			ImGui::SliderFloat("sep_dist", &sepdist, 0.0f, 50.0f);
			ImGui::SliderFloat("sep_zonbiedist", &sepzonbiedist, 0.0f, 100.0f);
			ImGui::SliderFloat("sep_speed ", &sepspeed, 0.0f,4.0f);
			ImGui::SliderFloat("sep_time", &septime, 0.0f, 100.0f);
		
		}
	}
	if (ImGui::CollapsingHeader(u8"Zombie_Stance"))
	{
		ImGui::DragFloat("hp", &zonbiehp);
		ImGui::SliderFloat("max_speed", &zonbiemaxspeed, 0.0f, 20.0f);
		ImGui::SliderFloat("down_speed", &zonbiedownspeed, 0.0f, 0.5f);
		ImGui::SliderFloat("attack_range", &zombirange, 0.0f, 40.0f);
		ImGui::SliderFloat("damage", &damage, 0.0f, 5.0f);
	
		if (ImGui::CollapsingHeader(u8"bomb_range"))
		{
			ImGui::SliderFloat("bomb_range", &bombdist, 0.0f, 200.0f);
		}
		if (ImGui::CollapsingHeader(u8"Search"))
		{
			ImGui::SliderInt("CD_randtime", &Searchcnt, 0, 200);
			ImGui::SliderFloat("Ser_speed", &Seachspeed, 0.0f, 2.0f);
			ImGui::SliderFloat("Ser_time", &Seachtime, 0.0f, 200.0f);
		
		}
		if (ImGui::CollapsingHeader(u8"Chase"))
		{
			ImGui::SliderFloat("chase_dist", &chasedist, 0.0f, 200.0f);
			ImGui::SliderFloat("chase_speed", &chasespeed, 0.0f, 3.0f);
			ImGui::SliderFloat("chase_time", &chasetime, 0.0f, 100.0f);

		}
		if (ImGui::CollapsingHeader(u8"Dash"))
		{
			ImGui::SliderFloat("Dash_speed", &Dashspeed, 0.0f, 10.0f);
			ImGui::SliderFloat("Dash_time", &Dashtime, 0.0f, 100.0f);

		}
		if (ImGui::CollapsingHeader(u8"Separation"))
		{
			ImGui::SliderFloat("Sep_dist", &Sepdist, 0.0f, 50.0f);
			ImGui::SliderFloat("Sep_speed", &Sepspeed, 0.0f, 5.0f);

		}
		if (ImGui::CollapsingHeader(u8"togather"))
		{
			ImGui::SliderFloat("Sep_speed", &Sepspeed, 0.0f, 5.0f);
			ImGui::SliderFloat("tog_speed", &cohspeed, 0.0f, 5.0f);

		}
		if (ImGui::CollapsingHeader(u8"away"))
		{
			ImGui::SliderFloat("away_time", &zombieawaytime, 0.0f, 30.0f);
			ImGui::SliderFloat("away_speed", &zombiawayspeed, 0.0f, 5.0f);

		}
	}
	ImGui::Checkbox("Paramater_Save", &save);
	ImGui::Checkbox("Paramater_Load", &load);

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void BoidsAI::SetNum()
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

int BoidsAI::GetHp()
{
	return hp;
}

float BoidsAI::boid_angle(const Pvector& v)
{
	// 内積の定義から
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

float BoidsAI::getDesSep() const
{
	return desSep;
}

float BoidsAI::getDesAli() const
{
	return desAli;
}

float BoidsAI::getDesCoh() const
{
	return desCoh;
}

float BoidsAI::getSepW() const
{
	return SepW;
}

float BoidsAI::getAliW() const
{
	return AliW;
}

float BoidsAI::getCohW() const
{
	return CohW;
}

void BoidsAI::setDesSep(float x)
{
	desSep += x;
}

void BoidsAI::setDesAli(float x)
{
	desAli += x;
}

void BoidsAI::setDesCoh(float x)
{
	desCoh += x;
}

void BoidsAI::setSepW(float x)
{
	SepW += x;
}

void BoidsAI::setAliW(float x)
{
	AliW += x;
}

void BoidsAI::setCohW(float x)
{
	CohW += x;
}
