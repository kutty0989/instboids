//=============================================================================
//
// obb�����N���X [obb.cpp]
//
//=============================================================================
#include	"obb.h"
#include	"CDirectxGraphics.h"
#include	"dx11mathutil.h"
#include	"CBox.h"
#include"DatFileLoader.h"
#include	"DX11Settransform.h"
#include	"CBBoxGenerater.h"

using namespace DirectX;


COBB::COBB() {
	DX11MtxIdentity(m_matworld);	// �P�ʍs��
	m_name = "";
}

COBB::~COBB() {
	Exit();
}

bool COBB::CompareLength(
	const OBB& boxA,
	const OBB& boxB,
	const XMFLOAT3& vecSeparate,		// ������
	const XMFLOAT3& vecDistance)
{
	float fDistance;

	// �������Ɏˉe�������S�Ԃ����ԃx�N�g��
	DX11Vec3Dot(fDistance, vecDistance, vecSeparate);	// ���ς��v�Z
	fDistance = fabsf(fDistance);		// ��Βl

	//��������Ƀ{�b�N�XA���ˉe�����e�̒���
	float fShadowA = 0;

	//��������Ƀ{�b�N�X�a���ˉe�����e�̒���
	float fShadowB = 0;

	//�{�b�N�XA�́h�e�h���Z�o
	float fShadowAx;
	float fShadowAy;
	float fShadowAz;

	// X���𕪗����Ɏˉe
	DX11Vec3Dot(fShadowAx, vecSeparate, boxA.vecAxisX);
	fShadowAx = fabsf(fShadowAx * (boxA.fLengthX / 2));

	// Y���𕪗����Ɏˉe
	DX11Vec3Dot(fShadowAy, vecSeparate, boxA.vecAxisY);
	fShadowAy = fabsf(fShadowAy * (boxA.fLengthY / 2));

	// Z���𕪗����Ɏˉe
	DX11Vec3Dot(fShadowAz, vecSeparate, boxA.vecAxisZ);
	fShadowAz = fabsf(fShadowAz * (boxA.fLengthZ / 2));

	fShadowA = fShadowAx + fShadowAy + fShadowAz;

	//�{�b�N�XB�́h�e�h���Z�o
	float fShadowBx;
	float fShadowBy;
	float fShadowBz;

	// X���𕪗����Ɏˉe
	DX11Vec3Dot(fShadowBx, vecSeparate, boxB.vecAxisX);
	fShadowBx = fabsf(fShadowBx * (boxB.fLengthX / 2));

	// Y���𕪗����Ɏˉe
	DX11Vec3Dot(fShadowBy, vecSeparate, boxB.vecAxisY);
	fShadowBy = fabsf(fShadowBy * (boxB.fLengthY / 2));

	// Z���𕪗����Ɏˉe
	DX11Vec3Dot(fShadowBz, vecSeparate, boxB.vecAxisZ);
	fShadowBz = fabsf(fShadowBz * (boxB.fLengthZ / 2));

	fShadowB = fShadowBx + fShadowBy + fShadowBz;

	if (fDistance > fShadowA + fShadowB) {
		return false;
	}

	return true;
}

// ���_�Q����听�����͂��Ăn�a�a�����
void COBB::CalculateOBB(std::vector<XMFLOAT3>& vertices) {

	CBBoxGenerater	Generator;
	XMFLOAT4X4 mtx;
	XMFLOAT4X4 eigenmtx;

	// �����U�s����쐬
	mtx = Generator.GetCovarianceMatrix(vertices);

	// �ŗL�x�N�g�����v�Z�ŋ��߂�
	Generator.GetEigenVector(mtx, eigenmtx);

	// �ŗL�x�N�g������ɂ��Ăa�a�n�w���쐬
	m_obbinfo = Generator.CaclBBox(vertices, eigenmtx);

}

