//*****************************************************************************
//!	@file	collision.cpp
//!	@brief	
//!	@note	�����蔻��Ɏg�p���邽�߂̊֐��Q
//!	@author	
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	<math.h>
#include	<DirectXMath.h>
#include	<windows.h>
#include	"collision.h"
#include	"dx11mathutil.h"

//==============================================================================
//!	@fn		CreatePlaneInfo
//!	@brief�@���ʂ̕����������߂�i���_�͎��v���œn���j
//!	@param	���_�P���W
//!	@param	���_�Q���W
//!	@param	���_�R���W
//!	@param	���ʂ̕�����
//!	@retval	�Ȃ�
//==============================================================================
void CreatePlaneInfo(const XMFLOAT3& p1,
	const XMFLOAT3& p2,
	const XMFLOAT3& p3,
	PLANE& plane)
{
	XMFLOAT3		p1p2;
	XMFLOAT3		p2p3;
	XMFLOAT3		normal;

	p1p2.x = p2.x - p1.x;
	p1p2.y = p2.y - p1.y;
	p1p2.z = p2.z - p1.z;

	p2p3.x = p3.x - p2.x;
	p2p3.y = p3.y - p2.y;
	p2p3.z = p3.z - p2.z;

	DX11Vec3Cross(normal, p1p2, p2p3);

	DX11Vec3Normalize(normal, normal);

	plane.a = normal.x;
	plane.b = normal.y;
	plane.c = normal.z;

	plane.d = -(plane.a * p1.x + plane.b * p1.y + plane.c * p1.z);
}

//==============================================================================
//!	@fn		LinetoPlaneCross
//!	@brief�@�����ƕ��ʂ̌�_�����߂�
//!	@param	���ʂ̕�����
//!	@param	�����̋N�_
//!	@param	�����̕����x�N�g��
//!	@param	��_���W
//!	@retval	true ��_����@false ��_�Ȃ�
//==============================================================================
bool LinetoPlaneCross(const PLANE& plane,		//���ʂ̕�����
	const XMFLOAT3& p0,						//�����̋N�_
	const XMFLOAT3& wv,						//�����̕����x�N�g��
	XMFLOAT3& ans)					//��_���W
{
	float t = 0;

	XMFLOAT3 normal;				// ���ʂ̖@���x�N�g���i���K���ς݁j
	normal.x = plane.a;
	normal.y = plane.b;
	normal.z = plane.c;

	float dot;			// ����
	// ���s�`�F�b�N(���ς��v�Z����)
	DX11Vec3Dot(dot, normal, wv);
	if (fabsf(dot) < FLT_EPSILON) {
		MessageBox(nullptr, "���s�ł��B", "���s�ł��B", MB_OK);
		return false;
	}

	float dot2;			// ���q
	DX11Vec3Dot(dot2, normal, p0);

	// �����ɂ������߂鎮������i���K���j
	t = -(dot2 + plane.d) / dot;

	ans.x = p0.x + wv.x * t;
	ans.y = p0.y + wv.y * t;
	ans.z = p0.z + wv.z * t;
	return true;
}

//==============================================================================
//!	@fn		CheckInTriangle
//!	@brief�@�R�p�`�̓����ɂ��邩�ǂ����𔻒�
//!	@param	�R�p�`�̑�P���_���W
//!	@param	�R�p�`�̑�Q���_���W
//!	@param	�R�p�`�̑�R���_���W
//!	@param	���肵�������_���W
//!	@retval	true �����@false �O��
//==============================================================================
bool CheckInTriangle(const XMFLOAT3& a,
	const XMFLOAT3& b,
	const XMFLOAT3& c,
	const XMFLOAT3& p) {
	XMFLOAT3	ab, bc, ca;			// �R�ӂ̃x�N�g��
	XMFLOAT3	ap, bp, cp;			// �����̓_�Ƃ̃x�N�g��
	XMFLOAT3	normal;				// �R�p�`�̖@���x�N�g��
	XMFLOAT3	n1, n2, n3;			// �R�ӂƓ����̓_�Ƃ̖@���x�N�g��

	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	ab.z = b.z - a.z;

	bc.x = c.x - b.x;
	bc.y = c.y - b.y;
	bc.z = c.z - b.z;

	ca.x = a.x - c.x;
	ca.y = a.y - c.y;
	ca.z = a.z - c.z;

	ap.x = p.x - a.x;
	ap.y = p.y - a.y;
	ap.z = p.z - a.z;

	bp.x = p.x - b.x;
	bp.y = p.y - b.y;
	bp.z = p.z - b.z;

	cp.x = p.x - c.x;
	cp.y = p.y - c.y;
	cp.z = p.z - c.z;

	DX11Vec3Cross(normal, ab, bc);			// �O�ς��v�Z

	DX11Vec3Cross(n1, ab, ap);				// �O�ς��v�Z

	DX11Vec3Cross(n2, bc, bp);				// �O�ς��v�Z

	DX11Vec3Cross(n3, ca, cp);				// �O�ς��v�Z

	float dot;
	DX11Vec3Dot(dot, n1, normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p
	DX11Vec3Dot(dot, n2, normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p
	DX11Vec3Dot(dot, n3, normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p

	return true;
}

//******************************************************************************
//	End of file.
//******************************************************************************
