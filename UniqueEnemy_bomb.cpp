#include "UniqueEnemy_Bomb.h"
#include"ground.h"
#include"CDirectInput.h"
#include"BulletMgr.h"
#include"player.h"
#include"billboardMgr.h"

const int INTERPOLATENUM = 4;			// 補間数

bool UniqueEnemy_Bomb::Init()
{

	//////um_instancemodel = pmodel;
	// 行列初期化
	DX11MtxIdentity(m_mtx);

	//XYZの軸を取り出し保管
	SetQutenion();

	float posx = rand() % 800 - 400.0f;
	float posz = rand() % 800 - 400.0f;
	if ((posx > -100)&&(posx < 100))
	{
		float s = rand() % 2 - 1;
		posx += 100*s;
	}	
	if ((posz > -100)&&(posz < 100))
	{
		float s = rand() % 2 - 1;
		posx += 100*s;
	}
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

	
	hp = 25;

	champion = false;
	desSep = 5.0f;
	desAli = 15.0f;
	desCoh = 10.0f;
	SepW = 1.5f;
	AliW = 1.0f;
	CohW = 1.0f;

	uniquebombhp.Init();

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

int leng = 500;

void UniqueEnemy_Bomb::Update(std::vector<Player*>& pvec, std::vector<ZombieBullet*>& zbvec)
{
	if (ubstatus == UBSTATUS::LIVE)
	{

		for (int i = 0; i < zbvec.size(); i++)
		{
			if (zbvec.at(i)->m_sts == ZOMBIEBSTS::LIVE)
			{
				float disx = this->GetMtx()._41 - zbvec.at(i)->GetMtx()._41;
				float disy = this->GetMtx()._43 - zbvec.at(i)->GetMtx()._43;
				float dist = disx * disx + disy * disy;
				if (leng > dist)
				{
					this->hp  -= 1;
					
					zbvec.at(i)->m_sts = ZOMBIEBSTS::DEAD;

					BillBoardMgr::GetInstance()->ExplsionCreate(XMFLOAT3(this->GetMtx()._41, this->GetMtx()._42, this->GetMtx()._43));
				}
			}
		}
		for (int i = 0; i < pvec.size(); i++)
		{
			if (pvec.at(i)->m_sts == Player::STATUS::LIVE)
			{
				float disx = this->GetMtx()._41 - pvec.at(i)->GetMtx()._41;
				float disy = this->GetMtx()._43 - pvec.at(i)->GetMtx()._43;
				float dist = disx * disx + disy * disy;
				if (leng > dist)
				{
					pvec.at(i)->hp -= 1;

					//zbvec.at(i)->m_sts = ZOMBIEBSTS::DEAD;

					//BillBoardMgr::GetInstance()->ExplsionCreate(XMFLOAT3(this->GetMtx()._41, this->GetMtx()._42, this->GetMtx()._43));
				}
			}
		}
	}

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
			boid_accel -= 0.0f;
		}
		if (boid_accel < 0)
		{
			boid_accel = 0;
		}
		 escapecnt--;
		//if (escapecnt < -10) escapecnt = -10;
	
		sepcnt -= 1;
		if (sepcnt < 0)sepcnt = 0;
	
	
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

		scale._11 = 8.0f;
		scale._22 = 8.0f;
		scale._33 = 8.0f;

		angle.y = 0.0f;

		angle.y = -GetAtan(velocity.x, velocity.y);
		angle.y -= 90.0f;
		
		velocity.mulScalar(0);

		//float ang = angle.y;
		SetAngle();
		

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
	else if (hp <= 0)
	{
		m_mtx._41 = -10000.0f;
		m_mtx._42 = -10000.0f;
		m_mtx._43 = -10000.0f;

	}
}

void UniqueEnemy_Bomb::UEnemy_run(std::vector<Player*>& zonbie_vector)
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


void UniqueEnemy_Bomb::UEnemy_flock(std::vector<Player*>& zonbie_vector)
{
	ueser = { 0,0 };
	uesep = { 0,0 };
	ueatt = { 0,0 };

	if (unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)
	{
		
	
		if (bserflg)
		{
			if (boid_accel < 0.3f)
			{
				ueser = UEnemy_Search();
			}
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
	//applyForce(uesep);
	applyForce(ueatt);

}

void UniqueEnemy_Bomb::UEnemy_update()
{
	acceleration.normalize();

	acceleration.mulScalar(boid_accel);
	//  更新速度
	velocity.addVector(acceleration);

	location.addVector(velocity);

	acceleration.mulScalar(0);
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
		sepcnt = 300;
	}
	return uesteer;
}

Pvector UniqueEnemy_Bomb::UEnemy_Attack(std::vector<Player*>& zonbie_vector)
{
	// ボイド間分離視野距離
	float desiredseparation = 100;//視野　プレイヤーからの距離
	uesteer = { 0,0 };
	float before_distanse = 100.0f;//一番近い距離保存用

	
	if (unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)
	{
		for (auto& it : zonbie_vector)
		{
			if (it->bstatus == Player::BSTATUS::LIVE)
			{
				float d = location.distance(it->location);
				if (d < before_distanse) {
					before_distanse = d;
					nearplayer = it->location;
					zpos = XMFLOAT3(it->m_mtx._41, it->m_mtx._42, it->m_mtx._43);

				}
			}
		}

		if (before_distanse < desiredseparation)
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

Pvector UniqueEnemy_Bomb::UEnemy_Escape(std::vector<Player>& zonbie_vector)
{
	return Pvector();
}

void UniqueEnemy_Bomb::UEnemy_Dmg(std::vector<Player*>& zonbie_vector)
{
	float desiredseparation = 10;//視野　プレイヤーからの距離

	for (auto& it : zonbie_vector)
	{
		
			float d = location.distance(it->location);
			// 現在のボイドが捕食者ではなく、私たちが見ているボイドが
			// 捕食者、次に大きな分離 Pvector を作成します
			if ((d > 0) && (d < desiredseparation) && it->predator == true) {

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

void UniqueEnemy_Bomb::UpdateHP()
{
	float maxhpp = maxhp;
	float hpp = hp;
	float hppercent= hpp / maxhpp;

	uniquebombhp.Update(XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43),hppercent);
	
	uniquebombhp.Draw();
}
