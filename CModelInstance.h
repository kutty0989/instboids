#pragma once
#pragma once
#include	<d3d11.h>
#include	"DatFile.h"
#include"DatFileLoader.h"
#include"ModelData.h"

class CModelInstance {
private:
	enum FILETYPE {
		eDATFILE,
		eASSIMPFILE
	};


	struct CONSTANT_BUFFER
	{
		DirectX::XMMATRIX gWVP;
	};

	struct PerInstanceData
	{
		DirectX::XMMATRIX matrix;
		DirectX::XMVECTOR color;

	};

	ComPtr<ID3D11Buffer> mPerInstanceBuffer;
	ComPtr<ID3D11Buffer> mConstantBuffer;

	FILETYPE				m_filetype = eASSIMPFILE;		// �t�@�C���^�C�v

	ModelData m_assimpfile;
	DatFile					m_datfile;						// dat�t�@�C��
	ID3D11VertexShader* m_pVertexShader = nullptr;		// ���_�V�F�[�_�[���ꕨ
	ID3D11PixelShader* m_pPixelShader = nullptr;		// �s�N�Z���V�F�[�_�[���ꕨ
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// ���_�t�H�[�}�b�g��`

	//ID3D11ShaderResourceView* m_texSRV = nullptr;			// �e�N�X�`���r�q�u
	int						m_instancecount = 0;			// �C���X�^���V���O��
	ID3D11Buffer* m_pInstanceBuffer;				// �C���X�^���X�p�s��i�[���_�o�b�t�@
	void* m_initdata = nullptr;			// �C���X�^���X�o�b�t�@�̏������f�[�^

	ID3D11Buffer* m_pVertexBuffer;		// ���_�o�b�t�@
	ID3D11Buffer* m_pIndexBuffer;			// �C���f�b�N�X�o�b�t�@
//	DatFileLoader* m_datfile;				// dat�t�@�C���f�[�^
	ID3D11ShaderResourceView** m_srv;					// �V�F�[�_�[���\�[�X�r���[
	ID3D11Buffer* m_cb3;					// �R���X�^���g�o�b�t�@(�}�e���A���p)
	ID3D11Resource* m_tex;
public:
	bool InitiInstancing(int instancecnt, const char* filename, const char* vsfile, const char* psfile, std::string texfoldername);
	bool Init(const char* filename, const char* vsfile, const char* psfile);
	void Uninit();
	void Update(XMFLOAT4X4 mat[]);							// �C���X�^���X�o�b�t�@�X�V
	void Draw();
	void DrawInstance();
	DatFileLoader* GetDatFileData() {
		return m_datfile.GetDatFileLoader();
	}
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProj;
	DirectX::XMMATRIX mRotation;
	DirectX::XMMATRIX mScale;
	std::vector<Vertex> ver;
	std::vector<unsigned int> ind;

	void GetVertex() {

		// ���b�V���f�[�^�擾
		const std::vector<Mesh>& meshes = m_assimpfile.GetMeshes();

		// OBB�S���擾
		for (int i = 0; i < meshes.size(); i++) {
			const Mesh& m = meshes[i];
			for (auto data : m.m_vertices) {
				ver.emplace_back(data);
			}
			for (auto data : m.m_indices) {
				ind.emplace_back(data);
			}
		}
	}

};
