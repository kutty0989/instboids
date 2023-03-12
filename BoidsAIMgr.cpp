#include"BoidsAIMgr.h"
#include"ModelMgr.h"
#include"Scean.h"
#include    "BoundingSphere.h"
#include"IMgui/imgui.h"
#include"Notes_Arrange.h"
#include"XIController.h"
#include"CDirectInput.h"
#include"CCamera.h"
#include"BulletMgr.h"
#include"BoidsHp.h"
#include"InstanceModelMgr.h"
#include"enemy.h"
#define debuglog(a) std::cout<<a<<std::endl;

BoundingSphere g_bsphere;//�����蔻��̋��I�u�W�F�N�g
BoundingSphere g_bsBoidsAI;//�����pBS

//�}�E�X���͗p�ϐ�
static bool input = false;
static bool input_flg = false;

int BoidsAIMgr::BoidsAI_vector_num = boids_num;//�{�C�h�̏����l
int BoidsAIMgr::in_BoidsAI_vector_num = 0;//�v���C���[�̎���ɂ���{�C�h�̏����l
int BoidsAIMgr::in_enemy_vector_num = 0;//�G�l�~�[�̎���ɂ���{�C�h�̏����l
//int BoidsAIMgr::instance_zombie_num = 0;//�G�l�~�[�̎���ɂ���{�C�h�̏����l
int BoidsAIMgr::unique_enemy_vector_num = 0;//�G�l�~�[�̎���ɂ���{�C�h�̏����l
int BoidsAIMgr::unique_enemy_bomb_vector_num = 0;//�G�l�~�[�̎���ɂ���{�C�h�̏����l


const int gridnum = 30;//�O���b�h�����̃T�C�Y
/// <summary>
/// �O���b�h�����ۑ��p�ϐ�
////////////////////////////</summary>
std::vector<BoidsAI> grid_vector[gridnum][gridnum] = {};
std::vector<BoidsAI> grid_zombievector[gridnum][gridnum] = {};
std::vector<ZombieBullet> grid_zombiebulletvector[gridnum][gridnum] = {};
std::vector<UniqueEnemy_Bomb> grid_uniquebombvector[gridnum][gridnum] = {};
//////////////////////////////
//���񂾃L�������i�[����z��
std::vector<BoidsAI> grid_bufvector;
std::vector<BoidsAI> grid_bufzombievector;
std::vector<ZombieBullet> grid_bufzombiebulletvector;
std::vector<UniqueEnemy_Bomb> grid_bufuniquebombvector;
///////////////////////

/// <summary>
/// �C���X�^���V���O���f��
/// </summary>
CModelInstance cmodelinstance_unique_enemy;
CModelInstance cmodelinstance_zombie;
CModelInstance cmodelinstance_hyuman;
CModelInstance cmodelinstance_zombiebullet;
CModelInstance cmodelinstance_uniquebomb;


std::vector<UniqueEnemy_Bomb> instance_uniquebomb;
std::vector<BoidsAI> instance_zombie;
std::vector<BoidsAI> instance_hyuman;
std::vector<ZombieBullet> instance_zombiebullet;
enemy g_test[5000];		// �G
CModel *g_model;
using namespace std;

/// <summary>
/// �|�W�V�����i�[�p
/// </summary>
static XMFLOAT4X4 mat[ENEMYAIMAX];
static XMFLOAT4X4 zmat[PLAYERAIMAX];
static XMFLOAT4X4 zbmat[PLAYERBULLETS];
static XMFLOAT4X4 ubmat[UNIQUEBOMBMAX];
static XMFLOAT3 zpos[PLAYERAIMAX];
/////////////////////////////////////
static int remakeflg = false;

