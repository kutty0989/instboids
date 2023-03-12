#pragma once
//=============================================================================
//
// �����蔻����g���₷�����邽�߂̊֐��N���X [collision.h]
//
//=============================================================================
#include	<DirectXMath.h>
#include	"dx11mathutil.h"

// �v���g�^�C�v�錾
void CreatePlaneInfo(const DirectX::XMFLOAT3& p1, const DirectX::XMFLOAT3& p2, const DirectX::XMFLOAT3& p3, PLANE& plane);

bool LinetoPlaneCross(const PLANE& plane,		//���ʂ̕�����
	const DirectX::XMFLOAT3& line_o,	//�������ʂ�_
	const DirectX::XMFLOAT3& line_v,	//�����̕����x�N�g��
	DirectX::XMFLOAT3& ans);		//��_���W

bool CheckInTriangle(const DirectX::XMFLOAT3& a,
	const DirectX::XMFLOAT3& b,
	const DirectX::XMFLOAT3& c,
	const DirectX::XMFLOAT3& p);

