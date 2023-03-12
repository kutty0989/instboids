//=============================================================================
//
// �e�N�X�`���[�����N���X [CTex.h]
//
//=============================================================================

#include	"CTex.h"

// comptr
using Microsoft::WRL::ComPtr;

// �g�p���钸�_�V�F�[�_�[��
const char* vstexfilename[] = {
	"shader/vsquad2d.hlsl"
};

// �g�p����s�N�Z���V�F�[�_�[��
const char* pstexfilename[] = {
	"shader/pstexcol.hlsl"
};

/// <summary>
/// ��`�̏�����
/// </summary>
/// <param name="width">����</param>
/// <param name="height">����</param>
/// <param name="color">�F</param>
/// <returns></returns>
bool CTex::Init(uint32_t width,
	uint32_t height,
	DirectX::XMFLOAT3 color) {

	DX11MtxIdentity(m_worldmtx);	// �����p��

	// �s�N�Z���V�F�[�_�[�𐶐�
	bool sts = ShaderHashmap::GetInstance()->SetPixelShader(pstexfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error", "error", MB_OK);
		return false;
	}

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// �G�������g��
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�𐶐�
	sts = ShaderHashmap::GetInstance()->SetVertexShader(
		vstexfilename[0],			// ���_�V�F�[�_�[�t�@�C����
		layout,					// ���_���C�A�E�g
		numElements);			// �G�������g��

	// ���_������
	updateVertex(width, height, color);

	// �f�o�C�X���擾
	ID3D11Device* device;
	device = GetDX11Device();

	// ���_�o�b�t�@�𐶐�
	sts = CreateVertexBufferWrite(
		device,						// �f�o�C�X�I�u�W�F�N�g
		sizeof(CTex::Vertex),		// �P���_������o�C�g��
		4,							// ���_��
		m_vertex,					// ���_�f�[�^�i�[�������擪�A�h���X
		&m_vertexbuffer				// ���_�o�b�t�@
	);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return false;
	}

	// �C���f�b�N�X�o�b�t�@�𐶐�
	uint32_t index[4] = { 0,1,2,3 };

	sts = CreateIndexBuffer(
		device,						// �f�o�C�X�I�u�W�F�N�g
		4,							// �C���f�b�N�X��
		index,						// �C���f�b�N�X�i�[�������擪�A�h���X
		&m_indexbuffer				// �C���f�b�N�X�o�b�t�@
	);
	if (!sts) {
		MessageBox(nullptr, "CreateIndexBuffer error", "error", MB_OK);
		return false;
	}

	// �r���[�|�[�g�T�C�Y�Z�b�g
	SetViewPortSize(DX11GetScreenWidth(), DX11GetScreenHeight());

	return true;
}

/// <summary>
/// �`�揈��
/// </summary>
void CTex::Draw() {

	TurnOffZbuffer();
	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	XMFLOAT4X4 vmtx;
	XMFLOAT4X4 pmtx;
	DX11MtxIdentity(pmtx);
	DX11MtxIdentity(vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, vmtx);
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, pmtx);

	// �e�N�X�`�����Z�b�g
	devcontext->PSSetShaderResources(0, 1, m_srv.GetAddressOf());

	//�s��v�Z
	DX11MtxIdentity(p_mtx);
	DX11MtxIdentity(s_mtx);
	DX11MtxIdentity(o_mtx);
	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);
	DX11MtxTranslation(m_pos, p_mtx);
    DX11MtxRotationZ(m_angle, o_mtx);//��]�s��
    DirectX::XMFLOAT4X4 mtx;
	DX11MtxIdentity(mtx);
	DX11MtxMultiply(mtx, s_mtx, o_mtx);
	DX11MtxMultiply(mtx, mtx, p_mtx);//�X�P�[���@���@��]�@���@�ړ�


	// ���W�ϊ��p�̍s����Z�b�g
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtx);


	unsigned int stride = sizeof(CTex::Vertex);	// �X�g���C�h���Z�b�g�i�P���_������̃o�C�g���j
	unsigned  offset = 0;						// �I�t�Z�b�g�l���Z�b�g

	// ���_�o�b�t�@���f�o�C�X�R���e�L�X�g�փZ�b�g
	devcontext->IASetVertexBuffers(
		0,									// �X�^�[�g�X���b�g
		1,									// ���_�o�b�t�@��
		m_vertexbuffer.GetAddressOf(),		// ���_�o�b�t�@�̐擪�A�h���X
		&stride,							// �X�g���C�h
		&offset);							// �I�t�Z�b�g

	// �C���f�b�N�X�o�b�t�@���f�o�C�X�R���e�L�X�g�փZ�b�g
	devcontext->IASetIndexBuffer(
		m_indexbuffer.Get(),				// �C���f�b�N�X�o�b�t�@
		DXGI_FORMAT_R32_UINT,				// �t�H�[�}�b�g
		0);									// �I�t�Z�b�g

	// �g�|���W�[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[�擾
	ID3D11VertexShader* vs;
	vs = ShaderHashmap::GetInstance()->GetVertexShader(vstexfilename[0]);
	ID3D11PixelShader* ps;
	ps = ShaderHashmap::GetInstance()->GetPixelShader(pstexfilename[0]);

	// ���_���C�A�E�g�擾
	ID3D11InputLayout* layout;
	layout = ShaderHashmap::GetInstance()->GetVertexLayout(vstexfilename[0]);

	//�e�V�F�[�_�[�ɃZ�b�g
	devcontext->VSSetShader(vs, nullptr, 0);
	//devcontext->GSSetShader(nullptr, nullptr, 0);
	//devcontext->HSSetShader(nullptr, nullptr, 0);
	//devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(ps, nullptr, 0);

	// ���_�t�H�[�}�b�g���Z�b�g
	devcontext->IASetInputLayout(layout);


	// �h���[�R�[�����s
	devcontext->DrawIndexed(
		4,						// �C���f�b�N�X��
		0,						// �J�n�C���f�b�N�X
		0);						// ����_�C���f�b�N�X

	TurnOnZbuffer();

}

