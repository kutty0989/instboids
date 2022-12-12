#include"PlayerMgr.h"
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

BoundingSphere g_bsphere;//当たり判定の球オブジェクト
BoundingSphere g_bsplayer;//自分用BS
PlayerMgr::DIRECTION g_direction = PlayerMgr::DIRECTION::NEUTRAL;
PlayerMgr::DIRECTION blink_direction = PlayerMgr::DIRECTION::NEUTRAL;
#define debuglog(a) std::cout<<a<<std::endl;
static bool input = false;
static bool input_flg = false;

bool PlayerMgr::miss_flg_flg = false;			//ミスを一度だけにするフラグ
bool PlayerMgr::miss_flg = false;//失敗したときのフラグ
int PlayerMgr::StickXRig = 0;
int PlayerMgr::StickYRig = 0;
int PlayerMgr::player_vector_num = boids_num;//ボイドの初期値
int PlayerMgr::in_player_vector_num = 0;//プレイヤーの周りにいるボイドの初期値
int PlayerMgr::in_enemy_vector_num = 0;//エネミーの周りにいるボイドの初期値
//int PlayerMgr::instance_zombie_num = 0;//エネミーの周りにいるボイドの初期値
int PlayerMgr::unique_enemy_vector_num = 0;//エネミーの周りにいるボイドの初期値
int PlayerMgr::unique_enemy_bomb_vector_num = 0;//エネミーの周りにいるボイドの初期値
int PlayerMgr::RStickRigX = 0;
int PlayerMgr::RStickRigY = 0;

const int gridnum = 20;
std::vector<Player> grid_vector[gridnum][gridnum] = {};
std::vector<Player> grid_zonbievector[gridnum][gridnum] = {};
//std::vector<shared_ptr<UniqueEnemy>> bufunique_enemy_vector[3][1] = {};//ゾンビ

CModelInstance cmodelinstance_unique_enemy;
CModelInstance cmodelinstance_zombie;
CModelInstance cmodelinstance_hyuman;


std::vector<UniqueEnemy_Bomb> instance_e_bomb;
std::vector<Player> instance_zombie;
std::vector<Player> instance_hyuman;
enemy g_test[5000];		// 敵
CModel *g_model;
using namespace std;

void PlayerMgr::Init()
{
	Player::GetInstance()->SetNum();
	//動かすプレイヤーを生成
	/*PlayerCreate();
	EnemyCreate();*/
	//for (int i = 0; i < boids_num; i++)
	//{	
	//	//ボイドを生成
	//	BoidsCreate(0,0);
	//}
	//for (int i = 0; i < zonbbie_num; i++)
	//{
	//	//ボイドを生成
	//	ZonbieCreate();
	//}
	/*for (int i = 0; i < unique_enemy_num; i++)
	{
		UEnemyCreate();
	}*/

	//for (int i = 0; i < unique_enemy_bomb_num; i++)
	//{
	//	UEnemyBombCreate();
	//}
	//
	//g_air.InitiInstancing(100, "assets/3danime/Warzombie F Pedroso.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/Ch21_1001_Diffuse.png");
	cmodelinstance_unique_enemy.InitiInstancing(ENEMYMAX, "assets/3danime/sphere.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/sphere.png");
	cmodelinstance_zombie.InitiInstancing(ZOMBIEMAX, "assets/3danime/cube.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/cube.png");
	cmodelinstance_hyuman.InitiInstancing(HYUMANMAX, "assets/3danime/tritop.fbx", "shader/vsinstance.fx", "shader/ps.fx", "assets/3danime/tritop.png");
	//cmodelinstance_hyuman.InitiInstancing(HYUMANMAX, "assets/3danime/Warzombie F Pedroso.fbx", "shader/vsinstance.fx", "shader/ps.hlsl", "assets/3danime/Ch21_1001_Diffuse.png ");
	//// 敵を初期化
	for (int i = 0; i < ENEMYMAX; i++) {
		UniqueEnemy_Bomb buf;
		buf.SetModel(&cmodelinstance_unique_enemy);
		buf.Init();
		instance_e_bomb.emplace_back(buf);

	}
	for (int i = 0; i < ZOMBIEMAX; i++) {
		Player buf;
		buf.SetInstanceModel(&cmodelinstance_zombie);
		buf.Init();
		buf.zonbie_Init(buf.GetPos().x, buf.GetPos().z, i);
		instance_zombie.emplace_back(buf);
	}
	for (int i = 0; i < HYUMANMAX; i++) {
		Player buf;
		buf.SetInstanceModel(&cmodelinstance_hyuman);
		buf.Init();
		buf.boid_Init(buf.GetPos().x, buf.GetPos().z);
		instance_hyuman.emplace_back(buf);
	}
	
	//// 敵を初期化
	//for (int i = 0; i < ENEMYMAX; i++) {
	//	g_enemy[i].SetModel(&g_air);
	//	g_enemy[i].Init();
	//}

	maxaccel = 2.0f;
	accel = maxaccel;

	BulletMgr::GetInstance()->Init();
}

