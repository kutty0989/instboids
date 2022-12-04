#pragma once
#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<math.h>
#include	<vector>
#include	"Shader.h"
#include	"CDirectxGraphics.h"

class CBox {
private:
	ID3D11Buffer* m_pVertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer* m_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@
	ID3D11VertexShader* m_pVertexShader;	// ���_�V�F�[�_�[
	ID3D11PixelShader* m_pPixelShader;		// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout* m_pVertexLayout;	// ���_���C�A�E�g
	float				m_lengthx;			// ����(X)
	float				m_lengthy;			// ����(Y)
	float				m_lengthz;			// ���s��(Z)

	struct Vertex {
		DirectX::XMFLOAT3	Pos;			// �ʒu
		DirectX::XMFLOAT4	Color;			// �J���[
	};

	struct Face {
		unsigned int idx[3];
	};

	Vertex					m_vertex[8];		// ���_���W

	Face					m_face[12];			// �ʃC���f�b�N�X�f�[�^
	unsigned int			m_facenum = 12;		// �ʐ�

	DirectX::XMFLOAT4		m_color = { 1.0f,1.0f,1.0f,0.3f };	// �J���[�l

	// �C���f�b�N�X�f�[�^���쐬����
	void CreateIndex();
	// ���_�f�[�^���쐬����
	void CreateVertex();
	// ���_�o�b�t�@������������
	void UpdateVertexBuffer() {
		ID3D11DeviceContext* devicecontext;

		devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

		D3D11_MAPPED_SUBRESOURCE pData;

		// �{�[���s��i�[�p�萔�o�b�t�@�X�V
		HRESULT hr = devicecontext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		if (SUCCEEDED(hr)) {
			memcpy_s(pData.pData, pData.RowPitch, (void*)&m_vertex, sizeof(Vertex) * 8);
			devicecontext->Unmap(m_pVertexBuffer, 0);
		}
	}
public:
	void SetColor(DirectX::XMFLOAT4 color) {
		m_color = color;
		CreateVertex();
		UpdateVertexBuffer();
	}

	XMFLOAT4 GetColor() {
		return m_color;
	}

	void Draw();

	// ������
	bool Init(
		float width,						// ��
		float height,						// ����
		float depth);						// ���s��

	// �I������
	void Exit();
};