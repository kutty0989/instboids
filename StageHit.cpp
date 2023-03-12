//=============================================================================
//
// �X�e�[�W�Ƃ̓����蔻��N���X [StageHit.cpp]
//
//=============================================================================

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	<DirectXMath.h>
#include	"StageHit.h"
#include	"collision.h"
#include	"CModel.h"
#include"CHeight_Map.h"
using namespace DirectX;

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
PLANEINFO* g_PlaneInfo = nullptr;				// ���ʃ|���S�����
int				g_NumFaces;							// �O�p�`�|���S����

//==============================================================================
//!	@fn		StageHitInit
//!	@brief�@�n�`�Ƃ̓����蔻�菉��������
//!	@param  CModel�|�C���^
//!	@param	�f�o�C�X�I�u�W�F�N�g
//!	@retval	�Ȃ�
//==============================================================================
void StageHitInit(CHeight_Map* pmodel) {

	//std::vector<XMFLOAT3> vertices;		// ���_�f�[�^
	//std::vector<int> indices;			// �C���f�b�N�X�f�[�^

	//const ModelData& md = pmodel->GetModelData();
	//const std::vector<Mesh>& meshes = md.GetMeshes();

	//// ���_�f�[�^�����o��
	//for (auto m : meshes) {
	//	for (auto v : m.m_vertices) {
	//		vertices.emplace_back(v.m_Pos);
	//	}
	//}

	//// �C���f�b�N�X�f�[�^�����o��
	//for (auto m : meshes) {
	//	for (auto idx : m.m_indices) {
	//		indices.emplace_back(idx);
	//	}
	//}

	// ���ʂ̕��������쐬
//	CreateStagePlaneInfoAll(vertices, indices);
}

//==============================================================================
//!	@fn		StageHitExit
//!	@brief�@�n�`�Ƃ̓����蔻��I������
//!	@retval	�Ȃ�
//==============================================================================
void StageHitExit() {
	if (g_PlaneInfo != nullptr) {
		delete[] g_PlaneInfo;
	}
}

//==============================================================================
//!	@fn		CreateStagePlaneInfoAll
//!	@brief�@�w�肳�ꂽ���b�V���̃|���S���ɂ��ē����蔻����s�����߂̕��ʕ��������𐶐�����
//!	@param	���b�V��
//!	@param	�f�o�C�X�I�u�W�F�N�g
//!	@retval	�Ȃ�
//==============================================================================
/*
void CreateStagePlaneInfoAll(DatFileLoader*	datfiledata)
{
	X::Vertex*				pVertices;						// ���_���i�[�p

	unsigned int*			pIndices;						// �C���f�b�N�X�ԍ�
	int						idx0, idx1, idx2;				// �R�p�`�|���S���̒��_�C���f�b�N�X�i�[�p

	pIndices = datfiledata->m_Index;

	pVertices = datfiledata->m_Vertex;

	// �w�x�y�̍��W�������܂܂�郁�b�V���N���[�����쐬
	g_NumFaces = datfiledata->m_IndexSuu / 3;		// �R�p�`���擾

	g_PlaneInfo = new PLANEINFO[g_NumFaces];		// �ʐ����m��

	// �|���S���������[�v
	for (int i = 0; i<g_NumFaces; i++){
		idx0 = *pIndices++;							// �R�p�`�|���S���̒��_�C���f�b�N�X�擾�i�O�Ԗځj
		idx1 = *pIndices++;							// �R�p�`�|���S���̒��_�C���f�b�N�X�擾�i�P�Ԗځj
		idx2 = *pIndices++;							// �R�p�`�|���S���̒��_�C���f�b�N�X�擾�i�Q�Ԗځj

		g_PlaneInfo[i].p0.x = (pVertices + idx0)->m_Pos.x;
		g_PlaneInfo[i].p0.y = (pVertices + idx0)->m_Pos.y;
		g_PlaneInfo[i].p0.z = (pVertices + idx0)->m_Pos.z;

		g_PlaneInfo[i].p1.x = (pVertices + idx1)->m_Pos.x;
		g_PlaneInfo[i].p1.y = (pVertices + idx1)->m_Pos.y;
		g_PlaneInfo[i].p1.z = (pVertices + idx1)->m_Pos.z;

		g_PlaneInfo[i].p2.x = (pVertices + idx2)->m_Pos.x;
		g_PlaneInfo[i].p2.y = (pVertices + idx2)->m_Pos.y;
		g_PlaneInfo[i].p2.z = (pVertices + idx2)->m_Pos.z;

		//���ʂ̕��������쐬����
		CreatePlaneInfo(g_PlaneInfo[i].p0, g_PlaneInfo[i].p1, g_PlaneInfo[i].p2, g_PlaneInfo[i].plane);
	}
}
*/