/// <summary>
/// �����������@���f���ǂݍ���
/// </summary>
void BoidsAIMgr::Init()
{
	BoidsAI::GetInstance()->SetNum();
	//�������v���C���[�𐶐�
	BoidsAICreate();

	/// <summary>
	/// �C���X�^���X���f������
	/// </summary>
	cmodelinstance_zombie.InitiInstancing(PLAYERAIMAX, "assets/3danime/cube.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/cube.png");
	cmodelinstance_hyuman.InitiInstancing(ENEMYAIMAX, "assets/3danime/tritop.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/tritop.png");
	cmodelinstance_zombiebullet.InitiInstancing(PLAYERBULLETS, "assets/3danime/sphere.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/tritop.png");
	cmodelinstance_uniquebomb.InitiInstancing(UNIQUEBOMBMAX, "assets/3danime/tritop.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/sphere.png");

	//����v���C���[�̏���������
	for (int i = 0; i < PLAYERAIMAX; i++) {
		BoidsAI buf;
		buf.SetInstanceModel(&cmodelinstance_zombie);
		buf.Init();
		buf.zonbie_Init(buf.GetPos().x, buf.GetPos().z, i);
		instance_zombie.emplace_back(buf);
	}
	//������AI�̐���
	for (int i = 0; i < ENEMYAIMAX; i++) {
		BoidsAI buf;
		buf.SetInstanceModel(&cmodelinstance_hyuman);
		buf.Init();
		buf.boid_Init(buf.GetPos().x, buf.GetPos().z);
		instance_hyuman.emplace_back(buf);
	}
	//�e�̊m��
	for (int i = 0; i < PLAYERBULLETS; i++) {
		ZombieBullet buf;
		buf.SetInstanceModel(&cmodelinstance_zombiebullet);
		buf.Init();
		instance_zombiebullet.emplace_back(buf);
	}
	//���j�[�N�G�l�~�[�̐���
	for (int i = 0; i < UNIQUEBOMBMAX; i++) {
		UniqueEnemy_Bomb buf;
		buf.SetInstanceModel(&cmodelinstance_uniquebomb);
		buf.Init();
		instance_uniquebomb.emplace_back(buf);
	}
	
	//�S�Ẵ��[���̃`�F�b�N���O��
	BoidsAI::GetInstance()->UnCheckBox();

	//�X�R�A�������l��
	ScoreNum = 0;

	//���x�������l��
	maxaccel = 2.0f;
	accel = maxaccel;

	//�o���b�g�Ǘ��N���X�̏�����
	BulletMgr::GetInstance()->Init();
}

/// <summary>
/// AI�S�Ă̍X�V
/// </summary>
void BoidsAIMgr::Update()
{	
	//���[���̃`�F�b�N�{�b�N�X�̓K��
	BoidsAI::GetInstance()->CheckBox();
	
	//AI�̊e�X�V
	BoidsAIUpdate();

	//�e�̍X�V
	BulletMgr::GetInstance()->Update();
}

/// <summary>
/// AI�̕`�揈��
/// </summary>
void BoidsAIMgr::Draw()
{
	//�v���C���[�̒e�`��
	BulletMgr::GetInstance()->Draw();

	// hp�⃌�C�Ȃǂ̕`�揈��
	for (int i = 0; i < PLAYERAIMAX; i++) {

		XMFLOAT3	pos;
		pos = XMFLOAT3(instance_zombie[i].GetMtx()._41, instance_zombie[i].GetMtx()._42, instance_zombie[i].GetMtx()._43);
		zpos[i] = pos;
	
		if (instance_zombie.at(i).bstatus == BoidsAI::BSTATUS::LIVE)
		{
			instance_zombie.at(i).UpdateHp();
		}
	}

	//�G��xyz���̃��C���`��
	for (int i = 0; i < ENEMYAIMAX; i++)
	{
		if (instance_hyuman.at(i).bstatus == BoidsAI::BSTATUS::LIVE)
		{
			instance_hyuman.at(i).HyumanDrawAxis();
		}
	}

	//�G��HP�̍X�V
	for (int i = 0; i < UNIQUEBOMBMAX; i++)
	{
		if (instance_uniquebomb.at(i).ubstatus == UniqueEnemy_Bomb::UBSTATUS::LIVE)
		{
			instance_uniquebomb.at(i).UpdateHP();
		}
	}
	

	unique_enemy_vector.clear();

	// ���f���̕`�揈��
	cmodelinstance_hyuman.DrawInstance();
	cmodelinstance_zombie.DrawInstance();
	cmodelinstance_zombiebullet.DrawInstance();
	cmodelinstance_uniquebomb.DrawInstance();

}

