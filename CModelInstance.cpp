#include	<windows.h>
#include	"CModelInstance.h"
#include	"Shader.h"

#include	"DX11util.h"
#include	"CCamera.h"
#include	"DX11Settransform.h"


bool CModelInstance::InitiInstancing(int num, const char* filename, const char* vsfile, const char* psfile) {

	bool sts;

	m_assimpfile.Load(filename, GetDX11Device(), GetDX11DeviceContext());
	// ��s�@�̃��f���f�[�^��ǂݍ���
	sts = m_datfile.Load(filename, GetDX11Device(), GetDX11DeviceContext());
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}

	// �C���X�^���V���O���Z�b�g
	m_instancecount = num;

	m_initdata = _mm_malloc(sizeof(XMMATRIX) * num, 16);
	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	// �C���X�^���X�o�b�t�@�̏����s����Z�b�g
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMMatrixTranslation(0, 0, 0));
		pstart++;
	}

	sts = CreateVertexBufferWrite(
		GetDX11Device(),		// device11
		sizeof(XMMATRIX),		// �P���_������o�C�g��
		num,					// ���_��
		m_initdata,				// �������f�[�^
		&m_pInstanceBuffer);	// ���_�o�b�t�@
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBufferWrite(InstanceBuffer) error", "error", MB_OK);
		return false;
	}

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// semantic name    index		format							slot	alignedbyteoffset				inputslotclass				instancedatasteprate
		{ "POSITION",		0,		DXGI_FORMAT_R32G32B32_FLOAT,		0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL",			0,		DXGI_FORMAT_R32G32B32_FLOAT,	    0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",		0,		DXGI_FORMAT_R32G32_FLOAT,			0,		D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "LocalToWorld",	0,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		0,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	1,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		16,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	2,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		32,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
		{ "LocalToWorld",	3,		DXGI_FORMAT_R32G32B32A32_FLOAT,		1,		48,								D3D11_INPUT_PER_INSTANCE_DATA,	1 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	sts = CreateVertexShader(GetDX11Device(),
		vsfile,
		"main",
		"vs_5_0",
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
		GetDX11Device(),		// �f�o�C�X�I�u�W�F�N�g
		psfile,
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	return true;
}

bool CModelInstance::Init(const char* filename, const char* vsfile, const char* psfile) {

	bool sts;

	// ��s�@�̃��f���f�[�^��ǂݍ���
	sts = m_datfile.Load(filename, GetDX11Device(), GetDX11DeviceContext());
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}

	// ��s�@�p�̒��_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	sts = CreateVertexShader(GetDX11Device(),
		vsfile,
		"main",
		"vs_5_0",
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
		GetDX11Device(),		// �f�o�C�X�I�u�W�F�N�g
		psfile,
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	return true;
}

void CModelInstance::Uninit() {
	// ���_�V�F�[�_�[���
	if (m_pVertexShader) {
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}

	// �s�N�Z���V�F�[�_�[���
	if (m_pPixelShader) {
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	// ���_���C�A�E�g���
	if (m_pVertexLayout) {
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}

	if (m_initdata) {
		// ���
		_mm_free(m_initdata);
		m_initdata = nullptr;
	}
}

void CModelInstance::Update(XMFLOAT4X4 mat[]) {


	D3D11_MAPPED_SUBRESOURCE pData;

	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	// �C���X�^���X�o�b�t�@�̏����s����Z�b�g
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMLoadFloat4x4(&mat[i]));
		pstart++;
	}

	HRESULT hr = GetDX11DeviceContext()->Map(m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_initdata), sizeof(XMMATRIX) * m_instancecount);

		GetDX11DeviceContext()->Unmap(m_pInstanceBuffer, 0);
	}
}

void CModelInstance::Draw() {
	// ���_�t�H�[�}�b�g���Z�b�g
	GetDX11DeviceContext()->IASetInputLayout(m_pVertexLayout);

	// ���_�V�F�[�_�[���Z�b�g
	GetDX11DeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);

	// �s�N�Z���V�F�[�_�[���Z�b�g
	GetDX11DeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);

	// ���f���`��
	m_datfile.Draw(GetDX11DeviceContext());
}

void CModelInstance::DrawInstance() {
	// ���_�t�H�[�}�b�g���Z�b�g
	GetDX11DeviceContext()->IASetInputLayout(m_pVertexLayout);

	// ���_�V�F�[�_�[���Z�b�g
	GetDX11DeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);

	// �s�N�Z���V�F�[�_�[���Z�b�g
	GetDX11DeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);

	// ���f���C���X�^���V���O�`��
	m_datfile.DrawInstance(GetDX11DeviceContext(), m_pInstanceBuffer, m_instancecount);
}
