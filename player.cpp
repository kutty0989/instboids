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

XAudio audio;						//���y�Ȃ炷


static float m_rig;//�v���C���[�̌��݂̊p�x�ۑ��p
static float ay;
static float bay;

//float Player::accel = 0.0f;
#define debuglog(a) std::cout<<a<<std::endl;

float scaling = Ground::GetInstance()->scaling;


const int window_height = (CHeight_Map::GetInstance()->iPixSize - 60) * scaling;//�}�b�v�̑傫���@�c
const int window_width = (CHeight_Map::GetInstance()->iPixSize - 60) * scaling;//�}�b�v�̑傫���@��


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


 //�l�Ԃ̑���
  float Player:: hyumanmaxspeed;//1.5
  float Player:: hyumanrandspeed;//5

 //hyumanali
  float Player:: alidist;//40


 //hyumnsep
  float Player:: sepdist;//10
  float Player:: sepzonbiedist;//30
  float Player:: sepspeed;//2.0
  float Player:: septime;//30


  float Player:: zonbiehp;//�Q
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

 //�W�����x
  float Player:: cohspeed;//�P�D�O

  //zombieaway
  float Player::zombiawayspeed;//1.5
  float Player::zombieawaytime;//�P�O

 //�]���r�Ƃ̃_���[�W����
  float Player:: zombirange;//15
  float Player:: damage;//�P�D�O

   bool Player::save = false;
   bool Player::load = false;

//go ���̍��W�l
//to�@�s��̍��W�l
//ratio�@���݂̐i�s�����@0.0f�`1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}




bool Player::Init() {

	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	//XYZ�̎������o���ۊ�
	SetQutenion();

	float posx = rand() % 400 - 200;//�����l
	float posz = rand() % 400 - 200;//�����l
	SetPos(XMFLOAT3(posx, 0.0f, posz));//�����l
	
	angle.x = 0.0f;
	angle.z = 0.0f;
	angle.y = 0.0f;

	return true;
}