// ���_�Q����ŗL�x�N�g�����g�p����AABB�����
void COBB::CalculateBoundingBox(DatFileLoader* datdata) {

	int				numvertices;			// ���_��

	float* x;						// ���_���W�f�[�^
	float* y;						// ���_���W�f�[�^
	float* z;						// ���_���W�f�[�^

	float			minx, miny, minz;		// �ŏ��l�i�w�C�x�C�y�j
	float			maxx, maxy, maxz;		// �ő�l�i�w�C�x�A�y�j
	float			cx, cy, cz;				// ���S���W


	void* pVertices = NULL;

	numvertices = datdata->m_VertexSuu;		// ���_�����Q�b�g

											// ���_�����̍��W�i�[�G���A�m��
	x = new float[numvertices];
	y = new float[numvertices];
	z = new float[numvertices];

	// ���_�����ׂĎ��o��
	for (int i = 0; i < numvertices; i++)
	{
		x[i] = datdata->m_Vertex[i].m_Pos.x;	// �w���W�擾
		y[i] = datdata->m_Vertex[i].m_Pos.y;	// �x���W�擾
		z[i] = datdata->m_Vertex[i].m_Pos.z;	// �y���W�擾
	}

	// �w�x�y���ꂼ��ɂ��āA�ő�l�A�ŏ��l�����߂�
	for (int i = 0; i < numvertices; i++)
	{
		if (i == 0) {
			minx = maxx = x[i];
			miny = maxy = y[i];
			minz = maxz = z[i];
		}
		if (minx >= x[i]) minx = x[i];
		if (miny >= y[i]) miny = y[i];
		if (minz >= z[i]) minz = z[i];
		if (maxx <= x[i]) maxx = x[i];
		if (maxy <= y[i]) maxy = y[i];
		if (maxz <= z[i]) maxz = z[i];
	}

	cx = (maxx + minx) / 2;		// ���̒��S���W�����߂�
	cy = (maxy + miny) / 2;		// ���̒��S���W�����߂�
	cz = (maxz + minz) / 2;		// ���̒��S���W�����߂�

	float distance;
	float maxdistance = 0;

	// �S���_�ƒ��S���W�Ƃ̋��������߂�
	for (int i = 0; i < numvertices; i++)
	{
		// 2�_�Ԃ̋��������߂�
		distance = (x[i] - cx) * (x[i] - cx) + (y[i] - cy) * (y[i] - cy) + (z[i] - cz) * (z[i] - cz);
		if (maxdistance < distance) maxdistance = distance;
	}
	// �ő唼�a���v�Z
	maxdistance = sqrtf(maxdistance);
	delete[] z;
	delete[] y;
	delete[] x;

	m_obbinfo.currentcenter.x = cx;				// �a�a�n�w�̒��S���Z�b�g
	m_obbinfo.currentcenter.y = cy;
	m_obbinfo.currentcenter.z = cz;

	m_obbinfo.center.x = cx;					// �a�a�n�w�̒��S���Z�b�g
	m_obbinfo.center.y = cy;
	m_obbinfo.center.z = cz;

	// �������Z�b�g
	m_obbinfo.fLengthX = fabsf(maxx - minx);
	m_obbinfo.fLengthY = fabsf(maxy - miny);
	m_obbinfo.fLengthZ = fabsf(maxz - minz);

	// 3�����Z�b�g
	m_obbinfo.vecAxisX = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_obbinfo.vecAxisY = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_obbinfo.vecAxisZ = XMFLOAT3(0.0f, 0.0f, 1.0f);
}

