#include "UniqueEnemy_Bomb.h"
#include"ground.h"
#include"CDirectInput.h"
#include"BulletMgr.h"
#include"player.h"
const int INTERPOLATENUM = 4;			// 補間数

bool UniqueEnemy_Bomb::Init()
{

	//////um_instancemodel = pmodel;
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	//XYZの軸を取り出し保管
	SetQutenion();

	float posx = rand() % 400 - 200.0f;
	float posz = rand() % 400 - 200.0f;
	m_mtx._41 = posx;
	m_mtx._43 = posz;
	angle.x = 0.0f;
	angle.z = 0.0f;
	angle.y = 0.0f;


	float xx = rand() % 5 - 2.0f;
	float yy = rand() % 5 - 2.0f;

	acceleration = Pvector(0, 0);
	velocity = Pvector(xx, yy);//加速度
	location = Pvector(posx, posz);//ポジション
	maxSpeed = 1.8f;
	maxForce = 0.7f;

	hp = 50;

	champion = false;
	desSep = 5.0f;
	desAli = 15.0f;
	desCoh = 10.0f;
	SepW = 1.5f;
	AliW = 1.0f;
	CohW = 1.0f;

	return true;
}

void UniqueEnemy_Bomb::Draw(std::vector<Player>& zonbie_vector)
{
	
	manime.animecnt = 0;
	unique_enemy_anime = UNIQUE_ENEMY_ANIME::IDLE;
	
	//	m_model->Update(animecnt, m_mtx, animereset);
		// モデル描画
	um_model->Draw(m_mtx);
}
void UniqueEnemy_Bomb::Update()
{
	if (hp > 0)
	{
		boid_borders();
		Ground::GetInstance()->GetPlayerHeight(*this);

		//Z軸を取り出す
		axisZ.x = m_mtx._31;
		axisZ.y = m_mtx._32;
		axisZ.z = m_mtx._33;
		axisZ.w = 0.0f;


		if (zonbienearflg)
		{
			if (bombcnt == 250)
			{
				BulletMgr::GetInstance()->Remake(m_mtx, zpos);
			}
			if (bombcnt > 250)
			{
				bombcnt = 0;
			}
			bombcnt++;

		}
		else
		{
			bombcnt = 0;
		}



		if ((unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK) && (boid_accel == 0))
		{
			unique_enemy_anime = UNIQUE_ENEMY_ANIME::IDLE;
			manime.animecnt = 0;
		}
		if ((unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK) && (boid_accel > 0))
		{
			unique_enemy_anime = UNIQUE_ENEMY_ANIME::MOVE;
			manime.animecnt = 1;
		}

		if (unique_enemy_anime == UNIQUE_ENEMY_ANIME::ATTACK)
		{
			boid_accel -= 0.5f;
			manime.animecnt = 2;
		}




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


		if (b_animecnt != manime.animecnt)
		{
			animereset = true;
			manime.m_Frame = 0;
		}
		else
		{
			animereset = false;
		}

		b_animecnt = manime.animecnt;//前回のアニメ番号保存


		if (manime.m_cnt % INTERPOLATENUM == 0) {
			manime.m_preFrame = manime.m_Frame;
			manime.m_Frame++;
			manime.m_factor = 0;
		}

		manime.m_factor = 1.0f / (float)(manime.m_cnt % INTERPOLATENUM + 1);

		manime.m_cnt++;
	}
	else if (hp <= 0)
	{
		m_mtx._41 = -10000.0f;
		m_mtx._42 = -10000.0f;
		m_mtx._43 = -10000.0f;

	}
}

void UniqueEnemy_Bomb::UEnemy_run(std::vector<Player>& zonbie_vector)
{
	if (hp > 0)
	{
		UEnemy_flock(zonbie_vector);
		UEnemy_update();
		if (dmgflg)
		{
			UEnemy_Dmg(zonbie_vector);
		}
	}
}


void UniqueEnemy_Bomb::UEnemy_flock(std::vector<Player>& zonbie_vector)
{
	ueser = { 0,0 };
	uesep = { 0,0 };
	ueatt = { 0,0 };

	if (unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)
	{
		
	
		if (bserflg)
		{
			ueser = UEnemy_Search();
		}
		if (bbombflg)
		{
			ueatt = UEnemy_Attack(zonbie_vector);
		}
	}



	ueser.mulScalar(CohW);
	//uesep.mulScalar(SepW);
	ueatt.mulScalar(1.5f);



	applyForce(ueser);
	applyForce(uesep);
	applyForce(ueatt);

}

