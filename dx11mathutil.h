#pragma once
#include	<assimp\Importer.hpp>
#include	<DirectXMath.h>

using namespace DirectX;

struct PLANE {
	float a, b, c, d;
};

/// <summary>
/// ワールド変換行列を作る
/// </summary>
/// <param name="mat">返却値</param>
/// <param name="angle">どれだけ傾いてるか</param>
/// <param name="trans">平行移動値</param>
void DX11MakeWorldMatrix(XMFLOAT4X4& mat, XMFLOAT3& angle, XMFLOAT3& trans);
/// <summary>
/// 3次元ベクトル＊行列
/// </summary>
/// <param name="outvec">変換値</param>
/// <param name="invec">ベクトル</param>
/// <param name="mat">行列</param>
void DX11Vec3MulMatrix(DirectX::XMFLOAT3& outvec, const DirectX::XMFLOAT3& invec, const DirectX::XMFLOAT4X4& mat);
/// <summary>
/// 外積の計算
/// </summary>
/// <param name="outvec">外積</param>
/// <param name="invec1">値１</param>
/// <param name="invec2">値２</param>
void DX11Vec3Cross(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec1, DirectX::XMFLOAT3& invec2);
/// <summary>
/// 内積の計算
/// </summary>
/// <param name="dot"></param>
/// <param name="invec1"></param>
/// <param name="invec2"></param>
void DX11Vec3Dot(float& dot, const DirectX::XMFLOAT3& invec1, const DirectX::XMFLOAT3& invec2);
/// <summary>
/// 正規化する
/// </summary>
/// <param name="outvec"></param>
/// <param name="invec"></param>
void DX11Vec3Normalize(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec);
/// <summary>after
/// 単位行列にする
/// </summary>
/// <param name="mat">単位行列にする行列</param>
void DX11MtxIdentity(DirectX::XMFLOAT4X4& mat);
/// <summary>
/// 行列からクォータニオンを作る　姿勢
/// </summary>
/// <param name="mat">行列</param>
/// <param name="qt">生成する行列</param>
void DX11GetQtfromMatrix(const XMFLOAT4X4& mat, XMFLOAT4& qt);
/// <summary>
/// 指定軸を中心に回転したクォータニオンを生成
/// </summary>
/// <param name="qt">生成されるクォータニオン</param>
/// <param name="axis">回転軸</param>
/// <param name="angle">回転角度</param>
void DX11QtRotationAxis(XMFLOAT4& qt, XMFLOAT4& axis, float angle);
/// <summary>
/// クォータニオンなどを合成　掛け算
/// </summary>
/// <param name="outqt">生成物</param>
/// <param name="qt1">値１</param>
/// <param name="qt2">値2</param>
void DX11QtMul(XMFLOAT4& outqt, const XMFLOAT4& qt1, const XMFLOAT4& qt2);
/// <summary>
/// クォータニオンから行列を作成
/// </summary>
/// <param name="outmtx">生成される行列</param>
/// <param name="qt">クォータニオン</param>
void DX11MtxFromQt(XMFLOAT4X4& outmtx, const XMFLOAT4& qt);
/// <summary>
/// ノーマライズ化　長さを１に
/// </summary>
/// <param name="inqt">初期化前</param>
/// <param name="outqt">初期化後</param>
void DX11QtNormalize(XMFLOAT4& inqt, XMFLOAT4& outqt);
/// <summary>
/// ベクトルの長さを求める
/// </summary>
/// <param name="vec"></param>
/// <param name="length"></param>
void DX11Vec4Length(XMFLOAT4& vec, float& length);
/// <summary>
/// 2点間の距離を求める
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="length"></param>
void DX11p2pLength(const XMFLOAT3& p1, const XMFLOAT3& p2, float& length);
/// <summary>
/// z,y,zに沿った平行移動
/// </summary>
/// <param name="trans"></param>
/// <param name="matrix"></param>
void DX11MtxTranslation(const XMFLOAT3& trans, XMFLOAT4X4& matrix);
/// <summary>
/// スラープ補完　球面線形補完　弾であると想定
/// </summary>
/// <param name="fromqt">最初</param>
/// <param name="toqt">目的地</param>
/// <param name="t"></param>
/// <param name="ansqt">出てくるクォータニオン</param>
void DX11QtSlerp(const XMFLOAT4& fromqt, const XMFLOAT4& toqt, float t, XMFLOAT4& ansqt);
/// <summary>
/// 単位クォータニオンに
/// </summary>
/// <param name="qt"></param>
void DX11QtIdentity(XMFLOAT4& qt);
/// <summary>
/// ヴェクターの長さを測る
/// </summary>
/// <param name="vec"></param>
/// <param name="length"></param>
void DX11Vec3Length(XMFLOAT3& vec, float& length);
/// <summary>
/// 指定軸で回転する行列を作成
/// </summary>
/// <param name="axis"></param>
/// <param name="angle"></param>
/// <param name="outmtx"></param>
void DX11MtxRotationAxis(const XMFLOAT3& axis, float angle, XMFLOAT4X4& outmtx);
/// <summary>
/// 行列の掛け算
/// </summary>
/// <param name="ansmtx"></param>
/// <param name="p1mtx"></param>
/// <param name="p2mtx"></param>
void DX11MtxMultiply(XMFLOAT4X4& ansmtx, const XMFLOAT4X4& p1mtx, const XMFLOAT4X4& p2mtx);
bool IsInFrustum(const XMFLOAT3& pos, const XMFLOAT4X4& matrix);
void IsInFrustum(const XMFLOAT3& pos, const XMFLOAT4X4& matrix, float ans[]);
bool IsInFrustum(const XMFLOAT3& pos, const XMFLOAT4X4& matrix, float ans[], PLANE* plane);
bool IsInFrustum(
	const XMFLOAT3& pos,					// BS中心座標
	float radius,							// 半径
	const XMFLOAT4X4& matrix,				// ビュー変換行列＊プロジェクション変換行列 
	float ans[],							// 平面との距離
	bool  canseeflag[],						// フラスタム平面とＢＳの関係
	PLANE* plane);							// 平面方程式;
void GetPlanefromProjectionmatrix(PLANE* p, const XMFLOAT4X4& matrix);
void GetPlanefromProjectionmatrixWithNormalize(PLANE* p, const XMFLOAT4X4& matrix);
void DX11MtxInverse(XMFLOAT4X4& ansmtx, const XMFLOAT4X4& mtx);
void DX11MtxTranspose(XMFLOAT4X4& outmtx, const XMFLOAT4X4& inmtx);
void DX11MtxRotationX(float angle, XMFLOAT4X4& outmtx);
void DX11MtxRotationY(float angle, XMFLOAT4X4& outmtx);
void DX11MtxRotationZ(float angle, XMFLOAT4X4& outmtx);
void DX11MtxScale(float sx, float sy, float sz, XMFLOAT4X4& outmtx);
float haltonseq(unsigned int no, unsigned int base);
XMFLOAT4X4 DX11MtxaiToDX(aiMatrix4x4& aimtx);


float GetKakudo(float x, float y);//ｘ、ｙ座標からパッドの角度を求める
float GetAtan(float x, float y);//ｘ、ｙ座標から角度を求める
float GetcosC(float x, float y);//ｘ、ｙ座標からコサインを求める
float GetsinC(float x, float y);//ｘ、ｙ座標からサインを求める

float persent(float bunbo, float bunsi);


