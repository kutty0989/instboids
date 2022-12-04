#include"CBillBoard.h"
#include"Shader.h"
#include"dx11mathutil.h"
#include"DX11Settransform.h"
#include"DX11util.h"

//�r���{�[�h�̒��_���W���v�Z
void CBillBoard::CalcVertex()
{
	m_Vertex[0].x = -m_XSize / 2;
	m_Vertex[0].y = m_YSize / 2;
	m_Vertex->z = 0.0f;
	m_Vertex[0].color = m_Color;
	m_Vertex[0].tu = m_uv[0].x;
	m_Vertex[0].tv = m_uv[0].y;

	m_Vertex[1].x = m_XSize / 2;
	m_Vertex[1].y = m_YSize / 2;
	m_Vertex->z = 0.0f;
	m_Vertex[1].color = m_Color;
	m_Vertex[1].tu = m_uv[1].x;
	m_Vertex[1].tv = m_uv[1].y;

	m_Vertex[2].x = -m_XSize / 2;
	m_Vertex[2].y = -m_YSize / 2;
	m_Vertex->z = 0.0f;
	m_Vertex[2].color = m_Color;
	m_Vertex[2].tu = m_uv[2].x;
	m_Vertex[2].tv = m_uv[2].y;

	m_Vertex[3].x = m_XSize / 2;
	m_Vertex[3].y = -m_YSize / 2;
	m_Vertex->z = 0.0f;
	m_Vertex[3].color = m_Color;
	m_Vertex[3].tu = m_uv[3].x;
	m_Vertex[3].tv = m_uv[3].y;

	if (m_vbuffer == nullptr) {
		ID3D11Device* dev;
		dev = GetDX11Device();

		//���_�o�b�t�@�쐬�i��ŕύX�\�ȁj
		bool sts = CreateVertexBufferWrite(dev, sizeof(MyVertex), 4, m_Vertex, &m_vbuffer);
		if (!sts) {
			MessageBox(nullptr, "create vertex buffer erro(CBillBoard)", "error", MB_OK);
		}
	}
	else {
		//�쐬�ς݂Ȃ���e������������
		D3D11_MAPPED_SUBRESOURCE pData;
		ID3D11DeviceContext* devcontext;
		devcontext = GetDX11DeviceContext();
		HRESULT hr = devcontext->Map(m_vbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		if (SUCCEEDED(hr)) {
			memcpy_s(pData. pData, pData. RowPitch, (void*)(m_Vertex), sizeof(MyVertex) * 4);
			devcontext->Unmap(m_vbuffer, 0);
		}
	}
}

//�T�C�Y���Z�b�g
void CBillBoard::SetSize(float x, float y)
{
	m_XSize = x;
	m_YSize = y;
	CalcVertex();
}



//�ʒu���Z�b�g
void CBillBoard::SetPosiotion(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void CBillBoard::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

//�r���{�[�h�p�̍s��𐶐�
void CBillBoard::CalcBillBoardMatrix(const DirectX::XMFLOAT4X4& cameramat)
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
void CBillBoard::Draw()
{
	//Z�o�b�t�@������
  //  TurnOnAlphablend();
	TurnOffZbuffer();

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	//�V�F�[�_�[���\�[�X�r���[���s�N�Z���V�F�[�_�[�փZ�b�g
	devcontext->PSSetShaderResources(5, 1, &m_srv);
	DX11MtxIdentity(t_mtx);
	DX11MtxIdentity(s_mtx);
	DX11MtxTranslation(XMFLOAT3(m_x,m_y,m_z), t_mtx);
	DX11MtxScale(scale.x,scale.y, scale.z, s_mtx);
	DX11MtxIdentity(o_mtx);
	DX11MtxRotationZ(angle, o_mtx);//��]�s��
	DirectX::XMFLOAT4X4 mtx;

	DX11MtxMultiply(mtx,s_mtx, o_mtx);
	DX11MtxMultiply(m_mtx,mtx, m_mtx);
	//DX11MtxMultiply(m_mtx,mtx, m_mtx);

	//���[���h�ϊ��s��
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD,m_mtx);

	//���_�o�b�t�@���Z�b�g
	unsigned int stride = sizeof(MyVertex);
	unsigned offset = 0;


	//���_�o�b�t�@���Z�b�g
	devcontext->IASetVertexBuffers(0, 1, &m_vbuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@���Z�b�g
	//m_devcontext->IASetIndexBuffers(nullptr,DXGI_FORMAT_R32_UINT,0);
	//�Ƃۂ�[���[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//���_�t�H�[�}�b�g���Z�b�g
	devcontext->IASetInputLayout(m_pVertexLayout);

	//4�p�`�`��
	devcontext->VSSetShader(m_pVertexShader, nullptr, 0);//���_�V�F�[�_�[���Z�b�g

	devcontext->HSSetShader(nullptr, nullptr, 0);
	devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(m_pPixelShader, nullptr, 0);//�s�N�Z���V�F�[�_�[��������
	devcontext->Draw(4, 0);

	TurnOnZbuffer();
	//TurnOffAlphablend();
	//Z�o�b�t�@��L����
	//TurnOnZbuffer();

}

//�r���{�[�h��`��
void CBillBoard::DrawBillBoard(const XMFLOAT4X4& cameramat) {
	//�J�����s�񂩂�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalcBillBoardMatrix(cameramat);

	//���u�����f�B���O���Z�b�g����
//	SetBlendStrateAlpha();

	//�`��
	Draw();

	//���u�����f�B���O���Z�b�g
//SetBlendStrateDefault();
}

//�r���{�[�h��`��
void CBillBoard::DrawBillBoardAdd(const XMFLOAT4X4& cameramat) {
	//�J�����s�񂩂�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalcBillBoardMatrix(cameramat);

	//�`��
	//�A���t�@�u�����f�B���O���Z�b�g
	SetBlendStateOne();
	//�`��
	Draw();

	//�A���t�@�u�����f�B���O���Z�b�g
	SetBlendStateDefault();
}
//

void CBillBoard::SetBlendStateDefault()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	devcontext->OMSetBlendState(m_pBlendStateDefault, blendFactor, 0xffffffff);

}

void CBillBoard::SetBlendStateSrcAlpha()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	devcontext->OMSetBlendState(m_pBlendStateSrcAlpha, blendFactor, 0xffffffff);
}