//==============================================================================
//!	@fn		CreateStagePlaneInfoAll
//!	@brief�@�w�肳�ꂽ���b�V���̃|���S���ɂ��ē����蔻����s�����߂̕��ʕ��������𐶐�����
//!	@param	���_�f�[�^
//!	@param	�C���f�b�N�X�f�[�^
//!	@retval	�Ȃ�
//==============================================================================
void CreateStagePlaneInfoAll(std::vector<XMFLOAT3>& vertices, std::vector<int>& indices) {

	g_NumFaces = indices.size() / 3;				// �R�p�`���v�Z

	g_PlaneInfo = new PLANEINFO[g_NumFaces];		// �ʐ����m��

	// �ʐ������[�v
	for (int facecnt = 0; facecnt < g_NumFaces; facecnt++) {

		g_PlaneInfo[facecnt].p0.x = vertices[indices[facecnt * 3]].x;
		g_PlaneInfo[facecnt].p0.y = vertices[indices[facecnt * 3]].y;
		g_PlaneInfo[facecnt].p0.z = vertices[indices[facecnt * 3]].z;

		g_PlaneInfo[facecnt].p1.x = vertices[indices[facecnt * 3 + 1]].x;
		g_PlaneInfo[facecnt].p1.y = vertices[indices[facecnt * 3 + 1]].y;
		g_PlaneInfo[facecnt].p1.z = vertices[indices[facecnt * 3 + 1]].z;

		g_PlaneInfo[facecnt].p2.x = vertices[indices[facecnt * 3 + 2]].x;
		g_PlaneInfo[facecnt].p2.y = vertices[indices[facecnt * 3 + 2]].y;
		g_PlaneInfo[facecnt].p2.z = vertices[indices[facecnt * 3 + 2]].z;

		//���ʂ̕��������쐬����
		CreatePlaneInfo(g_PlaneInfo[facecnt].p0, g_PlaneInfo[facecnt].p1, g_PlaneInfo[facecnt].p2, g_PlaneInfo[facecnt].plane);
	}
}

//==============================================================================
//!	@fn		SearchAllSurface
//!	@brief�@�w�肳�ꂽ���b�V�����ׂĂ̂R�p�`�|���S���ɂ��Ă̌�_�����߂�
//!	@param	�w���W
//!	@param	�y���W
//!	@param	��_
//!	@retval	true ��_���� false ��_�Ȃ�
//==============================================================================
bool SearchAllSurface(float x, float z, XMFLOAT3& ans) {

	XMFLOAT3		DownVector(0, 1, 0);				// �����̕����x�N�g��
	XMFLOAT3		CrossPoint;							// ��_
	XMFLOAT3		CurrentPosition(x, 0, z);			// ���݈ʒu�i�������Ȃ��j

	bool FindFlag = false;								// �|���S���������������ǂ���
	bool status;

	// �S�|���S���������[�v
	for (int i = 0; i < g_NumFaces; i++) {
		// ���ʂƒ����̌�_�����߂�
		status = LinetoPlaneCross(g_PlaneInfo[i].plane,	//���ʂ̕�����
			CurrentPosition,							//�����̋N�_�i���̌��݈ʒu�j
			DownVector,									//�����̕����x�N�g��
			CrossPoint);								//��_���W
		if (status) {
			// ��_���R�p�`�̓����ɂ��邩�H
			if (CheckInTriangle(g_PlaneInfo[i].p0, g_PlaneInfo[i].p1, g_PlaneInfo[i].p2, CrossPoint)) {
				CurrentPosition.y = CrossPoint.y;
				FindFlag = true;
				break;
			}
		}
	}
	if (FindFlag) {
		ans = CurrentPosition;
		return true;
	}
	else {
		return false;
	}
}

//******************************************************************************
//	End of file.
//******************************************************************************