/// <summary>
/// AIno
/// </summary>
void BoidsAIMgr::Finsh()
{
	BulletMgr::GetInstance()->Finalize();

	for (int i = 0; i < PLAYERAIMAX; i++) {
			instance_zombie.at(i).Uninit();
	}

	for (auto& n : BoidsAI_vector) {
		n->Finalize();
		
	}

	BoidsAI_vector.clear();
	BoidsAI_vector.resize(0);

	BoidsAI_vector_num = 0;

	
	instance_zombie.clear();
	instance_zombiebullet.clear();
	instance_uniquebomb.clear();
	
	instance_zombie.resize(0);
	instance_zombiebullet.resize(0);
	instance_uniquebomb.resize(0);

	
	cmodelinstance_zombie.Uninit();
	cmodelinstance_hyuman.Uninit();
	cmodelinstance_zombiebullet.Uninit();
	cmodelinstance_uniquebomb.Uninit();
	cmodelinstance_zombiebullet.Uninit();


	grid_bufvector.clear();
	grid_bufzombievector.clear();
	grid_bufzombiebulletvector.clear();
	grid_bufuniquebombvector.clear();

	grid_bufvector.resize(0);
	grid_bufzombievector.resize(0);
	grid_bufzombiebulletvector.resize(0);
	grid_bufuniquebombvector.resize(0);

	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			grid_vector[m][n].resize(0);
			grid_zombievector[m][n].resize(0);
			grid_zombiebulletvector[m][n].resize(0);
			grid_uniquebombvector[m][n].resize(0);
		}
	}
	//std::vector<shared_ptr<UniqueEnemy>> bufunique_enemy_vector[3][1] = {};//�]���r



	ImBoidsAI->Finalize();
	ImEnemy->Finalize();
	
}

