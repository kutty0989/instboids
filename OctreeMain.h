#pragma once
#include"ColTrees.h"
#include <math.h>
#include <time.h>
#include"player.h"


// 2���Փˏ���
void SphereColProc(Player* s1, Player* s2)
{
	float t = 0;
	XMFLOAT3 C1ColPos, C2ColPos, C1Velo, C2Velo;

	// �Փ˂��Ă���2�~�̏Փˈʒu�����o
	if ()
		return;	// �Փ˂��Ă��Ȃ��悤�ł�

	// �Փˈʒu��O�ʒu�Ƃ��ĕۑ�
	s1->p = C1ColPos;
	s2->p = C2ColPos;
	s1->Pre_p = C1ColPos;
	s2->Pre_p = C2ColPos;

	// �Փˌ�̑��x���Z�o
	if (!CalcParticleColliAfterPos(
		&C1ColPos, &s1->v,
		&C2ColPos, &s2->v,
		s1->w, s2->w,
		g_Circle_Ref, g_Circle_Ref,		// ���̔����W��
		t,
		&C1ColPos, &C1Velo,
		&C2ColPos, &C2Velo))
		return; // �������s�����悤�ł�

	// �Փˌ�ʒu�Ɉړ�
	s1->v = C1Velo;
	s2->v = C2Velo;
	s1->p += s1->v;
	s2->p += s2->v;
}







// ���̋��̈ʒu���擾
void GetNextSpherePos(SPHERE& s)
{
	D3DXVECTOR3 RefV;	// ���ˌ�̑��x�x�N�g��
	D3DXVECTOR3 ColliPos;	// �Փˈʒu
	float Res_time = 0.0f;	// �Փˌ�̈ړ��\����

	// �d�͂��|���ė��Ƃ�
	s.v.y -= g_Gravity / 60;	// 1�t���[����9.8/60(m/s)����

	// ���̑��x�ňʒu���X�V
	s.Pre_p = s.p;		// �O�̈ʒu��ۑ�
	s.p += s.v;			// �ʒu�X�V

	// �ǂƂ̏Փ˂��`�F�b�N
	// X����
	if (s.p.x < s.r && g_XLeft) {
		// ���ˌ�̑��x�x�N�g�����擾
		GetRefrectVelo(&RefV, D3DXVECTOR3(1, 0, 0), s.v, Wall_Ref);
		// �c�莞�ԎZ�o
		Res_time = (s.p.x - s.r) / s.v.x;
		// ���ˌ�̈ʒu���Z�o
		GetRelectedPos(Res_time, s, RefV);
	}
	// X�E��
	else if (s.p.x > 640 - s.r && g_XRight) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(-1, 0, 0), s.v, Wall_Ref);
		Res_time = (s.p.x - 640 + s.r) / s.v.x;
		GetRelectedPos(Res_time, s, RefV);
	}
	// Z��O��
	if (s.p.z < s.r && g_ZNear) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(0, 0, 1), s.v, Wall_Ref);
		Res_time = (s.p.z - s.r) / s.v.z;
		GetRelectedPos(Res_time, s, RefV);
	}
	// Z����
	else if (s.p.z > 640 - s.r && g_ZFar) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(0, 0, -1), s.v, Wall_Ref);
		Res_time = (s.p.z - 640 + s.r) / s.v.z;
		GetRelectedPos(Res_time, s, RefV);
	}
	// Y����
	else if (s.p.y < s.r) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(0, 1, 0), s.v, Wall_Ref);
		Res_time = (s.p.y - s.r) / s.v.y;
		GetRelectedPos(Res_time, s, RefV);
	}
}