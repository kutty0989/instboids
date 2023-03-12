//=============================================================================
//
// �p�[�e�B�N�������N���X [Particle.cpp]
//
//=============================================================================
#include "Particle.h"
#include"Shader.h"
#include"dx11mathutil.h"
#include"DX11Settransform.h"
#include"DX11util.h"


/// <summary>
/// �p�[�e�B�N����������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="xsize">���̑傫��</param>
/// <param name="ysize">���̑傫��</param>
/// <param name="color">�F</param>
/// <returns></returns>
bool Particle::Init(float x, float y, float z, float xsize, float ysize, DirectX::XMFLOAT4 color)
{
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// �f�o�C�X���擾
	ID3D11Device* dev;
	dev = GetDX11Device();


	//���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{	"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		};
	unsigned int numElements = ARRAYSIZE(layout);
	//���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	bool sts = CreateVertexShader(dev,
		"shader/vsbillboard.hlsl",
		"main",
		"vs_5_0",
		layout,
		numElements,
		&m_pVertexShader,
		&m_pVertexLayout);

	if (!sts)
	{
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}
	//�s�N�Z���V�F�[�_�[�𐶐�
	sts = CreatePixelShader(
		dev, "shader/psbillboard.hlsl",
		"main",
		"ps_5_0",
		&m_pPixelShader);
	if (!sts)
	{
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}
	//�W�I���g���[�V�F�[�_���쐬
	sts = CreateGeometryShader(
		dev, "shader/psbillboard.hlsl",
		"main",
		"ps_5_0",
		&m_pGeometryShader);
	if (!sts)
	{
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	MyVertex vertices[] =
	{
		-0.5f, 0.5f, 0.0f,
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MyVertex) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	//���_�o�b�t�@���Z�b�g
	unsigned int stride = sizeof(MyVertex);
	unsigned offset = 0;


	//���_�o�b�t�@���Z�b�g
	devcontext->IASetVertexBuffers(0, 1, &m_vbuffer, &stride, &offset);


	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	dev->CreateBuffer(&bd, &InitData, &m_vbuffer);
	
	CreateBlendStateSrcAlpha();//�A���t�@�u�����f�B���O�p�̃u�����h�X�e�[�g�𐶐�
	CreateBlendStateOne();//���Z�����p�u�����h�X�e�[�g����
	CreateBelndStateDefault();//�Ńt�@���Ƃ̃u�����h�X�e�[�g����

	// �萔�o�b�t�@����
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer2), &g_pConstantBuffer2);
	if (!sts) {
		MessageBox(nullptr, "CreateConstantBuffer2 error", "error", MB_OK);
		return false;
	}


	hp = 1.0f;
	ConstantBuffer2 cb2;
	cb2.hp = hp;//�����ϐ���n��
	devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// �R���X�^���g�o�b�t�@�X�V
	devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DS�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g


	return true;
}

//�T�C�Y���Z�b�g
void Particle::SetSize(float x, float y)
{
	m_XSize = x;
	m_YSize = y;
//	CalcVertex();
}



//�ʒu���Z�b�g
void Particle::SetPosiotion(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Particle::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

//�r���{�[�h�p�̍s��𐶐�
void Particle::CalParticleMatrix(const DirectX::XMFLOAT4X4& cameramat)
{
	m_mtx._11 = cameramat._11;
	m_mtx._12 = cameramat._21;
	m_mtx._13 = cameramat._31;

	m_mtx._21 = cameramat._12;
	m_mtx._22 = cameramat._22;
	m_mtx._23 = cameramat._32;

	m_mtx._31 = cameramat._13;
	m_mtx._32 = cameramat._23;
	m_mtx._33 = cameramat._33;

	m_mtx._41 = m_x;
	m_mtx._42 = m_y;
	m_mtx._43 = m_z;

	m_mtx._14 = 0;
	m_mtx._24 = 0;
	m_mtx._34 = 0;
	m_mtx._44 = 1;
}

//�`��
void Particle::Draw()
{
	TurnOffZbuffer();

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//�V�F�[�_�[���\�[�X�r���[���s�N�Z���V�F�[�_�[�փZ�b�g
	devcontext->PSSetShaderResources(5, 1, &m_srv);
	DX11MtxIdentity(t_mtx);
	DX11MtxIdentity(s_mtx);
	DX11MtxTranslation(XMFLOAT3(m_x, m_y, m_z), t_mtx);
	DX11MtxScale(scale.x, scale.y, scale.z, s_mtx);
	DX11MtxIdentity(o_mtx);

	DX11MtxRotationZ(angle, o_mtx);//��]�s��
	DirectX::XMFLOAT4X4 mtx;

	DX11MtxMultiply(mtx, s_mtx, o_mtx);
	DX11MtxMultiply(m_mtx, mtx, m_mtx);
	//DX11MtxMultiply(m_mtx,mtx, m_mtx);

	//���[���h�ϊ��s��
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, m_mtx);

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	//m_devcontext->IASetIndexBuffers(nullptr,DXGI_FORMAT_R32_UINT,0);
	//�Ƃۂ�[���[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//���_�t�H�[�}�b�g���Z�b�g
	devcontext->IASetInputLayout(m_pVertexLayout);

	//4�p�`�`��
	devcontext->VSSetShader(m_pVertexShader, nullptr, 0);//���_�V�F�[�_�[���Z�b�g
	devcontext->GSSetShader(m_pGeometryShader, nullptr, 0);
	devcontext->HSSetShader(nullptr, nullptr, 0);
	devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(m_pPixelShader, nullptr, 0);//�s�N�Z���V�F�[�_�[��������
	devcontext->Draw(4, 0);

	TurnOnZbuffer();


}

