#pragma once
//*****************************************************************************
//!	@file	CDirect3DXFile.h
//!	@brief	
//!	@note	dat�t�@�C���N���X
//!	@author
//*****************************************************************************
#pragma once

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	"DatFileLoader.h"

using namespace DirectX;

namespace X {
	// �萔�o�b�t�@��`�i�}�e���A���P�ʁj
	struct ConstantBufferMaterial {
		XMFLOAT4	AmbientMaterial;		// �����̔��˗�
		XMFLOAT4	DiffuseMaterial;		// �f�B�t���[�Y���̔��˗�
		XMFLOAT4	SpecularMaterial;		// �X�y�L�������̔��˗�
	};
}

//=============================================================================
//!	@class	CDirect3DXFile
//!	@brief	X�t�@�C���N���X
//=============================================================================
class DatFile {
private:
	DWORD						m_nummaterial;			// �}�e���A����
	ID3D11Buffer* m_pVertexBuffer;		// ���_�o�b�t�@
	ID3D11Buffer* m_pIndexBuffer;			// �C���f�b�N�X�o�b�t�@
	DatFileLoader* m_datfile;				// dat�t�@�C���f�[�^
	ID3D11ShaderResourceView** m_srv;					// �V�F�[�_�[���\�[�X�r���[
	ID3D11Buffer* m_cb3;					// �R���X�^���g�o�b�t�@(�}�e���A���p)
	ID3D11Resource* m_tex;
public:
	DatFile() {
		m_pVertexBuffer = nullptr;
		m_pIndexBuffer = nullptr;
	}

	virtual ~DatFile()
	{
		UnLoad();
	}

	bool Load(const char* xfilename, ID3D11Device* device11, ID3D11DeviceContext* device11Context);
	void UnLoad();
	void Draw(ID3D11DeviceContext* device);
	void DrawInstance(ID3D11DeviceContext* device, ID3D11Buffer* m_pInstanceBuffer, int instancecount);
	DatFileLoader* GetDatFileLoader() {
		return m_datfile;
	}
};

//******************************************************************************
//	End of file.
//******************************************************************************