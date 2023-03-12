//=============================================================================
//
// カメラの生成管理クラス [CCamera.cpp]
//
//=============================================================================
#include"CCamera.h"
#include"IMgui/imgui.h"
#include"BoidsAIMgr.h"
#include"CDirectInput.h"

bool CCamera::blowflg = false;
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

void CCamera::FPSCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
{
	//注視点を計算
	XMFLOAT3 lookat;
	lookat.x = pos.x + axisz.x;
	lookat.y = pos.y + axisz.y;
	lookat.z = pos.z + axisz.z;

	//カメラの位置を計算
	XMFLOAT3 eye;
	eye.x = pos.x;
	eye.y = pos.y;
	eye.z = pos.z;

	//カメラの上向きを計算
	XMFLOAT3 up;
	up.x = axisy.x;
	up.y = axisy.y;
	up.z = axisy.z;

	//カメラクラスにセット
	CCamera::GetInstance()->SetLookat(lookat);///注視点をセット
	CCamera::GetInstance()->SetEye(eye);//カメラの位置をセット
	CCamera::GetInstance()->SetUp(up);//カメラの上向きをセット


	CCamera::GetInstance()->CreateCameraMatrix();//ビュー変換行列を作成

}

static float cameratime;
float maxtime = 100;
static float nowtime = 0;

void CCamera::TPSCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
{
	static float a = 0.0f;
	static float b = 0.0f;
	static float c = 0.0f;

	static float x = 0.0f;
	static float y = 0.0f;
	static float z = 0.0f;

	static int cnt = 10;

	//カメラの位置を計算
	XMFLOAT3 eye;
	eye.x = 0 + a;
	eye.y = 1300.0f + b;
	eye.z = -240.0f + c;


	XMFLOAT3 lookat;
	lookat.x = x + eye.x;
	lookat.y =  y - 100 + eye.y;
	lookat.z = z + 40 + eye.z;

	
	if (nowtime == maxtime)
	{
		nowtime = 0;
	}

	cameratime = nowtime / maxtime;
	//a = sinf(cameratime);
	//c = cosf(cameratime);
	//a *= 1500;
	//c *= -1500;
	//b = LeapID<float>(a - 10, a + 10, cameratime);
	/*if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_O))
	{
		
		nowtime++;
	
	}
	a = sinf(cameratime);
	c = cosf(cameratime);
	a *= 1500.0f;
	c *= 1500.0f;*/
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

	/*bool rhythm = BoidsAIMgr::GetInstance()->rhythm_checker;
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

	//カメラの上向きを計算
	XMFLOAT3 up;
	up.x = 0;
	up.y = 0;
	up.z = 1;


		//カメラクラスにセット
		CCamera::GetInstance()->SetLookat(lookat);///注視点をセット
		CCamera::GetInstance()->SetEye(eye);//カメラの位置をセット
		CCamera::GetInstance()->SetUp(up);//カメラの上向きをセット

		CCamera::GetInstance()->CreateViewMatrix();
		CCamera::GetInstance()->CreateCameraMatrix();//ビュー変換行列を作成
	

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
		//	int it = BoidsAI::GetInstance()->iseconds % BoidsAI::GetInstance()->judge_seconds;

		float pos[3] = { a ,b,c };
		//float pos[3] = { BoidsAI::GetInstance()->GetPos().x, BoidsAI::GetInstance()->GetPos().y, BoidsAI::GetInstance()->GetPos().z};
		ImGui::DragFloat3("CAMERA ANGLE", pos);
		//ImGui::DragInt("notes", &it);
		a = pos[0];
		b = pos[1];
		c = pos[2];
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	//カメラの位置を計算
	XMFLOAT3 eye;
	eye.x = pos.x + a;
	eye.y = pos.y +b+ 450.0f;
	eye.z = pos.z +c + axisy.z -900.0f;


	//カメラの上向きを計算
	XMFLOAT3 up;
	up.x = axisz.x;
	up.y = axisz.y;
	up.z = axisz.z;


	//カメラクラスにセット
	CCamera::GetInstance()->SetLookat(lookat);///注視点をセット
	CCamera::GetInstance()->SetEye(eye);//カメラの位置をセット
	CCamera::GetInstance()->SetUp(up);//カメラの上向きをセット

	CCamera::GetInstance()->CreateCameraMatrix();//ビュー変換行列を作成

}

//固定注視カメラ
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
////ちょっとおくれてついてくるカメラ
//void CCamera::DelayCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy)
//{
//
//	//ビュー変換行列取得
//	static int svidx = 0;//保存位置を示すインデックスの値
//	static bool firstflag = false;//100個まで保存完了かを示すフラグ
//
//	static std::array<XMFLOAT3, 100> axisZ;//Z軸
//	axisz[svidx].x = mtx._31;
//	zaxis[svidx].y = mtx._32;
//	zaxis[svidx].z = mtx._33;
//
//	static std::array<XMFLOAT3, 100> yaxis;//Y軸
//	yaxis[svidx].x = mtx._21;
//	yaxis[svidx].y = mtx._22;
//	yaxis[svidx].z = mtx._23;
//
//
//	static std::array<XMFLOAT3, 100> pos;//現在位置
//	pos[svidx].x = mtx._41;
//	pos[svidx].y = mtx._42 + 1.0f;
//	pos[svidx].z = mtx._43;
//
//	svidx++;
//	if (svidx > zaxis.size() - 1)//100個を超えたとき　初期値に戻す
//	{
//		svidx = 0;
//		firstflag = true;
//	}
//
//	//３０フレーム前の情報を使用しカメラを作成
//	int useidx;
//	useidx = svidx - 10;//使うカメラは保存位置より30前
//	if (useidx < 0)//３０を引いて0以下になった時
//	{
//		if (firstflag == false)//最初の３０フレーム
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
//	//カメラクラスにセット
//	CCamera::GetInstance()->SetLookat(lookat);///注視点をセット
//	CCamera::GetInstance()->SetEye(eye);//カメラの位置をセット
//	CCamera::GetInstance()->SetUp(up);//カメラの上向きをセット
//
//	CCamera::GetInstance()->CreateCameraMatrix();//ビュー変換行列を作成
//
//}