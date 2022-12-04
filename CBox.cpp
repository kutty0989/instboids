#include	"CBox.h"
#include	"CDirectxGraphics.h"

const float PI = XM_PI;

// �C���f�b�N�X�f�[�^���쐬
void CBox::CreateIndex() {
	m_face[0].idx[0] = 0;		// ��O  ok
	m_face[0].idx[1] = 1;
	m_face[0].idx[2] = 2;

	m_face[1].idx[0] = 2;
	m_face[1].idx[1] = 3;
	m_face[1].idx[2] = 0;

	m_face[2].idx[0] = 5;		// ��  ok
	m_face[2].idx[1] = 4;
	m_face[2].idx[2] = 7;

	m_face[3].idx[0] = 7;
	m_face[3].idx[1] = 6;
	m_face[3].idx[2] = 5;

	m_face[4].idx[0] = 4;		// ���� ok
	m_face[4].idx[1] = 0;
	m_face[4].idx[2] = 7;

	m_face[5].idx[0] = 0;
	m_face[5].idx[1] = 3;
	m_face[5].idx[2] = 7;

	m_face[6].idx[0] = 1;		// �E�� ok
	m_face[6].idx[1] = 5;
	m_face[6].idx[2] = 6;

	m_face[7].idx[0] = 1;
	m_face[7].idx[1] = 6;
	m_face[7].idx[2] = 2;

	m_face[8].idx[0] = 0;		// �㑤 ok
	m_face[8].idx[1] = 4;
	m_face[8].idx[2] = 1;

	m_face[9].idx[0] = 4;
	m_face[9].idx[1] = 5;
	m_face[9].idx[2] = 1;

	m_face[10].idx[0] = 3;		// ����
	m_face[10].idx[1] = 2;
	m_face[10].idx[2] = 7;

	m_face[11].idx[0] = 6;
	m_face[11].idx[1] = 7;
	m_face[11].idx[2] = 2;
}

// ���_�f�[�^���쐬
void CBox::CreateVertex() {

	m_vertex[0].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[0].Pos.y = (m_lengthy / 2.0f);
	m_vertex[0].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[1].Pos.x = (m_lengthx / 2.0f);
	m_vertex[1].Pos.y = (m_lengthy / 2.0f);
	m_vertex[1].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[2].Pos.x = (m_lengthx / 2.0f);
	m_vertex[2].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[2].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[3].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[3].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[3].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[4].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[4].Pos.y = (m_lengthy / 2.0f);
	m_vertex[4].Pos.z = (m_lengthz / 2.0f);

	m_vertex[5].Pos.x = (m_lengthx / 2.0f);
	m_vertex[5].Pos.y = (m_lengthy / 2.0f);
	m_vertex[5].Pos.z = (m_lengthz / 2.0f);

	m_vertex[6].Pos.x = (m_lengthx / 2.0f);
	m_vertex[6].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[6].Pos.z = (m_lengthz / 2.0f);

	m_vertex[7].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[7].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[7].Pos.z = (m_lengthz / 2.0f);

	for (int i = 0; i < 8; i++) {
		m_vertex[i].Color = m_color;
	}
}

// �`��
void CBox::Draw() {

	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();
	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(Vertex);
	unsigned  offset = 0;
	devcontext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	devcontext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);			// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	devcontext->IASetInputLayout(m_pVertexLayout);					// ���_���C�A�E�g�Z�b�g

	devcontext->VSSetShader(m_pVertexShader, nullptr, 0);			// ���_�V�F�[�_�[���Z�b�g
	devcontext->PSSetShader(m_pPixelShader, nullptr, 0);			// �s�N�Z���V�F�[�_�[���Z�b�g

	devcontext->DrawIndexed(m_facenum * 3,		// �`�悷��C���f�b�N�X���i�ʐ��~�R�j
		0,										// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);										// ���_�o�b�t�@�̍ŏ�����g��
}

bool CBox::Init(
	float width,
	float height,
	float depth) {

	bool sts;

	// �a�a�n�w�T�C�Y���Z�b�g
	m_lengthx = width;
	m_lengthy = height;
	m_lengthz = depth;

	// BOX�̃C���f�b�N�X�f�[�^���쐬
	CreateIndex();

	// BOX�̒��_�f�[�^���쐬
	CreateVertex();

	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// ���_�o�b�t�@�쐬
	sts = CreateVertexBufferWrite(
		device,
		sizeof(Vertex),			// �P���_������o�C�g��
		8,						// ���_��
		m_vertex,				// ���_�f�[�^�i�[�������擪�A�h���X
		&m_pVertexBuffer);		// ���_�o�b�t�@
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}

	// �C���f�b�N�X�o�b�t�@�쐬
	sts = CreateIndexBuffer(
		device,
		12 * 3,					// �P�Q�ʁ~�R���_
		m_face,					// �C���f�b�N�X�f�[�^�擪�A�h���X
		&m_pIndexBuffer);		// �C���f�b�N�X�o�b�t�@
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return false;
	}

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	sts = CreateVertexShader(device,
		"shader/3dboxvs.fx",
		"main",
		"vs_4_0",
		layout,
		numElements,
		&m_pVertexShader,
		&m_pVertexLayout);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	sts = CreatePixelShader(			// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
		device,							// �f�o�C�X�I�u�W�F�N�g
		"shader/3dboxps.fx",
		"main",
		"ps_4_0",
		&m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	return true;
}

void CBox::Exit() {

	// �s�N�Z���V�F�[�_�[���
	if (m_pPixelShader) {
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	// ���_�V�F�[�_�[���
	if (m_pVertexShader) {
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}

	if (m_pVertexLayout) {
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}

	if (m_pIndexBuffer) {
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
}