void BoidsAIMgr::BoidsAIUpdate()
{
	//�������f��
	ImBoidsAI->FollowUpdate();

	/// <summary>
	/// �L�����̕ϐ��o�C�i���[�ۑ�
	/// </summary>
	if (BoidsAI::GetInstance()->save)
	{
		BoidsAI::GetInstance()->SaveNum();
		BoidsAI::GetInstance()->save = false;
	}
	if (BoidsAI::GetInstance()->load)
	{
		BoidsAI::GetInstance()->LoadNum();
		BoidsAI::GetInstance()->load = false;
	}
	BoidsAI::GetInstance()->Gui();

	/// <summary>
	/// �X�e�[�^�X���m�F���A��Ԃ�ύX����
	////////////////////////////////////////////// </summary>
	for (int i = 0; i < instance_zombie.size();i++)
	{
		if (instance_zombie.at(i).GetHp() == 0)
		{
			if (instance_zombie.at(i).bstatus != BoidsAI::BSTATUS::DEAD)
			{
				instance_zombie.at(i).bstatus = BoidsAI::BSTATUS::DEAD;
			}
		}
	}
	for (int i = 0; i < instance_zombiebullet.size();i++)
	{
		if (instance_zombiebullet.at(i).m_life < 0)
		{
			if (instance_zombiebullet.at(i).m_sts != ZOMBIEBSTS::DEAD)
			{
				instance_zombiebullet.at(i).m_sts = ZOMBIEBSTS::DEAD;
			}
		}
	}
	for (int i = 0; i < instance_hyuman.size();i++)
	{
		if (instance_hyuman.at(i).GetHp() == 0)
		{
			if (instance_hyuman.at(i).bstatus != BoidsAI::BSTATUS::DEAD)
			{
				instance_hyuman.at(i).bstatus = BoidsAI::BSTATUS::DEAD;
			}
		}
	}

	for (int i = 0; i < instance_uniquebomb.size();i++)
	{
		if (instance_uniquebomb.at(i).GetHp() == 0)
		{
			if (instance_uniquebomb.at(i).ubstatus != UniqueEnemy_Bomb::UBSTATUS::DEAD)
			{
				ScoreNum += 100;
				instance_uniquebomb.at(i).ubstatus = UniqueEnemy_Bomb::UBSTATUS::DEAD;
			}
		}
	}
	/// //////////////////////////////////////////////////
	

	//�O���b�h�̒��g����
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			grid_vector[m][n].clear();
			grid_zombievector[m][n].clear();
			grid_zombiebulletvector[m][n].clear();
			grid_uniquebombvector[m][n].clear();
		}
	}
	//�z��̒��g����
	grid_bufzombievector.clear();
	grid_bufvector.clear();
	grid_bufzombiebulletvector.clear();
	grid_bufuniquebombvector.clear();

	for (int i = 0; i < ENEMYAIMAX; i++)
	{
		//�����Ă���AI�����O���b�h�ɕ�����
		if (instance_hyuman.at(i).bstatus == BoidsAI::BSTATUS::LIVE)
		{
			int column = CHeight_Map::GetInstance()->iPixSize / int((instance_hyuman.at(i).location.x + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			int row = CHeight_Map::GetInstance()->iPixSize / int((instance_hyuman.at(i).location.y + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			grid_vector[column][row].push_back(std::move((instance_hyuman.at(i))));
		}
		else 
		{
	
			grid_bufvector.emplace_back(std::move((instance_hyuman.at(i))));
		}
	}

	instance_hyuman.clear();
	for (int i = 0; i < PLAYERAIMAX;i++)
	{
		//�����Ă���AI����,�񎟌��z��Ɋi�[
		if (instance_zombie.at(i).bstatus == BoidsAI::BSTATUS::LIVE)
		{
			//AI�̏ꏊ��n�ʂ̉𑜓x�ɕύX
			int zcolumn = CHeight_Map::GetInstance()->iPixSize / int((instance_zombie.at(i).location.x 
				+ CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			int zrow = CHeight_Map::GetInstance()->iPixSize / int((instance_zombie.at(i).location.y 
				+ CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			//�i�[
			grid_zombievector[zcolumn][zrow].emplace_back(instance_zombie.at(i));
			
		}
		else
		{
			//����ł���AI�i�[
			grid_bufzombievector.emplace_back(instance_zombie.at(i));
			
		}
	}
	instance_zombie.clear();

	/// <summary>
	/// �e�̏�Ԋm�F
	/// </summary>
	for (int i = 0; i < PLAYERBULLETS; i++)
	{
		if(instance_zombiebullet.at(i).m_sts == ZOMBIEBSTS::LIVE)
		{
			int zcolumn = CHeight_Map::GetInstance()->iPixSize / int((instance_zombiebullet.at(i).GetMtx()._41 + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			int zrow = CHeight_Map::GetInstance()->iPixSize / int((instance_zombiebullet.at(i).GetMtx()._43 + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));

			grid_zombiebulletvector[zcolumn][zrow].emplace_back(instance_zombiebullet.at(i));

		}
		else
		{
			grid_bufzombiebulletvector.emplace_back(instance_zombiebullet.at(i));

		}
	}


	instance_zombiebullet.clear();

	/// <summary>
	/// ���j�[�N�G�l�~�[�O���b�h����
	/// </summary>
	for (int i = 0; i < UNIQUEBOMBMAX; i++)
	{
		if (instance_uniquebomb.at(i).ubstatus == UniqueEnemy_Bomb::UBSTATUS::LIVE)
		{
			int zcolumn = CHeight_Map::GetInstance()->iPixSize / int((instance_uniquebomb.at(i).GetMtx()._41 + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			int zrow = CHeight_Map::GetInstance()->iPixSize / int((instance_uniquebomb.at(i).GetMtx()._43 + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));

			grid_uniquebombvector[zcolumn][zrow].emplace_back(instance_uniquebomb.at(i));

		}
		else
		{
			grid_bufuniquebombvector.emplace_back(instance_uniquebomb.at(i));

		}
	}


	instance_uniquebomb.clear();


	//�O���b�h�����������̂�ׂ������Ă���
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_zombievector[m][n].size();i++)
			{
				if (i == 0)
				{

					buf_vec.clear();
					buf_pvec.clear();
					buf_ubvec.clear();


					for (int w = 0; w < grid_zombievector[m][n].size(); w++)
					{
						BoidsAI* buf = &grid_zombievector[m][n].at(w);
						buf_vec.push_back(buf);
					}

					for (int w = 0; w < grid_vector[m][n].size(); w++)
					{
						BoidsAI* buf = &grid_vector[m][n].at(w);
						buf_pvec.push_back(buf);
					}

					for (int w = 0; w < grid_uniquebombvector[m][n].size(); w++)
					{
						UniqueEnemy_Bomb* buf = &grid_uniquebombvector[m][n].at(w);
						buf_ubvec.push_back(buf);
					}


				}
				// �G�X�V
				grid_zombievector[m][n].at(i).zonbie_run(buf_vec, buf_pvec, mousevelocity,buf_ubvec);
				grid_zombievector[m][n].at(i).BoidsAIAIUpdate(0, 1);
		
				grid_zombievector[m][n].at(i).boids_attack(buf_pvec, grid_zombievector[m][n].at(i), buf_ubvec);
			}
			
		}
	}

	velocityflg = false;
	scatterflg = false;


	if (scattercnt == 0)
	{
		scattercnt = 0;
	}

	static XMFLOAT4X4 phmat[ENEMYAIMAX];

	//�v���C���[�̃O���b�h������ׂ����m�F
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_vector[m][n].size();i++)
			{
				if (i == 0)
				{

					buf_vec.clear();
					buf_pvec.clear();
					buf_zbvec.clear();

					for (int w = 0; w < grid_zombievector[m][n].size(); w++)
					{
						BoidsAI* buf = &grid_zombievector[m][n].at(w);

						buf_vec.push_back(buf);
					}

		

					for (int w = 0; w < grid_vector[m][n].size(); w++)
					{
						BoidsAI* buf = &grid_vector[m][n].at(w);
						buf_pvec.push_back(buf);
					}
					for (int w = 0; w < grid_zombiebulletvector[m][n].size(); w++)
					{
						ZombieBullet* buf = &grid_zombiebulletvector[m][n].at(w);
						buf_zbvec.push_back(buf);
					}
	
				}
				
				//�e�L������update
				grid_vector[m][n].at(i).boid_run(buf_pvec, buf_vec);
				grid_vector[m][n].at(i).Update(false,buf_zbvec);

			}
		}
	}

	//���e�̓G�X�V
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_uniquebombvector[m][n].size();i++)
			{
				if (i == 0)
				{
					buf_pvec.clear();
					buf_zbvec.clear();

					for (int w = 0; w < grid_zombiebulletvector[m][n].size(); w++)
					{
						ZombieBullet* buf = &grid_zombiebulletvector[m][n].at(w);
						buf_zbvec.push_back(buf);
					}
					for (int w = 0; w < grid_zombievector[m][n].size(); w++)
					{
						BoidsAI* buf = &grid_zombievector[m][n].at(w);
						buf_pvec.push_back(buf);
					}

				}
				//���j�[�N�G�l�~�[�X�V
				grid_uniquebombvector[m][n].at(i).UEnemy_run(buf_pvec);
				grid_uniquebombvector[m][n].at(i).Update(buf_pvec,buf_zbvec);
			}

		}
	}

	buf_zbvec.clear();
	buf_pvec.clear();
	buf_ubvec.clear();


	//�e�̃O���b�h�m�F
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_zombiebulletvector[m][n].size();i++)
			{
				if (i == 0)
				{

					buf_pvec.clear();

					for (int w = 0; w < grid_vector[m][n].size(); w++)
					{
						BoidsAI* buf = &grid_vector[m][n].at(w);
						buf_pvec.push_back(buf);
					}

				}
				//���X�V
				grid_zombiebulletvector[m][n].at(i).Update(buf_pvec);
			}

		}
	}

	buf_zbvec.clear();
	////
	//����ai�������֔�΂�
	//////////////////////////////////////////
	for (int i = 0; i < grid_bufvector.size(); i++)
	{
		grid_bufvector.at(i).Update(false,buf_zbvec);
	}
	for (int i = 0; i < grid_bufzombievector.size(); i++)
	{
		grid_bufzombievector.at(i).BoidsAIAIUpdate(0, 0);
	}
	buf_pvec.clear();
	for (int i = 0; i < grid_bufzombiebulletvector.size(); i++)
	{
		grid_bufzombiebulletvector.at(i).Update(buf_pvec);
	}
	for (int i = 0; i < grid_bufuniquebombvector.size(); i++)
	{
		grid_bufuniquebombvector.at(i).Update(buf_pvec,buf_zbvec);
	}

	/////////////////////////////////////////
	//�O���b�h�̒��g���ڂ��ւ���
	////////////////////////////////////
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_vector[m][n].size();i++)
			{
				instance_hyuman.emplace_back(std::move(grid_vector[m][n].at(i)));
			}
		}
	}
	for (int i = 0; i < grid_bufvector.size(); i++)
	{
		instance_hyuman.emplace_back(std::move(grid_bufvector.at(i)));
	}

	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_zombievector[m][n].size();i++)
			{

				instance_zombie.emplace_back(std::move(grid_zombievector[m][n].at(i)));
			}
		}
	}
	for (int i = 0; i < grid_bufzombievector.size(); i++)
	{
		instance_zombie.emplace_back(std::move(grid_bufzombievector.at(i)));
	}

	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_zombiebulletvector[m][n].size();i++)
			{
				instance_zombiebullet.emplace_back(std::move(grid_zombiebulletvector[m][n].at(i)));
			}
		}
	}
	for (int i = 0; i < grid_bufzombiebulletvector.size(); i++)
	{
		instance_zombiebullet.emplace_back(std::move(grid_bufzombiebulletvector.at(i)));
	}
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_uniquebombvector[m][n].size();i++)
			{
				instance_uniquebomb.emplace_back(std::move(grid_uniquebombvector[m][n].at(i)));
			}
		}
	}
	for (int i = 0; i < grid_bufuniquebombvector.size(); i++)
	{
		instance_uniquebomb.emplace_back(std::move(grid_bufuniquebombvector.at(i)));
	}

	/////////////////////////////////////////////////////////////////////�����܂�
	

	//�G���C���X�^���X�p�ɔz��Ɋi�[
	for (int i = 0; i < ENEMYAIMAX; i++) {
	
		XMFLOAT4X4	world;
		world = instance_hyuman[i].GetMtx();;
		mat[i] = world;		
	}
	cmodelinstance_hyuman.Update(mat);

	
	//�v���C���[���C���X�^���X�p�ɔz��Ɋi�[
	for (int i = 0; i < PLAYERAIMAX; i++) {

		XMFLOAT4X4	world;
		world = instance_zombie[i].GetMtx();;
		zmat[i] = world;
	}
	cmodelinstance_zombie.Update(zmat);

	//�����C���X�^���X�p�ɔz��Ɋi�[
	for (int i = 0; i < PLAYERBULLETS; i++)
	{
		XMFLOAT4X4	world;
		world = instance_zombiebullet[i].GetMtx();
		zbmat[i] = world;
	}
	cmodelinstance_zombiebullet.Update(zbmat);


	static XMFLOAT4X4 uemat[UNIQUEBOMBMAX];
	//���j�[�N�ȓG���C���X�^���X�p�ɔz��Ɋi�[
	for (int i = 0; i < UNIQUEBOMBMAX; i++) {
		
		XMFLOAT4X4	world;
		world = instance_uniquebomb.at(i).GetMtx();;
		mat[i] = world;
	}
	cmodelinstance_uniquebomb.Update(mat);



	/// <summary>
	/// �}�E�X����
	/// </summary>
	if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
	{
		scattercnt += 30;
		p_mousepos = { 0,0 };
		r_mousepos = { 0,0 };
		mousevelocity = { 0,0 };

		//�}�E�X�̈ʒu����
		mousestate = Mouse_state::Push_One;
		p_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
		p_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
		p_mousepos.x -= Application::CLIENT_WIDTH / 2;
		p_mousepos.y = Application::CLIENT_HEIGHT / 2 - p_mousepos.y;


		//���U����
		XMFLOAT3 pppos = {};
		if (scattercnt > 90)
		{
			scattercnt = 90;
		}
		if (scattercnt > 61)
		{
			scatterflg = true;
			scattercnt = 0;
		}
		for (int i = 0; i < PLAYERAIMAX;i++)
		{
			//�_�b�V���̃x�N�g��������Ă���
			pppos = instance_zombie[i].Screenpos(instance_zombie[i].GetPos());
			pppos.x -= Application::CLIENT_WIDTH / 2;
			pppos.y = Application::CLIENT_HEIGHT / 2 - pppos.y;

			float dx = pppos.x - p_mousepos.x;
			float dy = pppos.y - p_mousepos.y;
			float dist = sqrt(dx * dx + dy * dy);

			if (dist < 50)
			{
				instance_zombie[i].insideflg = true;
			}

			if (scatterflg  == true)
			{
				//�߂��G�������U
				if (dist < 150)
				{
					instance_zombie[i].zombie_scatterflg = true;
				}
			}
		}

	}
	scattercnt--;
	if (scattercnt < 0)scattercnt = 0;


	//�W������
	if (CDirectInput::GetInstance().GetMouseLButtonCheck())
	{
		mousecnt++;
		if (mousecnt > 20)
		{
			gatherflg = true;
		}
	}

	//�������Ƃ��̏ꏊ���擾
	if (CDirectInput::GetInstance().GetMouseLButtonRelease())
	{
		r_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
		r_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
		r_mousepos.x -= Application::CLIENT_WIDTH / 2;
		r_mousepos.y = Application::CLIENT_HEIGHT / 2 - r_mousepos.y;

		mousecnt = 0;
		gatherflg = false;

		float mousedistance = p_mousepos.distance(r_mousepos);
		if (mousedistance > 5)
		{
			p_mousepos.subVector(r_mousepos);
			p_mousepos.normalize();

			velocityflg = true;
			mousevelocity = p_mousepos;
		}
		else
		{
			mousevelocity = { 0,0 };
		}

	}

	

	////�v�f�̈ړ��ƍ폜
	for (int i = 0; i < ENEMYAIMAX;i++)
	{
		if (instance_hyuman.at(i).hp == 0)
		{
			if (instance_hyuman.at(i).bstatus != BoidsAI::BSTATUS::DEAD)
			{
				instance_hyuman.at(i).bstatus = BoidsAI::BSTATUS::DEAD;

			}
		}
	}
	
	{
	
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("config 4");

		ImGui::SetNextWindowSize(ImVec2(300, 400));
		ImGui::DragInt("BoidsAI_num",&BoidsAI_vector_num);
		ImGui::End();
		ImGui::PopStyleColor();
	}



}
/// <summary>
/// �e�̍Đ���
/// </summary>
/// <param name="mtx"></param>
/// <param name="pos"></param>
void BoidsAIMgr::ZombieBulletRemake(XMFLOAT4X4 mtx, XMFLOAT3 pos)
{

	for (int i = 0; i < grid_bufzombiebulletvector.size(); i++)
	{
		if (grid_bufzombiebulletvector.at(i).isLive() == false) {
		
			grid_bufzombiebulletvector.at(i).Remake(pos,XMFLOAT3(mtx._31,mtx._32,mtx._33));
			break;
		}
		else ++i;
	}


}
/// <summary>
/// �v���C���[����
/// </summary>
void BoidsAIMgr::BoidsAICreate()
{
	std::unique_ptr<BoidsAI> p;
	p = std::make_unique<BoidsAI>();
	p->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::BOX)].modelname));
	p->CharengerInit();
	p->boid_BoidsAI_Init(p->GetPos().x, p->GetPos().z);
//	p->inside = true;
	ImBoidsAI = std::move(p);
}

void BoidsAIMgr::UEnemyBombCreate()
{

}

//�p�b�h�ł̃g���K�[����
bool BoidsAIMgr::Pat_Short_Move()
{

	if (((XIController::GetStickPress(LXPOS, 70)) ||
		(XIController::GetStickPress(LYPOS, 70)) ||
		(XIController::GetStickPress(LXPOS, -70)) ||
		(XIController::GetStickPress(LYPOS, -70))) && (XIController::GetButtonTrigger(XI_R)))
	{
		return true;
	}
	else
	{
		return false;
	}

}

