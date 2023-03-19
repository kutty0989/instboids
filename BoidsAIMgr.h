#pragma once
#include"BoidsAI.h"
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
#include"zombiebullet.h"
#include"CHeight_Map.h"

const int boids_num = 200;//�S�̂�boids�̏�����
const int zonbbie_num = 100;//�]���r�̏�����
const int unique_enemy_num = 0;//�ߐڂ̏�����
const int unique_enemy_bomb_num = 10;//�������̏�����



class BoidsAIMgr
{
public:

	std::vector<shared_ptr<BoidsAI>> BoidsAI_vector;//�͈͊O��bodis
	std::vector<shared_ptr<BoidsAI>> in_BoidsAI_vector;//�͈͓���boids
	std::vector<shared_ptr<BoidsAI>> zonbie_vector;//�]���r
	std::vector<shared_ptr<UniqueEnemy>> unique_enemy_vector;//�]���r
	std::vector<UniqueEnemy_Bomb> unique_enemy_bomb_vector;//�]���r
	std::vector<shared_ptr<BoidsAI>> in_enemy_vector;//�G�͈͓̔���boids
	std::vector <BoidsAI*> instance_vector;//�G�͈͓̔���boids
	//std::vector<shared_ptr<Build>> build_vector;//����
	
	std::vector<BoidsAI*> buf_vec; 
	std::vector<BoidsAI*> buf_pvec;
	std::vector<UniqueEnemy_Bomb*> buf_ubvec;
	std::vector<ZombieBullet*> buf_zbvec;
	std::shared_ptr<BoidsAI> ImBoidsAI;
	std::shared_ptr<BoidsAI> ImEnemy;


	const int window_height = (CHeight_Map::GetInstance()->iPixSize - 60) * CHeight_Map::ScaleMap;//�}�b�v�̑傫���@�c
	const int window_width = (CHeight_Map::GetInstance()->iPixSize - 60) * CHeight_Map::ScaleMap;//�}�b�v�̑傫���@��

	int ScoreNum = 0;


	void Init();

	void Update();

	void Draw();

	void Finsh();

	void BoidsCreate(float x,float z);

	void BoidsAICreate();

	void EnemyCreate();
	
	void BuildCreate(XMFLOAT3 pos);
	
	void ZonbieCreate();

	void UEnemyCreate();

	void UEnemyBombCreate();

	void BoidsAIUpdate();

	bool CheckImnput();

	void oneBoidsAIUpdate();

	void Releace();

	void ZombieBulletRemake(XMFLOAT4X4 mtx,XMFLOAT3 pos);

	static BoidsAIMgr* GetInstance()
	{
		static BoidsAIMgr instance;
		return &instance;
	}

	/// <summary>
	/// �p�b�h�ړ��@L�X�e�b�N���X�����Ă��āA�q�P�������ꂽ��true
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
		NOT,//�f�t�H���g���
		READY,//�����O�m�[�c�L�[�������ꂽ���
		READY_ZERO,//�m�[�c���^�񒆂ɂȂ��Ƃ�
		NOW,//�����Ȃ���΂Ȃ�Ȃ����
		COH,//���S�ɏW�܂鎞��
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
		NOT,//�f�t�H���g���
		READY,//�����O�m�[�c�L�[�������ꂽ���
		READY_ZERO,//�m�[�c���^�񒆂ɂȂ��Ƃ�
		NOW,//�����Ȃ���΂Ȃ�Ȃ����
		MISS,//�����^�C�~���O���߂���
		END
	};

	Billding_state billding_state = Billding_state::NOT;


	float accel = 0.0f;
	float maxaccel = 6.0f;

	///////////////////////////////
	//�m�[�c�p�̕ϐ�
	//////////////////////////
	bool turn_flg = false;						//�A�őj�~�p�̃t���O
	bool judge_flg = false;			        	//1����1��s���ɂ��邽�߂ɕK�v
	int turn_cnt = 0;//���Ԗڂ̃m�[�c���𔻒f�@1~6�Z�m�[�c�@7�`8�@�����O�m�[�c
	bool step_flg = false;//�����O�m�[�c��
	bool blink_flg = false;//�u�����N���肪�S�Ēʂ������̐���
	bool rhythm_checker = false;//���Y������ꂽ����
	bool building_flg = false;//���z����t���O
	bool buildlv_flg = false;//���z�Ƀ��\�[�X�𒍂��t���O
	bool ZeroSen_flg = false; //�O�`1000�b�̊�
	bool Minus_Sen_Zero_flg = false;//-1000����O�̊�
	float seconds = 0.0f;//�Ȃ̕b��
	int iseconds = 0;//�Ȃ̕b��10000�{
	int judge_seconds = 0;//��������10000�{
	float beat = 0.0f;//�P������������̕b��
	static bool miss_flg_flg;			//�~�X����x�����ɂ���t���O
	static bool miss_flg;//���s�����Ƃ��̃t���O

	//////////////////////
	


	float pad_rig = 0.0f;//L�X�e�B�b�N�̊p�x
	/////////////////////

	
	static int BoidsAI_vector_num;//�v���C���[�̊O���z��̗v�f��
	static int in_BoidsAI_vector_num;//�v���C���[�̓����z��̗v�f��
	static int in_enemy_vector_num;//�G�l�~�[�[�̓����z��̗v�f��
	static int zonbie_vector_num;//�]���r�[�̔z��̗v�f��
	static int unique_enemy_vector_num;//�]���r�[�̔z��̗v�f��
	static int unique_enemy_bomb_vector_num;//�]���r�[�̔z��̗v�f��
	
	////////////////////////
	//�}�E�X�̍��W
	/////////////////////////
	float mousex;
	float bmousex;
	float mousey;
	float bmousey;
	Pvector r_mousepos;
	Pvector p_mousepos;
	Pvector now_mousepos;
	Pvector mousevelocity;
	int mousecnt=0;//�}�E�X�������Ă���̎��Ԃ����
	int	scattercnt = 0;

	//////////////////////////

	bool gatherflg = false;
	bool velocityflg = false;
	bool scatterflg = false;//���U�̏���
	
	enum class Mouse_state
	{
		None,
		Push_One,
		Push,
		Release
	};
	Mouse_state mousestate = Mouse_state::None;

	/// <summary>
	/// �p�b�h���X���Ă��邩�ǂ���
	/// </summary>
	bool BoidsAI_pad_flg = false;


	bool Getpad_rig_flg()
	{
		return BoidsAI_pad_flg;
	}



	XMFLOAT3 Screenpos(XMFLOAT3 World_Pos);
private:

public:
	
};