void UniqueEnemy_Bomb::UEnemy_update()
{
	acceleration.normalize();

	acceleration.mulScalar(boid_accel);
	//  更新速度
	velocity.addVector(acceleration);

	location.addVector(velocity);

	velocity.mulScalar(0);
}




Pvector UniqueEnemy_Bomb::UEnemy_Search()
{
	int cnt = rand() % 60;
	if (cnt == 0)
	{
		float x = rand() % 100 - 50;
		float y = rand() % 100 - 50;

		uedesired = { x,y };
		uedesired.normalize();
		uedesired.mulScalar(-1);
		uedesired.divScalar(15);

		acceleration = uedesired;
		angley.x = acceleration.x;
		angley.y = acceleration.y;
		this->boid_accel = 0.5f;
		awaycnt = 80;
	}
	return uedesired;
}

Pvector UniqueEnemy_Bomb::UEnemy_Separation(std::vector<Player>& zonbie_vector)
{
	// ボイド間分離視野距離
	float desiredseparation = 10;//視野　プレイヤーからの距離
	uesteer = { 0,0 };
	int count = 0;
	//システム内のすべてのボイドについて、近すぎるかどうかを確認します

	for (auto& it : zonbie_vector)
	{
		float d = location.distance(it.location);
			// 現在のボイドが捕食者ではなく、私たちが見ているボイドが
			// 捕食者、次に大きな分離 Pvector を作成します
			if ((d > 0) && (d < desiredseparation) && it.predator == true) {
				uedesired = { 0,0 };
				uedesired = uedesired.subTwoVector(location, it.location);
				uedesired.mulScalar(900);
				uesteer.addVector(uedesired);
				count++;
			}
		}
	

	// 位置の平均差を加速度に加算
	if (count > 0)
		uesteer.divScalar((float)count);
	if (uesteer.magnitude2x() > 0) {
		awaycnt = 0;
		// Steering = Desired - Velocity
		uesteer.normalize();
		boid_accel = 2.5f;
		uesteer.limit(maxForce);
	}
	return uesteer;
}

Pvector UniqueEnemy_Bomb::UEnemy_Attack(std::vector<Player>& zonbie_vector)
{
	// ボイド間分離視野距離
	float desiredseparation = 100;//視野　プレイヤーからの距離
	uesteer = { 0,0 };
	float before_distanse = 100.0f;//一番近い距離保存用

	
	if (unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)
	{
		for (auto& it : zonbie_vector)
		{
			float d = location.distance(it.location);
			if (d < before_distanse) {
				before_distanse = d;
				nearplayer = it.location;
				zpos = XMFLOAT3(it.m_mtx._41,it.m_mtx._42,it.m_mtx._43);
				
			}
		}

		if ((before_distanse > 0) && (before_distanse < 15))
		{
			uedesired = { 0,0 };
			uedesired = uedesired.subTwoVector(location, nearplayer);
			uedesired.normalize();
			uedesired.divScalar(900);

			acceleration = uedesired;
			angley.x = acceleration.x;
			angley.y = acceleration.y;
			this->boid_accel = 2.3f;

			//unique_enemy_anime = UNIQUE_ENEMY_ANIME::ATTACK;

		}

		if ((before_distanse > 20) && (before_distanse < desiredseparation))
		{
			uedesired = { 0,0 };
			uedesired = uedesired.subTwoVector(location, nearplayer);
			uedesired.normalize();
			uedesired.mulScalar(-1);
			uedesired.divScalar(before_distanse);

			acceleration = uedesired;
			angley.x = acceleration.x;
			angley.y = acceleration.y;
			this->boid_accel = 0.0f;
			zonbienearflg = true;
		}
		else
		{
			zonbienearflg = false;
		}
	}
	
	return uedesired;
}

void UniqueEnemy_Bomb::UEnemy_Dmg(std::vector<Player>& zonbie_vector)
{
	float desiredseparation = 10;//視野　プレイヤーからの距離

	for (auto& it : zonbie_vector)
	{
		
			float d = location.distance(it.location);
			// 現在のボイドが捕食者ではなく、私たちが見ているボイドが
			// 捕食者、次に大きな分離 Pvector を作成します
			if ((d > 0) && (d < desiredseparation) && it.predator == true) {

				this->hp -= 1;
			}
		}
	
}

int UniqueEnemy_Bomb::UEnemy_GetAnime()
{
	return manime.animecnt;
}


void  UniqueEnemy_Bomb::UEDelete(float arraynum, std::vector<UniqueEnemy_Bomb>& Player_Vector1)
{
	Player_Vector1.erase(Player_Vector1.begin() + arraynum);
}