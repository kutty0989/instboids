#pragma once
#pragma once
#include	<d3d11.h>
#include	"DatFile.h"
#include"DatFileLoader.h"
#include"ModelData.h"

class CModelInstance {
private:
	ModelData m_assimpfile;
	DatFile					m_datfile;						// dat�t�@�C��
	ID3D11VertexShader* m_pVertexShader = nullptr;		// ���_�V�F�[�_�[���ꕨ
	ID3D11PixelShader* m_pPixelShader = nullptr;		// �s�N�Z���V�F�[�_�[���ꕨ
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// ���_�t�H�[�}�b�g��`

	ID3D11ShaderResourceView* m_texSRV = nullptr;			// �e�N�X�`���r�q�u
	int						m_instancecount = 0;			// �C���X�^���V���O��
	ID3D11Buffer* m_pInstanceBuffer;				// �C���X�^���X�p�s��i�[���_�o�b�t�@
	void* m_initdata = nullptr;			// �C���X�^���X�o�b�t�@�̏������f�[�^
public:
	bool InitiInstancing(int instancecnt, const char* filename, const char* vsfile, const char* psfile);
	bool Init(const char* filename, const char* vsfile, const char* psfile);
	void Uninit();
	void Update(XMFLOAT4X4 mat[]);							// �C���X�^���X�o�b�t�@�X�V
	void Draw();
	void DrawInstance();
	DatFileLoader* GetDatFileData() {
		return m_datfile.GetDatFileLoader();
	}
};
