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
XAudio audio;						//���y�Ȃ炷


static float m_rig;//�v���C���[�̌��݂̊p�x�ۑ��p

/// <summary>
/// AI�̃p�����[�^�[��static�ϐ�
/// </summary>
/////////////////////////////////////////////////////////

//�n�`�̃X�P�[��	
float scaling = Ground::GetInstance()->scaling;
	
/// <summary>
/// �������Ԃ�AI�̓K�����邩�ǂ����̃��[��
/// </summary>

//����
bool BoidsAI::hsepflg = false;
//����
bool BoidsAI::haliflg = false;
//�X���[�v
bool BoidsAI::slopeflg = false;
//�|�P�b�g
bool BoidsAI::pocketflg = false;
//�ō����x
float BoidsAI::hyumanmaxspeed;//1.5

float BoidsAI::hyumanrandspeed;//5
//����͈̔�
float BoidsAI::alidist;//40
//�����͈̔�
float BoidsAI::sepdist;//10
//����͈�
float BoidsAI::sepzonbiedist;//30
//�������x
float BoidsAI::sepspeed;//2.0
//�����鎞��
float BoidsAI::septime;//30

/// <summary>
/// ����v���C���[�̕ϐ�
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


float BoidsAI::zonbiehp;//�Q
float BoidsAI::zonbiemaxspeed;//8.5
float BoidsAI::zonbiedownspeed;//0.05f
//////////////////////////////////////////////

//���j�[�N�ȓG�̕ϐ�
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
					   
//�W�����x
float BoidsAI::cohspeed;//�P�D�O

//zombieaway
float BoidsAI::zombiawayspeed;//1.5
float BoidsAI::zombieawaytime;//�P�O

//�]���r�Ƃ̃_���[�W����
float BoidsAI::zombirange;//15
float BoidsAI::damage;//�P�D�O

bool BoidsAI::save = false;
bool BoidsAI::load = false;

float length = 200;
///////////////////////////////////////////////////////////




//go ���̍��W�l
//to�@�s��̍��W�l
//ratio�@���݂̐i�s�����@0.0f�`1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

bool BoidsAI::Init() {

	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	//XYZ�̎������o���ۊ�
	SetQutenion();

	float posx = rand() % 400 - 200;//�����l
	float posz = rand() % 400 - 200;//�����l
	SetPos(XMFLOAT3(posx, 0.0f, posz));//�����l
	
	//�p�x�̏���
	angle.x = 0.0f;
	angle.z = 0.0f;
	angle.y = 0.0f;

	return true;
}


bool BoidsAI::CharengerInit()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	//XYZ�̎������o���ۊ�
	SetQutenion();

	//�ꏊ�̏����l
	float posx = rand() % 400;
	float posz = rand() % 400;
	posx -= 200;
	posz -= 200;
	//�ꏊ���O��
	SetPos(XMFLOAT3(0, 0, 0));
	//�p�x�𒲐�
	angle.x = -90.0f;
	angle.z = 0.0f;
	angle.y = -90.0f;
	SetAngle();

	champion = true;

	return true;
}

