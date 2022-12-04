#include"CCamera.h"
#include"IMgui/imgui.h"
#include"PlayerMgr.h"
#include"CDirectInput.h"

bool CCamera::blowflg = false;
void CCamera::FPSCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
{
	//�����_���v�Z
	XMFLOAT3 lookat;
	lookat.x = pos.x + axisz.x;
	lookat.y = pos.y + axisz.y;
	lookat.z = pos.z + axisz.z;

	//�J�����̈ʒu���v�Z
	XMFLOAT3 eye;
	eye.x = pos.x;
	eye.y = pos.y;
	eye.z = pos.z;

	//�J�����̏�������v�Z
	XMFLOAT3 up;
	up.x = axisy.x;
	up.y = axisy.y;
	up.z = axisy.z;

	//�J�����N���X�ɃZ�b�g
	CCamera::GetInstance()->SetLookat(lookat);///�����_���Z�b�g
	CCamera::GetInstance()->SetEye(eye);//�J�����̈ʒu���Z�b�g
	CCamera::GetInstance()->SetUp(up);//�J�����̏�������Z�b�g

	CCamera::GetInstance()->CreateCameraMatrix();//�r���[�ϊ��s����쐬

}


void CCamera::TPSCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
{
	static float a = 0.0f;
	static float b = 0.0f;
	static float c = 0.0f;

	static float x = 0.0f;
	static float y = 0.0f;
	static float z = 0.0f;

	static int cnt = 10;

	//�J�����̈ʒu���v�Z
	XMFLOAT3 eye;
	eye.x = 0 + a;
	eye.y = 1300.0f + b;
	eye.z = -240.0f + c;


	XMFLOAT3 lookat;
	lookat.x = eye.x + x;
	lookat.y = eye.y +y- 10;
	lookat.z = eye.z +z+ 4;


	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_O))
	{
		blowflg = true;
		
	}
	if (blowflg)
	{
		x = rand() % 10 * 0.01f;
		y = rand() % 10 * 0.01f;
		z = rand() % 10 * 0.01f;
		cnt--;
		if (cnt < 0)
		{
			blowflg = false;
			cnt = 10;
			lookat.x = eye.x + x;
			lookat.y = eye.y + y - 10;
			lookat.z = eye.z + z + 4;

		}
	}
	

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W))
	{
		c += 10.0f;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S))
	{
		c -= 10.0f;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D))
	{
		a += 10.0f;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A))
	{
		a -= 10.0f;
	}
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP))
	{
		b += 10.0f;
	}if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN))
	{
		b -= 10.0f;
	}

	/*bool rhythm = PlayerMgr::GetInstance()->rhythm_checker;
	if (rhythm)
	{
		max_camera = 400.0f;
	}
	if (!rhythm)
	{
		max_camera -= 4.0f;
	}
	if (max_camera < 0)
	{
		max_camera = 0;
	}
	cameracnt+=3.0f;

	if (cameracnt > max_camera)
	{
		cameracnt = max_camera;
	}*/

	//�J�����̏�������v�Z
	XMFLOAT3 up;
	up.x = 0;
	up.y = 0;
	up.z = 1;

	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("config 3");

		ImGui::SetNextWindowSize(ImVec2(300, 400));
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

		float pos[3] = { a ,b,c };

		//float pos[3] = { Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z};
		ImGui::DragFloat3("CAMERA ANGLE", pos);

	
		//ImGui::DragInt("notes", &it);
		a = pos[0];
		b = pos[1];
		c = pos[2];
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}


	//�J�����N���X�ɃZ�b�g
	CCamera::GetInstance()->SetLookat(lookat);///�����_���Z�b�g
	CCamera::GetInstance()->SetEye(eye);//�J�����̈ʒu���Z�b�g
	CCamera::GetInstance()->SetUp(up);//�J�����̏�������Z�b�g

	CCamera::GetInstance()->CreateViewMatrix();
	CCamera::GetInstance()->CreateCameraMatrix();//�r���[�ϊ��s����쐬

}