//�r���{�[�h��`��
void Particle::DrawBillBoard(const XMFLOAT4X4& cameramat) {
	//�J�����s�񂩂�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalParticleMatrix(cameramat);

	//���u�����f�B���O���Z�b�g����
//	SetBlendStrateAlpha();

	//�`��
	Draw();

	//���u�����f�B���O���Z�b�g
//SetBlendStrateDefault();
}

//�r���{�[�h��`��
void Particle::DrawBillBoardAdd(const XMFLOAT4X4& cameramat) {
	//�J�����s�񂩂�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalParticleMatrix(cameramat);

	//�`��
	//�A���t�@�u�����f�B���O���Z�b�g
	SetBlendStateOne();
	//�`��
	Draw();

	//�A���t�@�u�����f�B���O���Z�b�g
	SetBlendStateDefault();
}
//

void Particle::SetBlendStateDefault()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	devcontext->OMSetBlendState(m_pBlendStateDefault, blendFactor, 0xffffffff);

}

void Particle::SetBlendStateSrcAlpha()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	devcontext->OMSetBlendState(m_pBlendStateSrcAlpha, blendFactor, 0xffffffff);
}


void Particle::SetBlendStateOne()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	devcontext->OMSetBlendState(m_pBlendStateOne, blendFactor, 0xffffffff);
}

void Particle::CreateBlendStateSrcAlpha() {
	D3D11_BLEND_DESC BlendDesc;

	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;//�z��O�Ԃ̂ݎd�l

	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11Device* dev;
	dev = GetDX11Device();

	dev->CreateBlendState(&BlendDesc, &m_pBlendStateSrcAlpha);

}

void Particle::CreateBlendStateOne() {
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;//�z��O�Ԗڂ̂ݎg�p

	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	ID3D11Device* dev;
	dev = GetDX11Device();

	dev->CreateBlendState(&BlendDesc, &m_pBlendStateOne);
}

void Particle::CreateBelndStateDefault() {

	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;//�z��O�Ԗڂ̂ݎg�p

	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	ID3D11Device* dev;
	dev = GetDX11Device();

	dev->CreateBlendState(&BlendDesc, &m_pBlendStateDefault);

}

void Particle::PartMax(float x, float y)
{
	PMaxX = x;
	PMaxY = y;
}

void Particle::Part(float x, float y)
{
	float px = 1 / PMaxX;
	float py = 1 / PMaxY;
	m_uv[0].x = x * px;
	m_uv[0].y = y * py;
	m_uv[1].x = x * px;
	m_uv[1].y = y * py + py;
	m_uv[2].x = x * px + px;
	m_uv[2].y = y * py;
	m_uv[3].x = x * px + px;
	m_uv[3].y = y * py + py;
	//CalcVertex();
}

//�r���{�[�h��`��iZ���ŉ�]�j
void Particle::DrawRotateBillBoard(const DirectX::XMFLOAT4X4& cameramat, float angle)
{
	//�J�����s�񂩂�@�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalParticleMatrix(cameramat);

	//Z����]�s����쐬
	DirectX::XMFLOAT4X4 matRotZ;
	DirectX::XMFLOAT3 axisZ = { cameramat._13,cameramat._23,cameramat._33 };

	//�w�莲��]�̍s����쐬
	DX11MtxRotationAxis(axisZ, angle, matRotZ);

	//�s����������A�ʒu���Z�b�g
	DX11MtxMultiply(m_mtx, m_mtx, matRotZ);
	m_mtx._41 = m_x;
	m_mtx._42 = m_y;
	m_mtx._43 = m_z;

	//�A���t�@�u�����f�B���O���Z�b�g
	//SetBlendStateSrcAlpha();

	//�`��
	Draw();



}

//�e�N�X�`����ǂݍ���
bool Particle::LoadTexTure(const char* filename)
{
	//���łɓǂݍ��܂�Ă���e�N�X�`��������ΊJ������
	if (m_srv != nullptr)
	{
		m_srv->Release();
		m_srv = nullptr;
	}

	ID3D11Device* dev = GetDX11Device();
	ID3D11DeviceContext* devcontext = GetDX11DeviceContext();

	bool sts = CreateSRVfromFile(filename,
		dev, devcontext, &m_res, &m_srv);

	if (sts == false)
	{
		MessageBox(nullptr, "textureload error(Particle LOADTEXTURE)", "error", MB_OK);
		return false;
	}

	return true;
}

