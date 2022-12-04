#pragma once
#include	<assimp\Importer.hpp>
#include	<DirectXMath.h>

using namespace DirectX;

struct PLANE {
	float a, b, c, d;
};

/// <summary>
/// ���[���h�ϊ��s������
/// </summary>
/// <param name="mat">�ԋp�l</param>
/// <param name="angle">�ǂꂾ���X���Ă邩</param>
/// <param name="trans">���s�ړ��l</param>
void DX11MakeWorldMatrix(XMFLOAT4X4& mat, XMFLOAT3& angle, XMFLOAT3& trans);
/// <summary>
/// 3�����x�N�g�����s��
/// </summary>
/// <param name="outvec">�ϊ��l</param>
/// <param name="invec">�x�N�g��</param>
/// <param name="mat">�s��</param>
void DX11Vec3MulMatrix(DirectX::XMFLOAT3& outvec, const DirectX::XMFLOAT3& invec, const DirectX::XMFLOAT4X4& mat);
/// <summary>
/// �O�ς̌v�Z
/// </summary>
/// <param name="outvec">�O��</param>
/// <param name="invec1">�l�P</param>
/// <param name="invec2">�l�Q</param>
void DX11Vec3Cross(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec1, DirectX::XMFLOAT3& invec2);
/// <summary>
/// ���ς̌v�Z
/// </summary>
/// <param name="dot"></param>
/// <param name="invec1"></param>
/// <param name="invec2"></param>
void DX11Vec3Dot(float& dot, const DirectX::XMFLOAT3& invec1, const DirectX::XMFLOAT3& invec2);
/// <summary>
/// ���K������
/// </summary>
/// <param name="outvec"></param>
/// <param name="invec"></param>
void DX11Vec3Normalize(DirectX::XMFLOAT3& outvec, DirectX::XMFLOAT3& invec);
/// <summary>after
/// �P�ʍs��ɂ���
/// </summary>
/// <param name="mat">�P�ʍs��ɂ���s��</param>
void DX11MtxIdentity(DirectX::XMFLOAT4X4& mat);
/// <summary>
/// �s�񂩂�N�H�[�^�j�I�������@�p��
/// </summary>
/// <param name="mat">�s��</param>
/// <param name="qt">��������s��</param>
void DX11GetQtfromMatrix(const XMFLOAT4X4& mat, XMFLOAT4& qt);
/// <summary>
/// �w�莲�𒆐S�ɉ�]�����N�H�[�^�j�I���𐶐�
/// </summary>
/// <param name="qt">���������N�H�[�^�j�I��</param>
/// <param name="axis">��]��</param>
/// <param name="angle">��]�p�x</param>
void DX11QtRotationAxis(XMFLOAT4& qt, XMFLOAT4& axis, float angle);
/// <summary>
/// �N�H�[�^�j�I���Ȃǂ������@�|���Z
/// </summary>
/// <param name="outqt">������</param>
/// <param name="qt1">�l�P</param>
/// <param name="qt2">�l2</param>
void DX11QtMul(XMFLOAT4& outqt, const XMFLOAT4& qt1, const XMFLOAT4& qt2);
/// <summary>
/// �N�H�[�^�j�I������s����쐬
/// </summary>
/// <param name="outmtx">���������s��</param>
/// <param name="qt">�N�H�[�^�j�I��</param>
void DX11MtxFromQt(XMFLOAT4X4& outmtx, const XMFLOAT4& qt);
/// <summary>
/// �m�[�}���C�Y���@�������P��
/// </summary>
/// <param name="inqt">�������O</param>
/// <param name="outqt">��������</param>
void DX11QtNormalize(XMFLOAT4& inqt, XMFLOAT4& outqt);
/// <summary>
/// �x�N�g���̒��������߂�
/// </summary>
/// <param name="vec"></param>
/// <param name="length"></param>
void DX11Vec4Length(XMFLOAT4& vec, float& length);
/// <summary>
/// 2�_�Ԃ̋��������߂�
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="length"></param>
void DX11p2pLength(const XMFLOAT3& p1, const XMFLOAT3& p2, float& length);
/// <summary>
/// z,y,z�ɉ��������s�ړ�
/// </summary>
/// <param name="trans"></param>
/// <param name="matrix"></param>
void DX11MtxTranslation(const XMFLOAT3& trans, XMFLOAT4X4& matrix);
/// <summary>
/// �X���[�v�⊮�@���ʐ��`�⊮�@�e�ł���Ƒz��
/// </summary>
/// <param name="fromqt">�ŏ�</param>
/// <param name="toqt">�ړI�n</param>
/// <param name="t"></param>
/// <param name="ansqt">�o�Ă���N�H�[�^�j�I��</param>
void DX11QtSlerp(const XMFLOAT4& fromqt, const XMFLOAT4& toqt, float t, XMFLOAT4& ansqt);
/// <summary>
/// �P�ʃN�H�[�^�j�I����
/// </summary>
/// <param name="qt"></param>
void DX11QtIdentity(XMFLOAT4& qt);
/// <summary>
/// ���F�N�^�[�̒����𑪂�
/// </summary>
/// <param name="vec"></param>
/// <param name="length"></param>
void DX11Vec3Length(XMFLOAT3& vec, float& length);
/// <summary>
/// �w�莲�ŉ�]����s����쐬
/// </summary>
/// <param name="axis"></param>
/// <param name="angle"></param>
/// <param name="outmtx"></param>
void DX11MtxRotationAxis(const XMFLOAT3& axis, float angle, XMFLOAT4X4& outmtx);
/// <summary>
/// �s��̊|���Z
/// </summary>
/// <param name="ansmtx"></param>
/// <param name="p1mtx"></param>
/// <param name="p2mtx"></param>
void DX11MtxMultiply(XMFLOAT4X4& ansmtx, const XMFLOAT4X4& p1mtx, const XMFLOAT4X4& p2mtx);
bool IsInFrustum(const XMFLOAT3& pos, const XMFLOAT4X4& matrix);
void IsInFrustum(const XMFLOAT3& pos, const XMFLOAT4X4& matrix, float ans[]);
bool IsInFrustum(const XMFLOAT3& pos, const XMFLOAT4X4& matrix, float ans[], PLANE* plane);
bool IsInFrustum(
	const XMFLOAT3& pos,					// BS���S���W
	float radius,							// ���a
	const XMFLOAT4X4& matrix,				// �r���[�ϊ��s�񁖃v���W�F�N�V�����ϊ��s�� 
	float ans[],							// ���ʂƂ̋���
	bool  canseeflag[],						// �t���X�^�����ʂƂa�r�̊֌W
	PLANE* plane);							// ���ʕ�����;
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


float GetKakudo(float x, float y);//���A�����W����p�b�h�̊p�x�����߂�
float GetAtan(float x, float y);//���A�����W����p�x�����߂�
float GetcosC(float x, float y);//���A�����W����R�T�C�������߂�
float GetsinC(float x, float y);//���A�����W����T�C�������߂�

float persent(float bunbo, float bunsi);