void CCamera::TopCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy) {
	XMFLOAT3 lookat;
	lookat.x = pos.x + axisz.x;
	lookat.y = pos.y + axisz.y;
	lookat.z = pos.z + axisz.z;
	static float a = 0.0f;
	static float b = 0.0f;
	static float c = 0.0f;



	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("config 3");

		ImGui::SetNextWindowSize(ImVec2(300, 400));
		//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

		float pos[3] = { a ,b,c };
		//float pos[3] = { Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y, Player::GetInstance()->GetPos().z};
		ImGui::DragFloat3("CAMERA ANGLE", pos);
		//ImGui::DragInt("notes", &it);
		a = pos[0];
		b = pos[1];
		c = pos[2];
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	//�J�����̈ʒu���v�Z
	XMFLOAT3 eye;
	eye.x = pos.x + a;
	eye.y = pos.y +b+ 450.0f;
	eye.z = pos.z +c + axisy.z -900.0f;


	//�J�����̏�������v�Z
	XMFLOAT3 up;
	up.x = axisz.x;
	up.y = axisz.y;
	up.z = axisz.z;


	//�J�����N���X�ɃZ�b�g
	CCamera::GetInstance()->SetLookat(lookat);///�����_���Z�b�g
	CCamera::GetInstance()->SetEye(eye);//�J�����̈ʒu���Z�b�g
	CCamera::GetInstance()->SetUp(up);//�J�����̏�������Z�b�g

	CCamera::GetInstance()->CreateCameraMatrix();//�r���[�ϊ��s����쐬

}

//�Œ蒍���J����
void CCamera::FixedCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
{
	XMFLOAT3 lookat;
	lookat.x = pos.x + axisz.x;
	lookat.y = pos.y + axisz.y;
	lookat.z = pos.z + axisz.z;

	CCamera::GetInstance()->SetLookat(lookat);

	CCamera::GetInstance()->CreateCameraMatrix();

}
//
////������Ƃ�����Ă��Ă���J����
//void CCamera::DelayCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
//{
//
//	//�r���[�ϊ��s��擾
//	static int svidx = 0;//�ۑ��ʒu�������C���f�b�N�X�̒l
//	static bool firstflag = false;//100�܂ŕۑ��������������t���O
//
//	static std::array<XMFLOAT3, 100> axisZ;//Z��
//	axisz[svidx].x = mtx._31;
//	zaxis[svidx].y = mtx._32;
//	zaxis[svidx].z = mtx._33;
//
//	static std::array<XMFLOAT3, 100> yaxis;//Y��
//	yaxis[svidx].x = mtx._21;
//	yaxis[svidx].y = mtx._22;
//	yaxis[svidx].z = mtx._23;
//
//
//	static std::array<XMFLOAT3, 100> pos;//���݈ʒu
//	pos[svidx].x = mtx._41;
//	pos[svidx].y = mtx._42 + 1.0f;
//	pos[svidx].z = mtx._43;
//
//	svidx++;
//	if (svidx > zaxis.size() - 1)//100�𒴂����Ƃ��@�����l�ɖ߂�
//	{
//		svidx = 0;
//		firstflag = true;
//	}
//
//	//�R�O�t���[���O�̏����g�p���J�������쐬
//	int useidx;
//	useidx = svidx - 10;//�g���J�����͕ۑ��ʒu���30�O
//	if (useidx < 0)//�R�O��������0�ȉ��ɂȂ�����
//	{
//		if (firstflag == false)//�ŏ��̂R�O�t���[��
//		{
//			useidx = 0;
//		}
//		else {
//			useidx = svidx + zaxis.size() - 10;
//		}
//	}
//
//	XMFLOAT3 eye;
//	XMFLOAT3 lookat;
//	XMFLOAT3 up;
//
//	lookat = pos[useidx];
//
//	eye.x = pos[useidx].x - 10 * zaxis[useidx].x;
//	eye.y = pos[useidx].y - 10 * zaxis[useidx].y;
//	eye.z = pos[useidx].z - 10 * zaxis[useidx].z;
//
//	//eye.x = LeapID(pos[useidx].x - 30, pos[useidx].x,1.0f);
//	//eye.y = LeapID(pos[useidx].y - 30, pos[useidx].y,1.0f);
//	//eye.z = LeapID(pos[useidx].z - 30, pos[useidx].z,1.0f);
//	up = yaxis[useidx];
//
//	//�J�����N���X�ɃZ�b�g
//	CCamera::GetInstance()->SetLookat(lookat);///�����_���Z�b�g
//	CCamera::GetInstance()->SetEye(eye);//�J�����̈ʒu���Z�b�g
//	CCamera::GetInstance()->SetUp(up);//�J�����̏�������Z�b�g
//
//	CCamera::GetInstance()->CreateCameraMatrix();//�r���[�ϊ��s����쐬
//
//}