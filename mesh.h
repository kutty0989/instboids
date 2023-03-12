#pragma once
//=============================================================================
//
// ���f���̃��b�V���摜�N���X [mesh.h]
//
//=============================================================================
#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <wrl/client.h>
#include "obb.h"
#include <unordered_map>
#include <map>
#include "vertexproto.h"

// �e�N�X�`���\����
struct Texture {
	std::string type;							// �e�N�X�`�����
	std::string path;							// �e�N�X�`���p�X��
	ID3D11Resource*	texres;						// �e�N�X�`�����\�[�X
	ID3D11ShaderResourceView *texture;			// SRV
};

using Microsoft::WRL::ComPtr;

class Mesh {
public:
	ID3D11ShaderResourceView*    m_whitesrv;	// �^�����r�q�u
	ID3D11Resource*				m_whiteres;	// �^����RES

	std::vector<Vertex> m_vertices;			// ���_�f�[�^
	std::vector<unsigned int> m_indices;	// �C���f�b�N�X
	std::vector<Texture> m_textures;		// �e�N�X�`��
	ID3D11Device* m_dev;					// �f�o�C�X	
	Material m_mtrl;						// �}�e���A��

	std::unordered_map<std::string, std::vector<DirectX::XMFLOAT3>>	m_bonevertices;		// �{�[�����̒��_�f�[�^

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures,Material mtrl);

	void Draw(ID3D11DeviceContext *devcon);
	void Drawinstance(ID3D11DeviceContext *devcon);
	std::vector<COBB*> m_obbvectorcontainer;		// OBB���X�g

	void Close();

	void DrawOBB(std::map<std::string, BONE>& bone);
	void UpdateOBB(std::map<std::string, BONE>& bone, const XMFLOAT4X4& mtxworld);

	ID3D11Buffer* m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11Buffer* m_IndexBuffer = nullptr;		// �C���f�b�N�X�o�b�t�@
	ID3D11Buffer* m_cbmtrl = nullptr;			// �}�e���A���p�R���X�^���g�o�b�t�@

private:
	
	bool setupMesh();
	void updatevertexbuffer();
};