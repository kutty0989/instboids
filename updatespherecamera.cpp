#include <DirectXMath.h>
#include "CCamera.h"

//�p�x�����W�A���ɕύX
inline float ToRad(float angle)
{
	return (angle * DirectX::XM_PI) / 180.0f;
}

//���ʑ����J�����iZ����]�Ȃ��o�[�W�����j

void UpdateSphereCamera(
	float radius,//���a
	float elevation,//�p
	float azimuth,//���ʊp
	const DirectX::XMFLOAT3& lookat//�����_
)
{
	DirectX::XMFLOAT3 eye;//���_

	//�p�@���ʊp�����W�A���ɕϊ�
	elevation = ToRad(elevation);
	azimuth = ToRad(azimuth);

	//�p�ɉ��������a���v�Z
	float r = radius * sinf(elevation);

	//�n�_���W���v�Z
	eye.x = r * cosf(azimuth);
	eye.y = radius * cosf(elevation);
	eye.z = r * sinf(azimuth);

	//������x�N�g�����v�Z�i�p��90�ǉ�]������Ƃł���j
	DirectX::XMFLOAT3 up;
	float elevationplus90 = elevation + ToRad(90.0f);//�p��90�x����

	r = radius * sinf(elevationplus90);

	up.x = r * cosf(azimuth);
	up.y = radius * cosf(elevationplus90);
	up.z = r * sinf(azimuth);

	//�n�_�x�N�g���𒍎��_�����s�ړ�
	eye.x += lookat.x;
	eye.y += lookat.y;
	eye.z += lookat.z;


	//�r���[�ϊ��s����쐬
	CCamera::GetInstance()->SetEye(eye);
	CCamera::GetInstance()->SetLookat(lookat);
	CCamera::GetInstance()->SetUp(up);
	CCamera::GetInstance()->CreateCameraMatrix();



}