/// <summary>
/// �I������
/// </summary>
void CTex::UnInit() {
	//ID3D11VertexShader* vs;
	//vs = ShaderHashmap::GetInstance()->GetVertexShader(vstexfilename[0]);
	//ID3D11PixelShader* ps;
	//ps = ShaderHashmap::GetInstance()->GetPixelShader(pstexfilename[0]);

	//// ���_���C�A�E�g�擾
	//ID3D11InputLayout* layout;
	//layout = ShaderHashmap::GetInstance()->GetVertexLayout(vstexfilename[0]);

	//// ���_�V�F�[�_�[���
	//if (vs) {
	//	vs->Release();
	//	vs = nullptr;
	//}

	//// �s�N�Z���V�F�[�_�[���
	//if (ps) {
	//	ps->Release();
	//	ps = nullptr;
	//}

	//// ���_���C�A�E�g���
	//if (layout) {
	//	layout->Release();
	//	layout = nullptr;
	//}
}

// �g��A�k��
void CTex::SetScale(float sx, float sy, float sz) {
	m_scale.x = sx;
	m_scale.y = sy;
	m_scale.z = sz;
}

// �ʒu���Z�b�g
void CTex::SetPosition(float x, float y, float z) {
	m_pos.x = Application::CLIENT_WIDTH * 0.5f + Application::CLIENT_WIDTH * 0.5f * x;
	m_pos.y = Application::CLIENT_HEIGHT * 0.5f + Application::CLIENT_HEIGHT * 0.5f * y;
	m_pos.z = z;
}

// Z����]
void CTex::SetRotation(float angle) {
	m_angle = angle;
}
void CTex::SetUV(XMFLOAT2* muv)
{
	c_uv[0] = muv[0];
	c_uv[1] = muv[1];
	c_uv[2] = muv[2];
	c_uv[3] = muv[3];

}

void CTex::SetAlpha(float a)
{
	m_Alpha = a;

}

void CTex::PartMax(float x, float y)
{
	PMaxX = x;
	PMaxY = y;
}

void CTex::Part(float x, float y)
{
	float px = 1 / PMaxX;
	float py = 1 / PMaxY;
	c_uv[0].x = x * px;
	c_uv[0].y = y * py;
	c_uv[1].x = x * px + px;
	c_uv[1].y = y * py;
	c_uv[2].x = x * px;
	c_uv[2].y = y * py+py;
	c_uv[3].x = x * px + px;
	c_uv[3].y = y * py + py;
	
}

// ���_�f�[�^�X�V
void CTex::updateVertex(uint32_t width,
	uint32_t height,
	DirectX::XMFLOAT3 color) {

	m_width = static_cast<float>(width);
	m_height = static_cast<float>(height);


		CTex::Vertex	v[4] = {
			// ���W													// �J���[	// UV	
			XMFLOAT3(-m_width ,	-m_height , 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[0],
			XMFLOAT3(m_width ,	-m_height, 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[1],
			XMFLOAT3(-m_width ,	 m_height , 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[2],
			XMFLOAT3(m_width ,	 m_height, 0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[3]
		};
		for (int i = 0; i < 4; i++) {
			m_vertex[i] = v[i];
		}
}

// ���_�o�b�t�@�X�V
void CTex::updateVbuffer() {
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetDX11DeviceContext()->Map(m_vertexbuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_vertex), sizeof(CTex::Vertex) * 4);
		GetDX11DeviceContext()->Unmap(m_vertexbuffer.Get(), 0);
	}
}