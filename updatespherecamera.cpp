#include <DirectXMath.h>
#include "CCamera.h"

//角度をラジアンに変更
inline float ToRad(float angle)
{
	return (angle * DirectX::XM_PI) / 180.0f;
}

//球面束縛カメラ（Z軸回転なしバージョン）

void UpdateSphereCamera(
	float radius,//半径
	float elevation,//仰角
	float azimuth,//方位角
	const DirectX::XMFLOAT3& lookat//注視点
)
{
	DirectX::XMFLOAT3 eye;//視点

	//仰角　方位角をラジアンに変換
	elevation = ToRad(elevation);
	azimuth = ToRad(azimuth);

	//仰角に応じた半径を計算
	float r = radius * sinf(elevation);

	//始点座標を計算
	eye.x = r * cosf(azimuth);
	eye.y = radius * cosf(elevation);
	eye.z = r * sinf(azimuth);

	//上向きベクトルを計算（仰角を90ど回転させるとできる）
	DirectX::XMFLOAT3 up;
	float elevationplus90 = elevation + ToRad(90.0f);//仰角を90度足す

	r = radius * sinf(elevationplus90);

	up.x = r * cosf(azimuth);
	up.y = radius * cosf(elevationplus90);
	up.z = r * sinf(azimuth);

	//始点ベクトルを注視点分平行移動
	eye.x += lookat.x;
	eye.y += lookat.y;
	eye.z += lookat.z;


	//ビュー変換行列を作成
	CCamera::GetInstance()->SetEye(eye);
	CCamera::GetInstance()->SetLookat(lookat);
	CCamera::GetInstance()->SetUp(up);
	CCamera::GetInstance()->CreateCameraMatrix();



}