void COBB::Update(DirectX::XMFLOAT4X4 mtxworld) {
	// �����Z�b�g
	m_obbinfo.vecAxisX = XMFLOAT3(mtxworld._11, mtxworld._12, mtxworld._13);
	m_obbinfo.vecAxisY = XMFLOAT3(mtxworld._21, mtxworld._22, mtxworld._23);
	m_obbinfo.vecAxisZ = XMFLOAT3(mtxworld._31, mtxworld._32, mtxworld._33);

	// �`��p�̍s����X�V
	m_matworld = mtxworld;

	// OBB�̒��S���W���X�V
	DX11Vec3MulMatrix(m_obbinfo.currentcenter, m_obbinfo.center, mtxworld);

	// ���݈ʒu��␳�iBBOX�̒��S�ƃ��f���̌��_�ʒu�͈قȂ邽�߁j
	m_matworld._41 = m_obbinfo.currentcenter.x;
	m_matworld._42 = m_obbinfo.currentcenter.y;
	m_matworld._43 = m_obbinfo.currentcenter.z;
}

void COBB::Draw() {
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, m_matworld);
	m_boxmesh.Draw();
}

bool COBB::Collision(COBB& obb) {
	//������
	XMFLOAT3 vecSeparate;

	// 2�̃I�u�W�F�N�g�����񂾃x�N�g�����v�Z
	XMFLOAT3 vecDistance;
	XMFLOAT3 obbpos = obb.GetPosition();
	vecDistance.x = m_obbinfo.currentcenter.x - obbpos.x;
	vecDistance.y = m_obbinfo.currentcenter.y - obbpos.y;
	vecDistance.z = m_obbinfo.currentcenter.z - obbpos.z;

	OBB boxB, boxA;
	boxA = this->GetOBB();
	boxB = obb.GetOBB();

	bool sts;			// �߂�l

	// OBB-A�����X�g
	XMFLOAT3* OBB_A_Axis[3] = {
			&boxA.vecAxisX,
			&boxA.vecAxisY,
			&boxA.vecAxisZ,
	};

	// OBB-B�����X�g
	XMFLOAT3* OBB_B_Axis[3] = {
		&boxB.vecAxisX,
		&boxB.vecAxisY,
		&boxB.vecAxisZ,
	};

	// OBB-A�̂R���𕪗����ɂ��ă`�F�b�N
	for (int i = 0;i < 3;i++) {
		vecSeparate.x = OBB_A_Axis[i]->x;
		vecSeparate.y = OBB_A_Axis[i]->y;
		vecSeparate.z = OBB_A_Axis[i]->z;

		DX11Vec3Normalize(vecSeparate, vecSeparate);	// ���K��

		sts = CompareLength(boxA,			// OBB-A
			boxB,							// OBB-B
			vecSeparate,					// ������
			vecDistance);					// �Q�̃I�u�W�F�N�g�����ԃx�N�g��
		if (sts == false) {
			return false;
		}
	}

	// OBB-B�̂R���𕪗����ɂ��ă`�F�b�N
	for (int i = 0;i < 3;i++) {
		vecSeparate.x = OBB_B_Axis[i]->x;
		vecSeparate.y = OBB_B_Axis[i]->y;
		vecSeparate.z = OBB_B_Axis[i]->z;

		DX11Vec3Normalize(vecSeparate, vecSeparate);	// ���K��

		sts = CompareLength(boxA,			// OBB-A
			boxB,							// OBB-B
			vecSeparate,					// ������
			vecDistance);					// �Q�̃I�u�W�F�N�g�����ԃx�N�g��
		if (sts == false) {
			return false;
		}
	}

	// �O�ς𕪗����Ƃ��Čv�Z
	for (int p1 = 0;p1 < 3;p1++) {
		for (int p2 = 0;p2 < 3;p2++) {
			XMFLOAT3	crossseparate;					// �O�σx�N�g��

			// �O�ς��v�Z����
			DX11Vec3Cross(crossseparate, *OBB_A_Axis[p1], *OBB_B_Axis[p2]);
			DX11Vec3Normalize(crossseparate, crossseparate);	// ���K��

			sts = CompareLength(
				boxA,				// OBB-A
				boxB,				// OBB-B
				crossseparate,		// ������
				vecDistance);		// �Q�̃I�u�W�F�N�g�����ԃx�N�g��
			if (sts == false) {
				return false;
			}
		}
	}

	return true;
}