void CBillBoard::SetBlendStateOne()
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	devcontext->OMSetBlendState(m_pBlendStateOne, blendFactor, 0xffffffff);
}

void CBillBoard::CreateBlendStateSrcAlpha() {
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

void CBillBoard::CreateBlendStateOne() {
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

void CBillBoard::CreateBelndStateDefault() {

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

void CBillBoard::PartMax(float x, float y)
{
	PMaxX = x;
	PMaxY = y;
}

void CBillBoard::Part(float x, float y)
{
	float px = 1/PMaxX;
	float py = 1/PMaxY;
	m_uv[0].x = x*px;
	m_uv[0].y = y*py;
	m_uv[1].x = x*px;
	m_uv[1].y = y*py+py;
	m_uv[2].x = x*px+px;
	m_uv[2].y = y*py;
	m_uv[3].x = x*px+px;
	m_uv[3].y = y*py+py;
	CalcVertex();
}

//�r���{�[�h��`��iZ���ŉ�]�j
void CBillBoard::DrawRotateBillBoard(const DirectX::XMFLOAT4X4& cameramat, float angle)
{
	//�J�����s�񂩂�@�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalcBillBoardMatrix(cameramat);

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
bool CBillBoard::LoadTexTure(const char* filename)
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
		MessageBox(nullptr, "textureload error(CBILLBOARD LOADTEXTURE)", "error", MB_OK);
		return false;
	}

	return true;
}