bool Player::CharengerInit()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	//XYZ�̎������o���ۊ�
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
	velocity = Pvector(xx, yy);//�����x
	location = Pvector(x, y);//�|�W�V����
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

	location = Pvector(x / 10, y / 10);//�|�W�V����
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
	//velocity = Pvector(PlayerMgr::GetInstance()->StickXRig, PlayerMgr::GetInstance()->StickYRig);//�����x
	////velocity = Pvector(0, 0);//�����x
	//location = Pvector(x, y);//�|�W�V����
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

	// ���f���`��
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

		//�e�s���������
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);

		scale._11 = 2.0f;
		scale._22 = 2.0f;
		scale._33 = 2.0f;

	
		Ground::GetInstance()->GetPlayerHeight(*this);
		//����̊p�x��ۑ�
		if (slopeflg)
		{
			boid_accel = Ground::GetInstance()->AccelBoid(*this);
		}
		velocity.mulScalar(boid_accel);
		location.addVector(velocity);


		angle.y = -GetAtan(velocity.x, velocity.y);
		//�p�x����
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


		//Z�������o��
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

			//  �X�V���x
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
//�g���ĂȂ�
void Player::FollowUpdate()
{

	Ground::GetInstance()->GetPlayerHeight(*this);
	//Z�������o��
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
	//1�̔z��ւQ�̔z��̗v�f�ԍ����ړ�
	player_vector1.push_back(std::move(player_vector2[arraynum]));

	//�����ꏊ�̔z�������
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

			//hp���Y����
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

Pvector desired;//�v�Z�p�̕ϐ�
Pvector des;//�v�Z�p�̕ϐ�

// maxSpeed �𐧌����A�K�v�ȑ��Ǘ͂������A
//�x�N�g���𐳋K�����܂�
Pvector Player::boid_seek(const Pvector& v)
{
	desired = { 0,0 };
	desired = desired.subTwoVector(v, location);  //�ʒu����^�[�Q�b�g���w���x�N�g��
	// �K�v�Ȑ��K���ƍő呬�x�ւ̃X�P�[�����O
	desired.normalize();
	desired.mulScalar(hyumanmaxspeed);

	//�X�e�A�����O = �]�܂����}�C�i�X���x
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
			//����p�ɂ���boid�����łR�@��
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


//�{�C�h�̌Q��ɎO�@����K�p����
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

	//�����̗͂�C�ӂɏd�ݕt������
	//cen.mulScalar(CohW);
	sep.mulScalar(1.5f);
	ali.mulScalar(1.0f); // ���܂��܂ȓ����̏d�݂�ύX����K�v������ꍇ������܂�
	avo.mulScalar(1.0f); // ���܂��܂ȓ����̏d�݂�ύX����K�v������ꍇ������܂�
	down.mulScalar(1.0f);
	
	//  �̓x�N�g���������x�ɉ�����

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

	//���U���Ă��鎞�ȊO�͍s��
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
	
	//�����̗͂�C�ӂɏd�ݕt������
	//cen.mulScalar(CohW);
	sep.mulScalar(SepW);

	coh.mulScalar(CohW);
	awa.mulScalar(1.0f);
	dmg.mulScalar(3.0f);
	ali.mulScalar(AliW); // ���܂��܂ȓ����̏d�݂�ύX����K�v������ꍇ������܂�
	//
	//  �̓x�N�g���������x�ɉ�����
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


// ���x�A�ʒu��ύX���A�����x�����̒l�Ń��Z�b�g���܂�
// �O�@���ŗ^������B
void Player::boid_update()
{
	if (follow == Follow::HYUMAN)
	{
		//�X���[�_�E�����}���ɂ��Ȃ����߂�
	//	acceleration.mulScalar(0.35f);
		//  �X�V���x
		velocity.addVector(acceleration);
		velocity.normalize();
		//  �������x
		velocity.mulScalar(hyumanmaxspeed);
		//velocity.limit(hyumanmaxspeed);
	

		// �e�T�C�N���ŉ����x�� 0 �Ƀ��Z�b�g����
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

			//�X���[�_�E�����}���ɂ��Ȃ����߂�
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

// ����
// �{�C�h���m���߂Â������Ȃ��悤�ɂ���
Pvector Player::boid_Separation(std::vector<Player*> player_vector, std::vector<Player*> zonbie_vector)
{
	// �{�C�h�ԕ������싗��
	//float desiredseparation = 10;//����@�v���C���[����̋���
	steer = { 0,0 };
	int count = 0;
	//�V�X�e�����̂��ׂẴ{�C�h�ɂ��āA�߂����邩�ǂ������m�F���܂�

	//for (int i = 0; i < sizeof(player_vector)/sizeof(player_vector[0]); i++)//0��
	if (boid_accel < 2.0f)
	{
		for (auto& it : player_vector)
		{

			// ���݂�boid���猩�Ă���boid�܂ł̋������v�Z����
			if (it->follow == Follow::HYUMAN)
			{
				float d = location.distance(it->location);
				// ���ꂪ���Ԃ̃{�C�h�ł���A�߂�����ꍇ�́A����Ă�������
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
		//// ���݂̃{�C�h���ߐH�҂ł���A�����������Ă���{�C�h���ߐH�҂ł���ꍇ
		//// �ߐH�҂͋߂Â��āA���̌�킸���ɕ���
		//if ((d > 0) && (d < desiredseparation) && predator == true
		//	&& it->predator == true) {
		//	desired = { 0,0 };
		//	desired = desired.subTwoVector(location, it->location);
		//	desired.normalize();
		//	desired.divScalar(d);
		//	steer.addVector(desired);
		//	count++;
		//}
		// ���݂̃{�C�h���ߐH�҂ł͂Ȃ��A�����������Ă���{�C�h��
		// �ߐH�ҁA���ɑ傫�ȕ��� Pvector ���쐬���܂�
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
	

	// �ʒu�̕��ύ��������x�ɉ��Z
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
		XMFLOAT3 diff = XMFLOAT3(it->GetPos().x-this->GetPos().x , 0.0f, it->GetPos().z-this->GetPos().z);//��Q���Ƃ̋���

		//�����o��
		float distance;
		DX11Vec3Dot(distance,diff, diff);
	
		sqrt(distance);
		float aboidrange = 450.0f;
		float escaperange = 50.0f;

		//������͈͓���
		if (distance > aboidrange)  // ��Q���������͈͓��ɂ��邩�H
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
		if (directionDot < 0) // �O�����ɏ�Q�����Ȃ���
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

		if (forward2ObstacleDistance> escaperange) // ��Q�����瓦����͈͂Ƒ��x�x�N�g���̒������d�Ȃ��Ă��Ȃ���
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
	// �{�C�h�ԕ������싗��
//	this->desSep;//����@�v���C���[����̋���

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
	//�V�X�e�����̂��ׂẴ{�C�h�ɂ��āA�߂����邩�ǂ������m�F���܂�
	for (auto& it : player_vector)
	{

		// ���݂�boid���猩�Ă���boid�܂ł̋������v�Z����
		if (it->follow != Follow::HYUMAN)
		{
			float d = location.distance(it->location);
			if ((d > 0) && (d < Sepdist)) {

				//desiredseparation /= count;
					// ���ꂪ���Ԃ̃{�C�h�ł���A�߂�����ꍇ�́A����Ă�������
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


	// �ʒu�̕��ύ��������x�ɉ��Z
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

// ����
//������̃{�C�h�̕��ϑ��x���v�Z���A
// ��v����悤�Ɍ��݂̃{�C�h�̑��x�𑀍삵�܂�
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
	// ���񂷂�̂ɏ\���߂��{�C�h������ꍇ...
	if (count > 0) {
		desired.divScalar((float)count);// ���v���߂��{�C�h�̐��Ŋ���܂� (���x�̕���)
		desired.normalize();            // ���v��P�ʃx�N�g���ɕϊ����A
		desired.mulScalar(hyumanmaxspeed);    //maxSpeed ���|����
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
	angle.y = 0.0f;//�p�x���Z�b�g

//	velocity.addVector(acceleration);
	velocity.normalize();

	//�x�N�g���ۑ�
	angley.x = velocity.x;
	angley.y = velocity.y;

	//boids�v�Z����o�����x�����Ɍ�����ύX
	angle.y = GetAtan(velocity.x, velocity.y);


	/*	if (angle.y > 360)angle.y -= 360.0f;
		else if (angle.y < 0)angle.y += 360.f;
		velocity.x = -cosf(((angle.y) * 3.14159265358979323846 / 180.0f));
		velocity.y = -sinf(((angle.y) * 3.14159265358979323846 / 180.0f));*/



		//����]�p�̊p�x
	left_angle = angle.y + 45.f;
	if (left_angle > 360)left_angle -= 360.0f;
	else if (left_angle < 0)left_angle += 360.f;
	//�E��]�p�̊p�x
	right_angle = angle.y - 45.f;
	if (right_angle > 360)right_angle -= 360.0f;
	else if (right_angle < 0)right_angle += 360.f;
	//180�x��]�p�̊p�x
	opposite_angle = angle.y + 180.f;
	if (opposite_angle > 360)opposite_angle -= 360.0f;
	else if (opposite_angle < 0)opposite_angle += 360.f;

	//���ꂼ��̊p�x�̃x�N�g�����Z�o
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
{// �{�C�h�ԕ������싗��
	//float desiredseparation = chasedist;//����@�v���C���[����̋���
	steer = { 0.0f,0.0f };
	int count = 0;
	
	float before_distanse = 50.0f;//��ԋ߂������ۑ��p
	
	Pvector nearplayer;//��ԋ߂����݂�ۑ�����ϐ�
	
	if (awayflg == false) {

		// ���݂̃{�C�h���ߐH�҂ł���A�����������Ă���{�C�h���ߐH�҂ł���ꍇ
		// �ߐH�҂͋߂Â��āA���̌�킸���ɕ���
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

// ����
// �߂��̃{�C�h�̕��ψʒu�������A
// ���̕����Ɉړ����鑀�Ǘ́B
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
/// ���U���Ă���
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
			bombdist = 100;//����@�v���C���[����̋���
		
		
			
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



//�W��
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

	XMFLOAT4X4 g_view = CCamera::GetInstance()->GetViewMatrix();//�r���[�ϊ��擾
	XMFLOAT4X4 g_projection = CCamera::GetInstance()->GetProjectionMatrix();//�v���W�F�N�V�����擾

	//�v�Z�ׂ̈ɕϊ�
	XMMATRIX view = XMLoadFloat4x4(&g_view);
	XMMATRIX proj = XMLoadFloat4x4(&g_projection);

	//t�r���[�|�[�g�ݒ�
	float w = (float)Application::CLIENT_WIDTH / 2.0f;
	float h = (float)Application::CLIENT_HEIGHT / 2.0f;
	XMMATRIX viewport = {
	w, 0, 0, 0,
	0, -h, 0, 0,
	0, 0, 1, 0,
	w, h, 0, 1
	};

	//�ύX�������L�����̍��W���擾���ϊ�
	XMFLOAT3 temp = World_Pos;
	XMVECTOR tmp = XMLoadFloat3(&temp);


	// �r���[�s��ƃv���W�F�N�V�����s����|����
	tmp = XMVector3Transform(tmp, view);
	tmp = XMVector3Transform(tmp, proj);

	//float�l��
	DirectX::XMStoreFloat3(&temp, tmp);

	// z�Ŋ�����-1~1�͈̔͂Ɏ��߂�
	// �X�N���[���ϊ�
	const XMVECTOR view_vec = XMVectorSet(temp.x / temp.z, temp.y / temp.z, 1.0f, 1.0f);
	tmp = XMVector3Transform(view_vec, viewport);

	//float�l�ɂ��Ė߂�l
	DirectX::XMStoreFloat3(&temp, tmp);
	return temp;
}


void Player::SetAngle()
{
	XMFLOAT4 qtx = {};//�N�H�[�^�j�I��
	XMFLOAT4 qty = {};//�N�H�[�^�j�I��
	XMFLOAT4 qtz = {};//�N�H�[�^�j�I��
	

	//DX11GetQtfromMatrix(m_mtx, qt);

	//�w�莲��]�̃N�H�[�^�j�I���𐶐�
	DX11QtRotationAxis(qtx, axisX, angle.x);
	DX11QtRotationAxis(qty, axisY, angle.y);
	DX11QtRotationAxis(qtz, axisZ, angle.z);


	//�N�H�[�^�j�I��������
	XMFLOAT4 tempqt1;
	DX11QtMul(tempqt1, qtx, qty);

	XMFLOAT4 tempqt2;
	DX11QtMul(tempqt2, qtz, tempqt1);

	//�N�H�[�^�j�I�����m�[�}���C�Y
	DX11QtNormalize(tempqt2, tempqt2);

	SetRotation(tempqt2);

	//�N�H�[�^�j�I������s����쐬
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

	//�l�Ԃ̑���
	 hyumanmaxspeed = 0.5f;//0.5
	 hyumanrandspeed = 5.0f;//5

	//hyumanali
	 alidist = 40.0f;//40

	//hyumnsep
	 sepdist = 10.0f;//10
	 sepzonbiedist = 40.0f;//30
	 sepspeed = 2.5f;//2.5
	 septime = 30.0f;//30


	 zonbiehp = 5.0f;//�Q
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
	 zombieawaytime = 15.0f;//�P�O

	//�W�����x
	 cohspeed = 1.0f;//�P�D�O

	//�]���r�Ƃ̃_���[�W����
	 zombirange = 15.0f;//15
	 damage = 1.0f;//�P�D�O
}

int Player::GetHp()
{
	return hp;
}

float Player::boid_angle(const Pvector& v)
{
	// ���ς̒�`����
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
