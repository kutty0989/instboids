#pragma once
//=============================================================================
//
// obb�����N���X [obb.h]
//
//=============================================================================
#include	<DirectXMath.h>
#include	<string>
#include	"CBox.h"
#include"DatFileLoader.h"

// OBB�p�\����
struct OBB {
	DirectX::XMFLOAT3	vecAxisX;		// X��
	DirectX::XMFLOAT3	vecAxisY;		// Y��
	DirectX::XMFLOAT3	vecAxisZ;		// Z��
	DirectX::XMFLOAT3	center;			// ���S���W�i���[�J�����W�n�j
	DirectX::XMFLOAT3	currentcenter;	// BBOX�̌��݈ʒu
	float	fLengthX;					// �a�a�n�w �w�T�C�Y	
	float	fLengthY;					// �a�a�n�w �x�T�C�Y
	float	fLengthZ;					// �a�a�n�w �y�T�C�Y
};

class COBB
{
private:
	std::string		m_name;				// ���O�i�{�[�������Z�b�g�j
	OBB				m_obbinfo;			// OBB BBOX���
	DirectX::XMFLOAT4X4	m_matworld;		// OBB �`��p���[���h�ϊ��s��
	CBox			m_boxmesh;			// BBOX mesh

	//bool CompareLength(OBB* pboxA,OBB* pboxB,D3DXVECTOR3* pvecSeparate,D3DXVECTOR3* pvecDistance)
	//�u�����v���u�Q�̉e�̍��v�v���傫���ꍇ�i��Փˁj��FALSE  ���������������ꍇ�i�Փˁj��TRUE
	// ���̊֐��́AOBBCollisionDetection�֐��݂̂ɌĂяo�����T�u���[�`��
	bool CompareLength(
		const OBB& pboxA,
		const OBB& pboxB,
		const DirectX::XMFLOAT3& pvecSeparate,		// ������
		const DirectX::XMFLOAT3& pvecDistance);		// �Q�̃I�u�W�F�N�g�����ԃx�N�g��

	void CalculateBoundingBox(DatFileLoader* datdata);		// AABB�����߂�

public:
	COBB();

	~COBB();

	void Init(DatFileLoader* datdata) {
		CalculateBoundingBox(datdata);	// OBB�쐬
		CreateBoxMesh();				// ���b�V���쐬
	}

	void Exit() {
		m_boxmesh.Exit();
	}

	void Update(DirectX::XMFLOAT4X4 matworld);

	void Draw();

	bool Collision(COBB& obb);

	DirectX::XMFLOAT3 GetPosition() {
		return m_obbinfo.currentcenter;
	}

	OBB GetOBB() {
		return m_obbinfo;
	}

	void CalculateOBB(std::vector<XMFLOAT3>& vertex);		// ���_�Q����ŗL�x�N�g�����g�p���Ăn�a�a�����

	void CreateBoxMesh() {
		m_boxmesh.Init(
			m_obbinfo.fLengthX,
			m_obbinfo.fLengthY,
			m_obbinfo.fLengthZ
		);
	}

	void SetName(std::string name) {
		m_name = name;
	}

	std::string& GetName() {
		return m_name;
	}

	void SetColor(DirectX::XMFLOAT4 col) {
		m_boxmesh.SetColor(col);
	}

	XMFLOAT4 GetColor() {
		return m_boxmesh.GetColor();
	}
};