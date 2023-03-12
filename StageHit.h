#pragma once
//=============================================================================
//
// �X�e�[�W�Ƃ̓����蔻��N���X [StageHit.h]
//
//=============================================================================

#include	<DirectXMath.h>
#include	<vector>
#include	"CModel.h"
#include	"collision.h"

// �n�`�f�[�^�̖ʂ̕��������
struct PLANEINFO {
	PLANE		plane;					//���ʂ̕�����
	DirectX::XMFLOAT3	p0, p1, p2;		//���_���W
};
void StageHitInit(CModel* pmodel);
void StageHitExit();
void CreateStagePlaneInfoAll(std::vector<XMFLOAT3>& v, std::vector<int>& idx);
bool SearchAllSurface(float x, float z, DirectX::XMFLOAT3& ans);
