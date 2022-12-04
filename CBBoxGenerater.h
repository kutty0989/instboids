#pragma once
//========================================================
//CBBoxGenerater�N���X
//		�����X�L�����f���p��BBOX�̐������s�����߂̃N���X
//========================================================
#pragma once

class CBBoxGenerater
{
public:
	static const int N = 4;
	static const int MAX = 100;
	static const double TOL;
public:
	CBBoxGenerater(void);
	~CBBoxGenerater(void);

	// �����U�s����쐬����
	XMFLOAT4X4 GetCovarianceMatrix(std::vector<XMFLOAT3>& vertices);

	XMFLOAT4X4 GetCovarianceMatrix(
		XMFLOAT3* vertex,			// ���_�f�[�^�z�� 
		unsigned int* index,		// �{�[���ɉe�����󂯂钸�_�C���f�b�N�X�̔z��
		int numVertices);			// �{�[���ɉe�����󂯂钸�_��

	bool GetEigenVector(XMFLOAT4X4& a, XMFLOAT4X4& x);						// �ŗL�x�N�g�������߂�

	OBB CaclBBox(XMFLOAT3* vertex, unsigned int* index, int numVertices, XMFLOAT4X4 eigenmat);
	OBB CaclBBox(std::vector<XMFLOAT3>& vertices, XMFLOAT4X4 eigenmat);
};
