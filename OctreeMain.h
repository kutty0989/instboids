#pragma once
#include"ColTrees.h"
#include <math.h>
#include <time.h>
#include"player.h"


// 2球衝突処理
void SphereColProc(Player* s1, Player* s2)
{
	float t = 0;
	XMFLOAT3 C1ColPos, C2ColPos, C1Velo, C2Velo;

	// 衝突している2円の衝突位置を検出
	if ()
		return;	// 衝突していないようです

	// 衝突位置を前位置として保存
	s1->p = C1ColPos;
	s2->p = C2ColPos;
	s1->Pre_p = C1ColPos;
	s2->Pre_p = C2ColPos;

	// 衝突後の速度を算出
	if (!CalcParticleColliAfterPos(
		&C1ColPos, &s1->v,
		&C2ColPos, &s2->v,
		s1->w, s2->w,
		g_Circle_Ref, g_Circle_Ref,		// 球の反発係数
		t,
		&C1ColPos, &C1Velo,
		&C2ColPos, &C2Velo))
		return; // 何か失敗したようです

	// 衝突後位置に移動
	s1->v = C1Velo;
	s2->v = C2Velo;
	s1->p += s1->v;
	s2->p += s2->v;
}







// 次の球の位置を取得
void GetNextSpherePos(SPHERE& s)
{
	D3DXVECTOR3 RefV;	// 反射後の速度ベクトル
	D3DXVECTOR3 ColliPos;	// 衝突位置
	float Res_time = 0.0f;	// 衝突後の移動可能時間

	// 重力を掛けて落とす
	s.v.y -= g_Gravity / 60;	// 1フレームで9.8/60(m/s)加速

	// 今の速度で位置を更新
	s.Pre_p = s.p;		// 前の位置を保存
	s.p += s.v;			// 位置更新

	// 壁との衝突をチェック
	// X左壁
	if (s.p.x < s.r && g_XLeft) {
		// 反射後の速度ベクトルを取得
		GetRefrectVelo(&RefV, D3DXVECTOR3(1, 0, 0), s.v, Wall_Ref);
		// 残り時間算出
		Res_time = (s.p.x - s.r) / s.v.x;
		// 反射後の位置を算出
		GetRelectedPos(Res_time, s, RefV);
	}
	// X右壁
	else if (s.p.x > 640 - s.r && g_XRight) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(-1, 0, 0), s.v, Wall_Ref);
		Res_time = (s.p.x - 640 + s.r) / s.v.x;
		GetRelectedPos(Res_time, s, RefV);
	}
	// Z手前壁
	if (s.p.z < s.r && g_ZNear) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(0, 0, 1), s.v, Wall_Ref);
		Res_time = (s.p.z - s.r) / s.v.z;
		GetRelectedPos(Res_time, s, RefV);
	}
	// Z奥壁
	else if (s.p.z > 640 - s.r && g_ZFar) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(0, 0, -1), s.v, Wall_Ref);
		Res_time = (s.p.z - 640 + s.r) / s.v.z;
		GetRelectedPos(Res_time, s, RefV);
	}
	// Y下壁
	else if (s.p.y < s.r) {
		GetRefrectVelo(&RefV, D3DXVECTOR3(0, 1, 0), s.v, Wall_Ref);
		Res_time = (s.p.y - s.r) / s.v.y;
		GetRelectedPos(Res_time, s, RefV);
	}
}