void PlayerMgr::Update()
{	
	Player::GetInstance()->CheckBox();

	//プレイヤーのパッド角度を最初に取ってくる
	StickXRig = XIController::GetStickRig(LXPOS);//スティックのXの角度　ー100～100
	StickYRig = XIController::GetStickRig(LYPOS);//スティックのYの角度　ー100～100
	//計算し角度に
	pad_rig = GetKakudo(StickXRig, StickYRig);//Lスティックの角度
	
											  //配列の移動など
	PlayerUpdate();

	BulletMgr::GetInstance()->Update();
}

void PlayerMgr::Draw()
{
	//ImPlayer->Draw();
	//ImEnemy->Draw();
	
	BulletMgr::GetInstance()->Draw();

	//for (int i = 0; i < instance_zombie_num; i++)
	//{
	//	instance_zombie[i]->Draw(i);
	//}
	////全描画
	//for (auto& n : player_vector) {
	//	n->Draw(0);
	//}
	//for (auto& n : unique_enemy_bomb_vector)
	//{
	//	n.Draw(instance_zombie);
	//}
//	InstanceModelMgr::GetInstance().InstanceDraw("assets/f1.x.dat");
	//for (int i = 0; i < unique_enemy_vector_num; i++)
	//{
	//	if (unique_enemy_vector[i] != nullptr)
	//	{
	//		int animecnt = unique_enemy_vector[i]->UEnemy_GetAnime();
	//	

	//		shared_ptr <UniqueEnemy> buf = unique_enemy_vector[i];
	//		bufunique_enemy_vector[animecnt]->push_back(move(buf));
	//	}

	//}
	unique_enemy_vector.clear();
	cmodelinstance_unique_enemy.DrawInstance();
	cmodelinstance_hyuman.DrawInstance();
	cmodelinstance_zombie.DrawInstance();
//	g_ene.TestInstance();
//	g_air.DrawInstance();
	//for (int i = 0; i <3; i++)
	//{
	//	for (int a = 0; a < bufunique_enemy_vector[i]->size(); a++)
	//	{
	//	//	if (a == 0)
	//		{
	//			//bufunique_enemy_vector[i]->at(a)->um_model->Update(bufunique_enemy_vector[i]->at(a)->manime.m_Frame, bufunique_enemy_vector[i]->at(a)->manime.m_preFrame, bufunique_enemy_vector[i]->at(a)->manime.m_factor, bufunique_enemy_vector[i]->at(a)->manime.animecnt,
	//				//bufunique_enemy_vector[i]->at(a)->m_mtx);
	//		}
	//	//	bufunique_enemy_vector[i]->at(a)->Draw(instance_zombie);
	//	}
	//}
	//for (auto& n : in_player_vector) {
	//	n->Draw();
	//}
	////敵が
	//for (auto& n : in_enemy_vector) {
	//	n->Draw();
	//}
	////ゾンビの移動
	//for (auto& n : instance_zombie) {
	//	n->Draw();
	//}

}

void PlayerMgr::Finsh()
{
	BulletMgr::GetInstance()->Finalize();

	for (auto& n : player_vector) {
		n->Finalize();
		
	}
	player_vector.clear();
	player_vector_num = 0;
	//for (auto& n : in_player_vector) {
	//	n->Finalize();
	//}
	//for (auto& n : in_enemy_vector) {
	//	n->Finalize();
	//}
	/*for (auto& n : instance_zombie) {
		n->Finalize();
	}
	for (int i = 0; i < unique_enemy_vector.size(); i++)
	{
		unique_enemy_vector[i]->Finalize();
	}
	for (auto& n : unique_enemy_bomb_vector)
	{
		n.Finalize();
	}*/
	
	instance_zombie.clear();

	
	ImPlayer->Finalize();
	ImEnemy->Finalize();
	
}