/// <summary>
/// �������Ԃ�AI�̏�����
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void BoidsAI::boid_Init(float x, float y)
{
	//�����l
	float xx = rand() % 100 - 50.0f;
	float yy = rand() % 100 - 50.0f;
	//�������Ă����Ԃ�
	BSTATUS::LIVE;
	acceleration = Pvector(1, 1);
	velocity = Pvector(xx, yy);//�����x
	location = Pvector(x, y);//�|�W�V����
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
/// ���삷��AI�̏����l
/// </summary>
/// <param name="x">�����ꏊ</param>
/// <param name="y"></param>
/// <param name="nowzombiecnt"></param>
void BoidsAI::zonbie_Init(float x, float y, int nowzombiecnt)
{

	acceleration = Pvector(0, 0);
	bulletcreatecnt = rand() % 10 + 60;
	velocity = { 0,0 };
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
	boid_accel = 0.0f;

	//hpUI�̏�����
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
/// AI�Đ����̊֐�
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
/// �����̍X�V
/// </summary>
void BoidsAI::UpdateHp() {

	//�����Ă�`������
	if (follow == Follow::ZONBIE)
	{
		boidshp.UpdateHp(hp);
		boidshp.Update(XMFLOAT3(this->GetMtx()._41,this->GetMtx()._42,this->GetMtx()._43));
		boidshp.Draw();
	}
}

/// <summary>
/// ���������Ƀ��C��������
/// </summary>
void BoidsAI::HyumanDrawAxis() {
	drawaxis(m_mtx, 5.0f, XMFLOAT3(m_mtx._41, m_mtx._42, m_mtx._43));
}

/// <summary>
/// /���f����`��ƃ��C����xyz�Ɉ���
/// </summary>
void BoidsAI::DrawWithAxis() {
	// ���f���`��
	drawaxis(m_mtx, 200, m_pos);
}

struct FLOAT3
{
	float x, y, z;
};




void BoidsAI::Update(bool input, std::vector<ZombieBullet*> zbvec) {

	//�`�h��|�����Ƃ��̗���
	if (bstatus == BSTATUS::LIVE)
	{
		for (int i = 0; i < zbvec.size(); i++)
		{
			if (zbvec.at(i)->m_sts == ZOMBIEBSTS::LIVE)
			{
				float disx = this->GetMtx()._41 - zbvec.at(i)->GetMtx()._41;
				float disy = this->GetMtx()._43 - zbvec.at(i)->GetMtx()._43;
				float dist = disx * disx + disy * disy;
			//�e�Ɠ���������
				if (length > dist)
				{
					this->hp = 0;
					this->m_sts = BoidsAI::STATUS::DEAD;
					zbvec.at(i)->m_sts = ZOMBIEBSTS::DEAD;
					//�X�R�A�𑫂�
					BoidsAIMgr::GetInstance()->ScoreNum += 10;
					//�������o
					BillBoardMgr::GetInstance()->ExplsionCreate(XMFLOAT3(this->GetMtx()._41, this->GetMtx()._42, this->GetMtx()._43));
				}
			}
		}
	}

	if (bstatus == BSTATUS::LIVE)
	{
		//�}�b�v����o�Ȃ��悤��
		boid_borders();

		///��������
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
		//���ȉ��̒x���ɂ��Ȃ��悤��
		if (boid_accel < 1.0f)
		{
			boid_accel = 1.0f;
		}
		if (boid_accel > 4.0f)boid_accel = 4.0f;
		///////////

		//�e�s���������
		DX11MtxIdentity(scale);
		DX11MtxIdentity(trans);
		DX11MtxIdentity(rot);
		DX11MtxIdentity(world);


		scale._11 = 2.0f;
		scale._22 = 2.0f;
		scale._33 = 2.0f;

	
		Ground::GetInstance()->GetBoidsAIHeight(*this);
		//����̊p�x��ۑ�
		if (slopeflg)
		{
			boid_accel = Ground::GetInstance()->AccelBoid(*this);
		}
		velocity.mulScalar(boid_accel);
		location.addVector(velocity);

		//��������
		angle.y = -GetAtan(velocity.x, velocity.y);
		//�p�x����
		angle.y -= 90.0f;
		SetAngle();
	
		//mtx�v�Z
		DX11MtxMultiply(world, scale, rot);

		m_pos.x = location.x;
		m_pos.z = location.y;

		trans._41 = m_pos.x;
		trans._42 = m_pos.y + 4.0f;
		trans._43 = m_pos.z;

		world._41 = trans._41;
		world._42 = trans._42;
		world._43 = trans._43;

		//�s��K��
		m_mtx = world;

	}
	else
	{
		//����ł��鏈��
		m_mtx._41 = 10000;
	}
}


/// <summary>
/// ���삷��AI�̍X�V
/// </summary>
/// <param name="animenum"></param>
/// <param name="i"></param>
void BoidsAI::BoidsAIAIUpdate(int animenum, int i)
{
	if (bstatus == BSTATUS::LIVE)
	{
		//�m�b�N�o�b�N����
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

		//�n�`����o�Ȃ��悤��
		boid_borders();
		//�s�񏉊���
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
		//�p�x����
		angle.y = -GetKakudo(angley.x, angley.y);
		angle.y -= 90.0f;
		if (angle.y > 360)
		{
			angle.y -= 360.0f;
		}

		//�Đ����֐�
		if (reborn_flg)
		{
			
		}
		else
		{
			//���������߂�֐�
			Ground::GetInstance()->GetBoidsAIHeight(*this);
			
			//���x�𗎂Ƃ����ړ�����
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


			//�����x�m�[�}���C�Y
			acceleration.normalize();

			acceleration.mulScalar(boid_accel);

			//  �X�V���x
			velocity.addVector(acceleration);

			location.addVector(velocity);


			m_pos.x = location.x;
			m_pos.z = location.y;

		}


		//�ꏊ����
		trans._41 = m_pos.x;
		trans._42 = m_pos.y + 4.0f;
		trans._43 = m_pos.z;

		scale._11 = 5.2f;
		scale._22 = 5.2f;
		scale._33 = 5.2f;


		//�p�x����
		float ang = angle.y;
		SetAngle();
		angle.y -= b_angle;
		b_angle = ang;

		DX11MtxMultiply(world, scale, rot);

		world._41 = trans._41;
		world._42 = trans._42;
		world._43 = trans._43;

		m_mtx = world;

		//�o���b�g��ł���
		if (shootflg == true)
		{
			bulletcnt++;
			if (bulletcnt == 30)
			{
				//�o���b�g����
				BoidsAIMgr::GetInstance()->ZombieBulletRemake(this->GetMtx(), XMFLOAT3(this->GetMtx()._41, this->GetMtx()._42, this->GetMtx()._43));
				bulletcnt = 0;
			}
		}
	}
	else
	{
	//���񂾂Ƃ��̏���
	m_mtx._41 = 10000;
	}

}

/// <summary>
/// ���C���L�����̍X�V�@
/// </summary>
void BoidsAI::FollowUpdate()
{

	Ground::GetInstance()->GetBoidsAIHeight(*this);
	//Z�������o��
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


//�����x��ǉ�
void BoidsAI::applyForce(const Pvector& force)
{
	acceleration.addVector(force);
}

/// <summary>
/// ������AI�̔z�񂩂�ړ��Ə���
/// </summary>
/// <param name="arraynum"></param>
/// <param name="BoidsAI_vector1"></param>
/// <param name="BoidsAI_vector2"></param>
void BoidsAI::Move_And_Delete(float arraynum, std::vector<BoidsAI*> BoidsAI_vector1, std::vector<BoidsAI*> BoidsAI_vector2)
{
	//1�̔z��ւQ�̔z��̗v�f�ԍ����ړ�
	BoidsAI_vector1.push_back(std::move(BoidsAI_vector2[arraynum]));

	//�����ꏊ�̔z�������
	BoidsAI_vector2.erase(BoidsAI_vector2.begin() + arraynum);

}

void BoidsAI::Delete(float arraynum, std::vector<BoidsAI*> BoidsAI_Vector1)
{
	BoidsAI_Vector1.erase(BoidsAI_Vector1.begin() + arraynum);
}

//�U���֐�
void BoidsAI::boids_attack(std::vector<BoidsAI*>& BoidsAI_vector, BoidsAI& zonbie, std::vector<UniqueEnemy_Bomb*>& unique_enemy_vector)
{
	if (changeflg)
	{
		
	}
}

Pvector desired;//�v�Z�p�̕ϐ�
Pvector des;//�v�Z�p�̕ϐ�

// maxSpeed �𐧌����A�K�v�ȑ��Ǘ͂������A
//�x�N�g���𐳋K�����܂�
Pvector BoidsAI::boid_seek(const Pvector& v)
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

/// <summary>
/// ���E�͈̔͂�O��90�x�����ɂ���
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
			//����p�ɂ���boid�����łR�@��
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
/// ���삷��AI�̑S�X�V
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


//�{�C�h�̌Q��ɎO�@����K�p����
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

	//�����̗͂�C�ӂɏd�ݕt������
	sep.mulScalar(1.5f);
	ali.mulScalar(1.0f); // ���܂��܂ȓ����̏d�݂�ύX����K�v������ꍇ������܂�
	avo.mulScalar(1.0f); // ���܂��܂ȓ����̏d�݂�ύX����K�v������ꍇ������܂�
	down.mulScalar(1.0f);

	//  �̓x�N�g���������x�ɉ�����
	applyForce(sep);
	applyForce(avo);
	applyForce(ali);
	applyForce(down);

}

void BoidsAI::zonbie_flock(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> human_vector, Pvector mousevec, std::vector<UniqueEnemy_Bomb*>& uniquebomb)
{
	//���[���̃x�N�g���̏�����
	sep = { 0,0 };
	ali = { 0,0 };
	coh = { 0,0 };
	awa = { 0,0 };
	dmg = { 0,0 };

	//���U����
	if (BoidsAIMgr::GetInstance()->scatterflg)
	{
		if (zscaflg)
		{
			awaycnt = 0;
			coh = Zombie_Scatter();
		}
	}

	//���U���Ă��鎞�ƃm�b�N�o�b�N�ȊO�͍s��
	if ((!zombie_scatterflg) && (!knockbackflg))
	{
		if ((boid_accel < 0.5f) || (BoidsAIMgr::GetInstance()->gatherflg))
		{
			if (zsepflg)
			{
				sep = boid_inSeparation(BoidsAI_vector);
			}
		}
		//�W������
		if (BoidsAIMgr::GetInstance()->gatherflg)
		{
			if (zcohflg)
			{
				awaycnt = 0;
				coh = boid_Gather(BoidsAI_vector);
			}
		}
		//�T������
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
		//�A�E�F�C����
		if (!BoidsAIMgr::GetInstance()->gatherflg) {
			if (zawaflg)
			{
				if (boid_accel < 0.4f)
				{
					awa = boid_zonbieAway(human_vector);
				}
			}
		}
		//�_�b�V������
		if (zdashflg)
		{
			ali = boid_zonbieAlignment(mousevec);
		}
		if (dmgflg)
		{
			dmg = zonbie_damage(uniquebomb);
		}
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
void BoidsAI::boid_update()
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

		// �e�T�C�N���ŉ����x�� 0 �Ƀ��Z�b�g����
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
/// �}�b�v�̊O�ɏo�Ȃ��悤�ɂ��鏈��
/// </summary>
void BoidsAI::boid_borders()
{

	if (location.x < -BoidsAIMgr::GetInstance()->window_width * 0.5f)	location.x += BoidsAIMgr::GetInstance()->window_width;
	if (location.y < -BoidsAIMgr::GetInstance()->window_width * 0.5f)	location.y += BoidsAIMgr::GetInstance()->window_height;
	if (location.x > BoidsAIMgr::GetInstance()->window_height * 0.5f)	location.x -= BoidsAIMgr::GetInstance()->window_width;
	if (location.y > BoidsAIMgr::GetInstance()->window_height * 0.5f)	location.y -= BoidsAIMgr::GetInstance()->window_height;
}

Pvector steer(0, 0);

// ����
// �{�C�h���m���߂Â������Ȃ��悤�ɂ���
Pvector BoidsAI::boid_Separation(std::vector<BoidsAI*> BoidsAI_vector, std::vector<BoidsAI*> zonbie_vector)
{
	// �{�C�h�ԕ������싗��
	//float desiredseparation = 10;//����@�v���C���[����̋���
	steer = { 0,0 };
	int count = 0;
	//�V�X�e�����̂��ׂẴ{�C�h�ɂ��āA�߂����邩�ǂ������m�F���܂�

	//for (int i = 0; i < sizeof(BoidsAI_vector)/sizeof(BoidsAI_vector[0]); i++)//0��
	if (boid_accel < 2.0f)
	{
		for (auto& it : BoidsAI_vector)
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

/// <summary>
/// ������֐�
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <returns></returns>
Pvector BoidsAI::boid_Avoid(std::vector<BoidsAI*> BoidsAI_vector)
{
	Pvector stt = { 0,0 };
	for (auto& it : BoidsAI_vector)
	{
		XMFLOAT3 diff = XMFLOAT3(it->GetPos().x - this->GetPos().x, 0.0f, it->GetPos().z - this->GetPos().z);//��Q���Ƃ̋���

		//�����o��
		float distance;
		DX11Vec3Dot(distance, diff, diff);

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
		//�^�[�Q�b�g�Ƃ̃x�N�g���𐳋K��
		XMFLOAT3 target2ObstacleDirection;
		DX11Vec3Normalize(target2ObstacleDirection, diff);

		XMFLOAT3 forward = XMFLOAT3(this->angley.x, 1.0f, this->angley.y);

		DX11Vec3Normalize(forward, forward);

		//���p�����߂�
		float directionDot;
		DX11Vec3Dot(directionDot, target2ObstacleDirection, forward);

		//
		if (directionDot < 0) // �O�����ɏ�Q�����Ȃ���
		{
			return desired = { 0, 0 };
		}

		XMFLOAT3 forward2DiffCross;
		XMFLOAT3 forward2DiffCrossv;
		
		DX11Vec3Cross(forward2DiffCross, diff, forward);
		DX11Vec3Cross(forward2DiffCrossv, forward, diff);

		float forward2ObstacleDistance;
		DX11Vec3Length(forward2DiffCross, forward2ObstacleDistance);

		if (forward2ObstacleDistance > escaperange) // ��Q�����瓦����͈͂Ƒ��x�x�N�g���̒������d�Ȃ��Ă��Ȃ���
		{
			return desired = { 0, 0 };
		}

		const float crossElementSum = forward2DiffCross.x + forward2DiffCross.y + forward2DiffCross.z;
		//const XMFLOAT3 axis;

		//�������߂����Ȃ������f
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
/// �����֐�
/// </summary>
/// <param name="BoidsAI_vector"></param>
/// <returns></returns>
Pvector BoidsAI::boid_inSeparation(std::vector<BoidsAI*> BoidsAI_vector)
{
	// �{�C�h�ԕ������싗��
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
	//�V�X�e�����̂��ׂẴ{�C�h�ɂ��āA�߂����邩�ǂ������m�F���܂�
	for (auto& it : BoidsAI_vector)
	{

		// ���݂�boid���猩�Ă���boid�܂ł̋������v�Z����
		if (it->follow != Follow::HYUMAN)
		{
			float d = location.distance(it->location);
			if ((d > 0) && (d < Sepdist)) {

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

Pvector BoidsAI::boid_Down()
{
	angle.y = 0.0f;//�p�x���Z�b�g

//	velocity.addVector(acceleration);
	velocity.normalize();

	//�x�N�g���ۑ�
	angley.x = velocity.x;
	angley.y = velocity.y;

	//boids�v�Z����o�����x�����Ɍ�����ύX
	angle.y = GetAtan(velocity.x, velocity.y);


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

/// <summary>
/// AI�̃_�b�V���֐�
/// </summary>
///�}�E�X�ň͂����L�������X���C�v�ő��삷��
/// <param name="mousepos"></param>
/// <returns></returns>
Pvector BoidsAI::boid_zonbieAlignment(Pvector mousepos)
{

	//�}�E�X�̒��ɂ��邩
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
{// �{�C�h�ԕ������싗��
	//float desiredseparation = chasedist;//����@�v���C���[����̋���
	steer = { 0.0f,0.0f };
	int count = 0;
	
	float before_distanse = 100.0f;//��ԋ߂������ۑ��p
	
	Pvector nearBoidsAI;//��ԋ߂����݂�ۑ�����ϐ�
	
	if (awayflg == false) {

		// ���݂̃{�C�h���ߐH�҂ł���A�����������Ă���{�C�h���ߐH�҂ł���ꍇ
		// �ߐH�҂͋߂Â��āA���̌�킸���ɕ���
		for (auto& it : BoidsAI_vector)
		{
			float d = location.distance(it->location);
			if (d < before_distanse) {
				before_distanse = d;
				nearBoidsAI = it->location;
			}
		}
		//���͈͓���
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
/// �߂���AI��T������������
/// </summary>
/// <returns></returns>
Pvector BoidsAI::boid_zonbieSearch()
{
	//�����_��������
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution<int32_t> rand4(0,10000);
	std::uniform_int_distribution<int32_t> rand5(-150,150);
	
	
	int cnt = rand4(seed_gen)% Searchcnt;
	if (cnt == 0)
	{
		//�����_���ɏo���ꂽ���l�������Ɏg��
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
/// ���U���Ă���
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
/// ���e�ɂ��_���[�W���󂯂邩�ǂ���
/// </summary>
/// <param name="uniquebomb"></param>
/// <returns></returns>
Pvector BoidsAI::zonbie_damage(std::vector<UniqueEnemy_Bomb*>& uniquebomb)
{
	for (auto& b : BulletMgr::GetInstance()->g_bullets) {
		if (b->explosion == true)
		{
			bombdist = 50;//����@�v���C���[����̋���
		
			ali_vel.x = b->GetMtx()._41;
			ali_vel.y = b->GetMtx()._43;

			float d = location.distance(ali_vel);
			//���e�̃����W
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
	//�S�Ẵ��j�[�N�ȓG�̑��݂��m�F
	for (auto& b : uniquebomb){
		if (b->ubstatus== UniqueEnemy_Bomb::UBSTATUS::LIVE)
		{
			bombdist = 30;//����@�v���C���[����̋���

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
/// AI�̏W������
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

		//�}�E�X�Œ����������ꏊ���擾
		now_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
		now_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
		now_mousepos.x -= Application::CLIENT_WIDTH / 2 * 1.0f;
		now_mousepos.y = Application::CLIENT_HEIGHT / 2 * 1.0f - now_mousepos.y;

		//�X�N���[�����W�ɕϊ�
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
/// �X�N���[�����W��ɕϊ�
/// </summary>
/// <param name="World_Pos"></param>
/// <returns></returns>
XMFLOAT3 BoidsAI::Screenpos(XMFLOAT3 World_Pos) {

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


void BoidsAI::SetAngle()
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

XMFLOAT3 BoidsAI::GetAngle()
{
	return angle;
}


/// <summary>
/// gui�̕ϐ���\������
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

//���[��������������
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
/// ���[���̃Z�[�u�@�\
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


//ai�̒l�̃��[�h
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

int BoidsAI::GetHp()
{
	return hp;
}

float BoidsAI::boid_angle(const Pvector& v)
{
	// ���ς̒�`����
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
