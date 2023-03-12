//=============================================================================
//
// �C���X�^���X���f���`�揈�� [CModelInstance.h]
//
//=============================================================================
#include	<windows.h>
#include	"CModelInstance.h"
#include	"Shader.h"
#include	"DX11util.h"
#include	"CCamera.h"
#include	"DX11Settransform.h"
#include"drawaxis.h"

/// <summary>
/// �C���X�^���V���O�̏���������
/// </summary>
/// <param name="num">�C���X�^���X��</param>
/// <param name="filename">���f���̃t�@�C����</param>
/// <param name="vsfile">VS�̃t�@�C����</param>
/// <param name="psfile">PS�t�@�C����</param>
/// <param name="texfoldername">�e�N�X�`���̃t�H���_�[</param>
/// <returns></returns>
bool CModelInstance::InitiInstancing(int num, const char* filename, const char* vsfile, const char* psfile, std::string texfoldername) {

	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// �f�o�C�X���擾
	ID3D11Device* device;
	device = GetDX11Device();

	bool sts;
	
	//�t�@�C�����ۑ�
	std::string fname(filename);

	//�e�N�X�`���ǂݍ���
	sts = m_assimpfile.Load(texfoldername, fname);
	if (!sts) {
		char str[128];
		sprintf_s(str, 128, "%s load ERROR!!", filename);
		MessageBox(nullptr, str, "error", MB_OK);
		return false;
	}
	//�������쐬
	CreateSRVfromFile(texfoldername.c_str(),
		GetDX11Device(),
		GetDX11DeviceContext(),
		&m_tex, &m_srv);

	//�S���b�V�����_���A���擾
	GetVertex();

	//�ŏ���ptr�擾
	auto vdata = ver.begin()._Ptr;
	auto idata = ind.begin()._Ptr;

	// ���_�o�b�t�@�쐬
	sts = CreateVertexBuffer(
		device,
		sizeof(Vertex),				// �P���_������o�C�g��
		ver.size(),			// ���_��
		vdata,				// ���_�f�[�^�i�[�������擪�A�h���X
		&m_pVertexBuffer);				// ���_�o�b�t�@
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}

	// �C���f�b�N�X�o�b�t�@�쐬
	sts = CreateIndexBuffer(
		device,
		ind.size(),				// ���_��
		idata,				// ���_�f�[�^�i�[�������擪�A�h���X
		&m_pIndexBuffer);				// �C���f�b�N�X�o�b�t�@
	if (!sts) {
		MessageBox(NULL, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return false;
	}
	
	//�t�@�C���^�C�v�����߂�
	m_filetype = eASSIMPFILE;
	


	// �C���X�^���V���O���Z�b�g
	m_instancecount = num;

	//�f�[�^�T�C�Y���v�Z
	m_initdata = _mm_malloc(sizeof(XMMATRIX) * num, 16);
	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	// �C���X�^���X�o�b�t�@�̏����s����Z�b�g
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMMatrixTranslation(0, 0, 0));
		pstart++;
	}
	//�C���X�^���X�p�o�b�t�@
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
	sts = CreateVertexinShader(device,
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



	// �萔�o�b�t�@�̍쐬(�p�����[�^�󂯓n���p)
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	device->CreateBuffer(&cb, NULL, mConstantBuffer.GetAddressOf());

	//�p�C�v���C���̍\�z
	ID3D11Buffer* bufs[] = { m_pVertexBuffer};
	UINT stride[] = { sizeof(Vertex) };
	UINT offset[] = { 0 };
	devcontext->IASetVertexBuffers(0, sizeof(bufs) / sizeof(bufs[0]), bufs, stride, offset);
	devcontext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devcontext->IASetInputLayout(m_pVertexLayout);

	//�J�����s��v�Z
	auto camera = CCamera::GetInstance()->GetCameraMatrix();
	mView = DirectX::XMLoadFloat4x4(&camera);
	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
	mProj = DirectX::XMLoadFloat4x4(&proj);
	mScale = XMMatrixScalingFromVector(XMVectorSet(0.1f, 0.1f, 0.1f, 0.0f));
	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(90.0f);

	return true;
}

/// <summary>
/// �V�F�[�_�[���
/// </summary>
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


/// <summary>
///
/// </summary>
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
/// <summary>
/// ���_�X�V
/// </summary>
/// <param name="mat"></param>
void CModelInstance::Update(XMFLOAT4X4 mat[]) {


	D3D11_MAPPED_SUBRESOURCE pData;

	XMMATRIX* pstart = static_cast<XMMATRIX*>(m_initdata);

	 //�C���X�^���X�o�b�t�@�̏����s����Z�b�g
	for (int i = 0; i < m_instancecount; i++) {
		*pstart = XMMatrixTranspose(XMLoadFloat4x4(&mat[i]));
		drawaxis(mat[i], 1000, XMFLOAT3(mat->_41, mat->_42, mat->_43));
		pstart++;

	}

	HRESULT hr = GetDX11DeviceContext()->Map(m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_initdata), sizeof(XMMATRIX) * m_instancecount);

		GetDX11DeviceContext()->Unmap(m_pInstanceBuffer, 0);
	}

	
}


/// <summary>
/// �C���X�^���X�`�揈��
/// </summary>
void CModelInstance::DrawInstance() {
	
	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// �f�o�C�X���擾
	ID3D11Device* device;
	device = GetDX11Device();

	// ���_�t�H�[�}�b�g���Z�b�g
	GetDX11DeviceContext()->IASetInputLayout(m_pVertexLayout);

	// ���_�V�F�[�_�[���Z�b�g
	GetDX11DeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
	GetDX11DeviceContext()->GSSetShader(nullptr, nullptr, 0);
	GetDX11DeviceContext()->HSSetShader(nullptr, nullptr, 0);
	GetDX11DeviceContext()->DSSetShader(nullptr, nullptr, 0);
	// �s�N�Z���V�F�[�_�[���Z�b�g
	GetDX11DeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);


	//�e�N�X�`���[���s�N�Z���V�F�[�_�[�ɓn��
	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());

	int indexnum = 0;
	int indexstart = 0;

	X::ConstantBufferMaterial		cb;					// �R���X�^���g�o�b�t�@�R�p�\���́i�}�e���A���̒l�j

														// ���͂��钸�_�o�b�t�@�ƃC���X�^���X�o�b�t�@
	ID3D11Buffer* vbuffer[2] = { m_pVertexBuffer ,m_pInstanceBuffer };
	// ���ꂼ��̃X�g���C�h���Z�b�g
	unsigned int stride[2] = { sizeof(Vertex),sizeof(XMMATRIX) };
	// �I�t�Z�b�g���Z�b�g
	unsigned  offset[2] = { 0,0 };

	// ���_�o�b�t�@���Z�b�g	
	devcontext->IASetVertexBuffers(0, 2, vbuffer, stride, offset);

	// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcontext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcontext->PSSetShaderResources(0, 1, &m_srv);			// debug ts

	//�C���X�^���X�`��
	devcontext->DrawIndexedInstanced(ind.size(), m_instancecount, 0, 0, 0);

}
