#include "UniqueEnemy.h"
#include"ground.h"
const int INTERPOLATENUM = 4;			// ��Ԑ�

bool UniqueEnemy::Init()
{
	// �s�񏉊���
	DX11MtxIdentity(m_mtx);

	//XYZ�̎������o���ۊ�
	SetQutenion();

	float posx = rand() % 400 - 200;
	float posz = rand() % 400 - 200;
	SetPos(XMFLOAT3(posx, 0.0f, posz));
	angle.x = 0.0f;
	angle.z = 0.0f;
	angle.y = -90.0f;


	float xx = rand() % 5 - 2.0f;
	float yy = rand() % 5 - 2.0f;

	acceleration = Pvector(0, 0);
	velocity = Pvector(xx, yy);//�����x
	location = Pvector(posx, posz);//�|�W�V����
	maxSpeed = 1.8f;
	maxForce = 0.7f;

	

	champion = false;
	desSep = 5.0f;
	desAli = 15.0f;
	desCoh = 10.0f;
	SepW = 1.5f;
	AliW = 1.0f;
	CohW = 1.0f;

	return true;
}

void UniqueEnemy::Draw(std::vector<shared_ptr<Player>>& zonbie_vector)
{
	
	if (um_model->m_assimpfile.animationreset == true)
	{
		float desiredseparation = 10;//����@�v���C���[����̋���
		if(manime.animecnt == 2)
		{ 
			for (auto& it : zonbie_vector)
			{
				if (it != nullptr)
				{
					float d = location.distance(it->location);
					// ���݂̃{�C�h���ߐH�҂ł͂Ȃ��A�����������Ă���{�C�h��
					// �ߐH�ҁA���ɑ傫�ȕ��� Pvector ���쐬���܂�
					if ((d > 0) && (d < desiredseparation) && it->predator == true) {

						it->hp = 0;
					}
				}
			}
			manime.animecnt = 0;
			unique_enemy_anime = UNIQUE_ENEMY_ANIME::IDLE;
		}
	}
	
//	m_model->Update(animecnt, m_mtx, animereset);
	// ���f���`��
	um_model->Draw(m_mtx);

	

}
void UniqueEnemy::Update()
{
	
	boid_borders();
	Ground::GetInstance()->GetPlayerHeight(*this);

	//Z�������o��
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;
	
	if ((unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)&&(boid_accel == 0))
	{
		unique_enemy_anime = UNIQUE_ENEMY_ANIME::IDLE;
		manime.animecnt = 0;
	}
	if((unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)&& (boid_accel > 0))
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

	scale._11 = 5.0f;
	scale._22 = 5.0f;
	scale._33 = 5.0f;

	angle.y = -GetKakudo(angley.x, angley.y);
	angle.y += 180.0f;
	if (angle.y < 360)
	{
		angle.y -= 360.0f;
	}
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

	b_animecnt = manime.animecnt;//�O��̃A�j���ԍ��ۑ�
	

	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("config 5");

		ImGui::SetNextWindowSize(ImVec2(300, 400));
		float pos[2] = { location.x,location.y };
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

	
		//float pos[3] = { Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z};
		ImGui::DragInt("animecnt", &manime.animecnt);
		ImGui::DragInt("animecnt", &manime.m_Frame);
		ImGui::DragFloat2("pos", pos);


		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	if (manime.m_cnt % INTERPOLATENUM == 0) {
		manime.m_preFrame = manime.m_Frame;
		manime.m_Frame++;
		manime.m_factor = 0;
	}

	manime.m_factor = 1.0f / (float)(manime.m_cnt % INTERPOLATENUM + 1);

	manime.m_cnt++;

}

void UniqueEnemy::UEnemy_run(std::vector<shared_ptr<Player>>& zonbie_vector)
{
	UEnemy_flock(zonbie_vector);
	UEnemy_update();
}




void UniqueEnemy::UEnemy_flock(std::vector<shared_ptr<Player>>& zonbie_vector)
{
	ueser = { 0,0 };
	uesep = { 0,0 };
	ueatt = { 0,0 };

	if (unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)
	{
		ueser = UEnemy_Search();

		//	uesep = UEnemy_Separation(zonbie_vector);
		//ueatt = UEnemy_Attack(zonbie_vector);
	}



	ueser.mulScalar(CohW);
	//uesep.mulScalar(SepW);
	ueatt.mulScalar(1.5f);



	applyForce(ueser);
	applyForce(uesep);
	applyForce(ueatt);

}

void UniqueEnemy::UEnemy_update()
{
	acceleration.normalize();

	acceleration.mulScalar(boid_accel);
	//  �X�V���x
	velocity.addVector(acceleration);

	location.addVector(velocity);

	velocity.mulScalar(0);
}




Pvector UniqueEnemy::UEnemy_Search()
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

Pvector UniqueEnemy::UEnemy_Separation(std::vector<shared_ptr<Player>>& zonbie_vector)
{
	// �{�C�h�ԕ������싗��
	float desiredseparation = 10;//����@�v���C���[����̋���
	uesteer = { 0,0 };
	int count = 0;
	//�V�X�e�����̂��ׂẴ{�C�h�ɂ��āA�߂����邩�ǂ������m�F���܂�

	for (auto& it : zonbie_vector)
	{
		if (it != nullptr)
		{
			float d = location.distance(it->location);
			// ���݂̃{�C�h���ߐH�҂ł͂Ȃ��A�����������Ă���{�C�h��
			// �ߐH�ҁA���ɑ傫�ȕ��� Pvector ���쐬���܂�
			if ((d > 0) && (d < desiredseparation) && it->predator == true) {
				uedesired = { 0,0 };
				uedesired = uedesired.subTwoVector(location, it->location);
				uedesired.mulScalar(900);
				uesteer.addVector(uedesired);
				count++;
			}
		}
	}

	// �ʒu�̕��ύ��������x�ɉ��Z
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

Pvector UniqueEnemy::UEnemy_Attack(std::vector<shared_ptr<Player>>& zonbie_vector)
{
	// �{�C�h�ԕ������싗��
	float desiredseparation = 80;//����@�v���C���[����̋���
	uesteer = { 0,0 };
	float before_distanse = 80.0f;//��ԋ߂������ۑ��p

	Pvector nearplayer;//��ԋ߂����݂�ۑ�����ϐ�
	if (unique_enemy_anime != UNIQUE_ENEMY_ANIME::ATTACK)
	{
	for (auto& it : zonbie_vector)
	{
		float d = location.distance(it->location);
		if (d < before_distanse) {
			before_distanse = d;
			nearplayer = it->location;
		}
	}
	
	if ((before_distanse > 0) && (before_distanse <15))
	{
		uedesired = { 0,0 };
		uedesired = uedesired.subTwoVector(location, nearplayer);
		uedesired.normalize();
		uedesired.mulScalar(-1);
		acceleration = uedesired;
		angley.x = uedesired.x;
		angley.y = uedesired.y;

		unique_enemy_anime = UNIQUE_ENEMY_ANIME::ATTACK;

	}

		if ((before_distanse > 15) && (before_distanse < desiredseparation))
		{
			uedesired = { 0,0 };
			uedesired = uedesired.subTwoVector(location, nearplayer);
			uedesired.normalize();
			uedesired.mulScalar(-1);
			uedesired.divScalar(before_distanse);

			acceleration = uedesired;
			angley.x = acceleration.x;
			angley.y = acceleration.y;
			this->boid_accel = 0.3f;
		}
	}
return uedesired;
}

int UniqueEnemy::UEnemy_GetAnime()
{
	return manime.animecnt;
}