void PlayerMgr::PlayerUpdate()
{
	if (Player::GetInstance()->save)
	{
		Player::GetInstance()->SaveNum();
		Player::GetInstance()->save = false;
	}
	if (Player::GetInstance()->load)
	{
		Player::GetInstance()->LoadNum();
		Player::GetInstance()->load = false;
	}
	Player::GetInstance()->Gui();

	////要素の移動と削除
	for (int i = 0; i < HYUMANMAX;i++)
	{
		if (instance_hyuman.at(i).GetHp() == 0)
		{
			if (instance_hyuman.at(i).bstatus !=Player::BSTATUS::DEAD)
			{
				for (int a = 0; a < ZOMBIEMAX;a++)
				{
					if (instance_zombie.at(a).bstatus == Player::BSTATUS::DEAD)
					{
						instance_zombie.at(a).zombie_reborn(instance_hyuman.at(a).GetMtx()._41, instance_hyuman.at(a).GetMtx()._43);
						instance_zombie.at(a).bstatus = Player::BSTATUS::LIVE;
						instance_hyuman.at(i).bstatus = Player::BSTATUS::DEAD;
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < instance_zombie.size();i++)
	{
		if (instance_zombie.at(i).GetHp() == 0)
		{
			if (instance_zombie.at(i).bstatus != Player::BSTATUS::DEAD)
			{
				instance_zombie.at(i).bstatus = Player::BSTATUS::DEAD;
			}
		}

	}
	

	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			grid_vector[m][n].clear();
			grid_zonbievector[m][n].clear();
		}
	}


	for (int i = 0; i < HYUMANMAX; i++)
	{
		if (instance_hyuman.at(i).bstatus == Player::BSTATUS::LIVE)
		{
			int column = CHeight_Map::GetInstance()->iPixSize / int((instance_hyuman.at(i).location.x + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			int row = CHeight_Map::GetInstance()->iPixSize / int((instance_hyuman.at(i).location.y + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			grid_vector[column][row].push_back(std::move((instance_hyuman.at(i))));
		}
		else if ((instance_hyuman.at(i).hp <= 0) && (instance_hyuman.at(i).bstatus == Player::BSTATUS::LIVE))
		{
			instance_hyuman.at(i).bstatus == Player::BSTATUS::DEAD;
			
			for (int i = 0; i < ZOMBIEMAX; i++)
			{
				if (instance_zombie.at(i).bstatus == Player::BSTATUS::DEAD)
				{
					instance_zombie.at(i).bstatus = Player::BSTATUS::LIVE;
					instance_zombie.at(i).hp = Player::zonbiehp;
					instance_zombie.at(i).m_mtx._41 = 10000;
					break;
				}
			}
		}
	}
	instance_hyuman.clear();
	for (int i = 0; i < instance_zombie.size();i++)
	{
		if (instance_zombie.at(i).bstatus == Player::BSTATUS::LIVE)
		{
			int zcolumn = CHeight_Map::GetInstance()->iPixSize / int((instance_zombie.at(i).location.x + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			int zrow = CHeight_Map::GetInstance()->iPixSize / int((instance_zombie.at(i).location.y + CHeight_Map::GetInstance()->iPixSize * 0.5f * Ground::GetInstance()->scaling));
			grid_zonbievector[zcolumn][zrow].push_back(move(instance_zombie.at(i)));

		}
	}
	instance_zombie.clear();

	static XMFLOAT4X4 phmat[HYUMANMAX];
	int hyumancnt = 0;
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

					buf_vec = grid_zonbievector[m][n];
					buf_pvec = grid_vector[m][n];
					if (m != 0)
					{
						for (int i = 0; i < grid_zonbievector[m - 1][n].size(); i++)
						{
							Player buf = grid_zonbievector[m - 1][n].at(i);

							buf_vec.push_back(buf);
						}
					}
					if (n != 0)
					{
						for (int i = 0; i < grid_zonbievector[m][n - 1].size(); i++)
						{
							Player buf = grid_zonbievector[m][n - 1].at(i);
							buf_vec.push_back(buf);
						}
					}
					if (m != gridnum)
					{
						for (int i = 0; i < grid_zonbievector[m + 1][n].size(); i++)
						{
							Player buf = grid_zonbievector[m + 1][n].at(i);
							buf_vec.push_back(buf);
						}
					}
					if (n != gridnum)
					{
						for (int i = 0; i < grid_zonbievector[m][n + 1].size(); i++)
						{
							Player buf = grid_zonbievector[m][n + 1].at(i);
							buf_vec.push_back(buf);
						}
					}



					if (m != 0)
					{
						for (int i = 0; i < grid_vector[m - 1][n].size(); i++)
						{
							Player buf = grid_vector[m - 1][n].at(i);
							buf_pvec.push_back(buf);
						}
					}
					if (n != 0)
					{
						for (int i = 0; i < grid_vector[m][n - 1].size(); i++)
						{
							Player buf = grid_vector[m][n - 1].at(i);
							buf_pvec.push_back(buf);
						}
					}
					if (m != gridnum)
					{
						for (int i = 0; i < grid_vector[m + 1][n].size(); i++)
						{
							Player buf = grid_vector[m + 1][n].at(i);
							buf_pvec.push_back(buf);
						}
					}
					if (n != gridnum)
					{
						for (int i = 0; i < grid_vector[m][n + 1].size(); i++)
						{
							Player buf = grid_vector[m][n + 1].at(i);
							buf_pvec.push_back(buf);
						}
					}

				}


				XMFLOAT4X4	world;

				//DX11MtxFromQt(world, g_enemy[i].GetRotation());

				grid_vector[m][n].at(i).boid_run(buf_pvec, buf_vec);
				grid_vector[m][n].at(i).Update(false);


				world = grid_vector[m][n].at(i).GetMtx();
				phmat[hyumancnt] = world;

				hyumancnt += 1;
			}
		}
	}
	cmodelinstance_hyuman.Update(phmat);
	hyumancnt = 0;

	static XMFLOAT4X4 zmat[ZOMBIEMAX];
	static unsigned int animno = 0;
	int zonbiecnt = 0;
	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_zonbievector[m][n].size();i++)
			{

				if (i == 0)
				{
					buf_vec.clear();
					buf_pvec.clear();

					buf_vec = grid_zonbievector[m][n];
					buf_pvec = grid_vector[m][n];
					if (m != 0)
					{
						for (int i = 0; i < grid_zonbievector[m - 1][n].size(); i++)
						{
							Player buf = grid_zonbievector[m - 1][n].at(i);
							buf_vec.push_back(buf);
						}
					}
					if (n != 0)
					{
						for (int i = 0; i < grid_zonbievector[m][n - 1].size(); i++)
						{
							Player buf = grid_zonbievector[m][n - 1].at(i);
							buf_vec.push_back(buf);
						}
					}
					if (m != gridnum)
					{
						for (int i = 0; i < grid_zonbievector[m + 1][n].size(); i++)
						{
							Player buf = grid_zonbievector[m + 1][n].at(i);
							buf_vec.push_back(buf);
						}
					}
					if (n != gridnum)
					{
						for (int i = 0; i < grid_zonbievector[m][n + 1].size(); i++)
						{
							Player buf = grid_zonbievector[m][n + 1].at(i);
							buf_vec.push_back(buf);
						}
					}



					if (m != 0)
					{
						for (int i = 0; i < grid_vector[m - 1][n].size(); i++)
						{
							Player buf = grid_vector[m - 1][n].at(i);
							buf_pvec.push_back(buf);
						}
					}
					if (n != 0)
					{
						for (int i = 0; i < grid_vector[m][n - 1].size(); i++)
						{
							Player buf = grid_vector[m][n - 1].at(i);
							buf_pvec.push_back(buf);
						}
					}
					if (m != gridnum)
					{
						for (int i = 0; i < grid_vector[m + 1][n].size(); i++)
						{
							Player buf = grid_vector[m + 1][n].at(i);
							buf_pvec.push_back(buf);
						}
					}
					if (n != gridnum)
					{
						for (int i = 0; i < grid_vector[m][n + 1].size(); i++)
						{
							Player buf = grid_vector[m][n + 1].at(i);
							buf_pvec.push_back(buf);
						}
					}

				}


				// 敵更新
				grid_zonbievector[m][n].at(i).zonbie_run(buf_vec, buf_pvec, mousevelocity);
				grid_zonbievector[m][n].at(i).ZonbieUpdate(animno, 1);
				grid_zonbievector[m][n].at(i).boids_attack(buf_pvec, grid_zonbievector[m][n].at(i), unique_enemy_bomb_vector);
				XMFLOAT4X4	world;
				world = grid_zonbievector[m][n].at(i).GetMtx();
				//DX11MtxFromQt(world, g_enemy[i].GetRotation());

				zmat[zonbiecnt] = world;
				zonbiecnt += 1;

			}
		}
	}

	cmodelinstance_zombie.Update(zmat);
	zonbiecnt = 0;
	velocityflg = false;
	scatterflg = false;


	if (scattercnt == 0)
	{
		scattercnt = 0;
	}
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

	for (int m = 0; m < gridnum; m++)
	{
		for (int n = 0; n < gridnum; n++)
		{
			for (int i = 0;i < grid_zonbievector[m][n].size();i++)
			{
				instance_zombie.emplace_back(std::move(grid_zonbievector[m][n].at(i)));
			}
		}
	}

	//for (int i = 0; i < unique_enemy_vector.size(); i++)
	//{

	//	unique_enemy_vector[i]->UEnemy_run(instance_zombie);
	//	unique_enemy_vector[i]->Update();

	//}

	/*for (int i = 0; i < ENEMYMAX; i++)
	{
		if (instance_e_bomb.at(i).bstatus == Player::BSTATUS::LIVE)
		{
			unique_enemy_bomb_vector.at(i).UEnemy_run(instance_zombie);
			unique_enemy_bomb_vector.at(i).Update();
		}
	}*/

	//for (int i = 0; i < unique_enemy_bomb_vector_num; i++)
	//{
	//	if (unique_enemy_bomb_vector.at(i).GetHp() <= 0)
	//	{
	//		unique_enemy_bomb_vector.at(i).UEDelete(i, unique_enemy_bomb_vector);
	//		unique_enemy_bomb_vector_num--;
	//	}

	//}
	//static XMFLOAT4X4 mat[ENEMYMAX];
	//// 敵更新
	//for (int i = 0; i < ENEMYMAX; i++) {
	//	g_enemy[i].UEnemy_run(instance_zombie);
	//	g_enemy[i].Update();
	//	XMFLOAT4X4	world;
	//	world = g_enemy[i].GetMtx();;
	//	//DX11MtxFromQt(world, g_enemy[i].GetRotation());
	//
	//	mat[i] = world;
	//}
		static XMFLOAT4X4 mat[ENEMYMAX];
	// 敵更新
	for (int i = 0; i < ENEMYMAX; i++) {
		if (instance_e_bomb.at(i).bstatus == Player::BSTATUS::LIVE)
		{
			instance_e_bomb.at(i).UEnemy_run(instance_zombie);
			instance_e_bomb.at(i).Update();
		}
		XMFLOAT4X4	world;
		world = instance_e_bomb.at(i).GetMtx();;
		//DX11MtxFromQt(world, g_enemy[i].GetRotation());
	
		mat[i] = world;
	}
	cmodelinstance_unique_enemy.Update(mat);




	if (CDirectInput::GetInstance().GetMouseLButtonTrigger())
	{
		scattercnt += 30;
		p_mousepos = { 0,0 };
		r_mousepos = { 0,0 };
		mousevelocity = { 0,0 };

		mousestate = Mouse_state::Push_One;
		p_mousepos.x = CDirectInput::GetInstance().GetMousePosX();
		p_mousepos.y = CDirectInput::GetInstance().GetMousePosY();
		p_mousepos.x -= Application::CLIENT_WIDTH / 2;
		p_mousepos.y = Application::CLIENT_HEIGHT / 2 - p_mousepos.y;


		XMFLOAT3 pppos = {};

		for (int i = 0; i < ZOMBIEMAX;i++)
		{

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
		}
	}
	scattercnt--;
	if (scattercnt < 0)scattercnt = 0;
	if (scattercnt > 61)
	{
		scatterflg = true;
	}
	if (scattercnt > 90)
	{
		scattercnt = 90;
	}

	if (CDirectInput::GetInstance().GetMouseLButtonCheck())
	{
		mousecnt++;
		if (mousecnt > 20)
		{
			gatherflg = true;
		}
	}
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

	

	// インスタンスバッファを更新
//	g_air.Update(mat);

	//static XMFLOAT4X4 testmat[5000];
	//// 敵更新
	//for (int i = 0; i < 5000; i++) {
	//	g_test[i].Update();
	//	
	//	XMFLOAT4X4	world;
	//	world = g_test[i].GetMtx();;
	////	DX11MtxFromQt(world, g_test[i].GetRotation());

	//	testmat[i] = world;
	//}
//	g_ene.TestUpdate(testmat);
	//InstanceModelMgr::GetInstance().InstanceUpdate("assets/f1.x.dat",mat);
	{
		//ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("config 4");

		ImGui::SetNextWindowSize(ImVec2(300, 400));
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

		//ImGui::DragInt("zonbie_num",&instance_zombie_num);
		ImGui::DragInt("player_num",&player_vector_num);
		ImGui::End();
		ImGui::PopStyleColor();
	}



}
//
//void PlayerMgr::BoidsCreate(float x, float z)
//{
//	shared_ptr<Player> pl;
//	pl = std::make_shared<Player>();
//	pl->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::PLAYER)].modelname));
//	pl->Init();
//	if ((x == 0)&&(z == 0))
//	{
//		pl->boid_Init(pl->GetPos().x, pl->GetPos().z);
//	}
//	else
//	{
//		pl->boid_Init(x, z);
//	}
////	pl->SetScale(10.0f, 10.0f, 10.0f);
//	player_vector.emplace_back(std::move(pl));
//}
//
//void PlayerMgr::PlayerCreate()
//{
//	std::unique_ptr<Player> p;
//	p = std::make_unique<Player>();
//	p->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::BOX)].modelname));
//	p->CharengerInit();
//	p->boid_player_Init(p->GetPos().x, p->GetPos().z);
////	p->inside = true;
//	ImPlayer = std::move(p);
//}
//
//void PlayerMgr::EnemyCreate()
//{
//	std::unique_ptr<Player> p;
//	p = std::make_unique<Player>();
//	p->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::BOX)].modelname));
//	p->CharengerInit();
//	p->boid_player_Init(p->GetPos().x, p->GetPos().z);
//	
//	ImEnemy = std::move(p);
//}
//
//void PlayerMgr::BuildCreate(XMFLOAT3 pos)
//{
//	std::unique_ptr<Build> p;
//	p = std::make_unique<Build>();
//	p->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::BOX)].modelname));
//	p->Init(pos);
//	build_vector.emplace_back(std::move(p));
//
//}
//
//void PlayerMgr::ZonbieCreate()
//{
//	shared_ptr<Player> pl;
//	pl = std::make_shared<Player>();
//	pl->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::ONE)].modelname));
//	pl->Init();
//	pl->zonbie_Init(pl->GetPos().x, pl->GetPos().z);
//	pl->SetScale(0.1f, 0.1f, 0.1f);
//	instance_zombie_num++;
//	instance_zombie.emplace_back(std::move(pl));
//
//}

//void PlayerMgr::UEnemyCreate()
//{
//	shared_ptr<UniqueEnemy> pl;
//	pl = std::make_shared<UniqueEnemy>();
//	pl->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::BOX)].modelname));
//	pl->Init();
//	unique_enemy_vector_num++;
//	unique_enemy_vector.emplace_back(std::move(pl));
//}

void PlayerMgr::UEnemyBombCreate()
{
	//shared_ptr<UniqueEnemy_Bomb> pl;
	//pl = std::make_shared<UniqueEnemy_Bomb>();
	//pl->SetModel(ModelMgr::GetInstance().GetModelPtr(Scean::GetInstance()->g_modellist[static_cast<int>(Scean::MODELID::PLAYER)].modelname));
	////pl->SetInstanceModel(InstanceModelMgr::GetInstance().GetInstanceModelPtr(Scean::GetInstance()->g_modelinstancelist[static_cast<int>(Scean::MODELIID::PLAYER)].modelname));
	//
	//pl->Init();
	//
	//unique_enemy_bomb_vector_num++;
	//unique_enemy_bomb_vector.emplace_back(std::move(pl));
}




bool PlayerMgr::Pat_Short_Move()
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

