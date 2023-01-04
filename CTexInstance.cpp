#include"CTexInstance.h"
#include"shaderhashmap.h"
#include"CCamera.h"

using namespace DirectX;


// �g�p���钸�_�V�F�[�_�[��
const char* vsfilenamein[] = {
	"shader/instancevs.hlsl"
};

// �g�p����s�N�Z���V�F�[�_�[��
const char* psfilenamein[] = {
	"shader/instanceps.hlsl"
};

void CTexInstance::Init(int num, const char* filename)
{	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// �f�o�C�X���擾
	ID3D11Device* device;
	device = GetDX11Device();


	LoadTexture(filename);

	mInstanceNum = num;


	// �r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = 1920;
	vp.Height = 1080;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	// �V�F�[�_�̐ݒ�
	ID3DBlob* pCompileVS = NULL;
	ID3DBlob* pCompilePS = NULL;
	D3DCompileFromFile(L"shader/instancevs.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	device->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, mVertexShader.GetAddressOf());
	D3DCompileFromFile(L"shader/instancevs.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	device->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, mPixelShader.GetAddressOf());

	
	// ���_���C�A�E�g
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};

	device->CreateInputLayout(layout, _countof(layout), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), mInputLayout.GetAddressOf());
	pCompileVS->Release();
	pCompilePS->Release();



	//�|���S���̒��_�f�[�^�̍쐬�Ƃ��̃o�b�t�@�̐ݒ�
	
		VERTEX	v[4] = {
			// ���W													// �J���[	// UV	
			XMFLOAT3(-1.0f ,1.0 , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),	XMFLOAT2(0.0f,0.0f),
			XMFLOAT3(-1.0 ,	-1.0f, 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(1.0f,0.0f),
			XMFLOAT3(1.0 ,1.0 , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(0.0f,1.0f),
			XMFLOAT3(1.0 ,-1.0 , 0.0f),	XMFLOAT4(1.0f,1.0f,1.0f,1.0f),		XMFLOAT2(1.0f,1.0f),
			};

	mDrawNum = sizeof(v) / sizeof(v[0]);

	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = v;
	device->CreateBuffer(&bd, &vertexData, mVertexBuffer.GetAddressOf());

	// �C���f�b�N�X�f�[�^�p�o�b�t�@�̐ݒ�
	int indexes[] =
	{
		0,1,2,
		2,1,3,
	};
	mDrawNum = sizeof(indexes) / sizeof(indexes[0]);
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indexes;
	device->CreateBuffer(&bd_index, &indexData, mIndexBuffer.GetAddressOf());


	//�C���X�^���X�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_instance;
	bd_instance.Usage = D3D11_USAGE_DYNAMIC;
	bd_instance.ByteWidth = sizeof(PerInstanceData) * mInstanceNum;
	bd_instance.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bd_instance.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd_instance.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd_instance.StructureByteStride = sizeof(PerInstanceData);
	device->CreateBuffer(&bd_instance, NULL, mPerInstanceBuffer.GetAddressOf());

	//�C���X�^���X�p�̃��\�[�X�r���[���쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.BufferEx.NumElements = mInstanceNum;
	device->CreateShaderResourceView(mPerInstanceBuffer.Get(), &srvDesc, mShaderResourceView.GetAddressOf());

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
	ID3D11Buffer* bufs[] = { mVertexBuffer.Get() };
	UINT stride[] = { sizeof(VERTEX) };
	UINT offset[] = { 0 };
	devcontext->IASetVertexBuffers(0, sizeof(bufs) / sizeof(bufs[0]), bufs, stride, offset);
	devcontext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	devcontext->IASetInputLayout(mInputLayout.Get());

	auto camera = CCamera::GetInstance()->GetCameraMatrix();
	
	mView = DirectX::XMLoadFloat4x4(&camera);

	auto proj = CCamera::GetInstance()->GetProjectionMatrix();
	mProj = DirectX::XMLoadFloat4x4(&proj);
	mScale = XMMatrixScalingFromVector(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	mRotation = XMMatrixRotationX(0.0f) * XMMatrixRotationY(0.0f) * XMMatrixRotationZ(90.0f);

}

bool CTexInstance::Update(XMFLOAT3 pos[])
{

	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	// �p�����[�^�̎󂯓n��
	D3D11_MAPPED_SUBRESOURCE pdata;
	devcontext->Map(mPerInstanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
	PerInstanceData* instanceData = (PerInstanceData*)(pdata.pData);

	//instanceData.tex = { 1.0f, 1.0f };
	for (int i = 0; i < mInstanceNum; i++)
	{
		//�Ƃ肠�������[�v�ϐ��g���Ĉړ�
		float xPos = pos->x;
		float yPos = pos->y;
		XMMATRIX move = XMMatrixTranslation(xPos, yPos, 1.0f);
		//�s������Z�b�g
		instanceData[i].matrix = XMMatrixTranspose(mScale * mRotation * move);//*mView* mProj);
		//�F�����Z�b�g
		instanceData[i].color = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);

	}
	//�e�N�X�`���[���s�N�Z���V�F�[�_�[�ɓn��
	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());

	devcontext->Unmap(mPerInstanceBuffer.Get(), 0);

	//ID3D11DeviceContext* devcontext;
	//devcontext = GetDX11DeviceContext();

	//// �f�o�C�X���擾
	//ID3D11Device* device;
	//device = GetDX11Device();

	//float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	//devcontext->ClearRenderTargetView(mRenderTargetView.Get(), clearColor);

	//RenderInstancing();


//	mInput->SetPreBuffer();
	return true;
}

void CTexInstance::RenderInstancing()
{

	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();
	// �f�o�C�X���擾
	ID3D11Device* device;
	device = GetDX11Device();

	
	devcontext->VSSetShader(mVertexShader.Get(), NULL, 0);
	devcontext->GSSetShader(nullptr, nullptr, 0);
	devcontext->HSSetShader(nullptr, nullptr, 0);
	devcontext->DSSetShader(nullptr, nullptr, 0);
	devcontext->PSSetShader(mPixelShader.Get(), NULL, 0);

	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcontext->VSSetShaderResources(8, 1, mShaderResourceView.GetAddressOf());
	devcontext->PSSetShaderResources(8, 1, mShaderResourceView.GetAddressOf());
	devcontext->VSSetShaderResources(9, 1, m_srv.GetAddressOf());
	devcontext->PSSetShaderResources(9, 1, m_srv.GetAddressOf());
	// �`����s
	devcontext->DrawIndexedInstanced(mDrawNum, mInstanceNum, 0, 0, 0);
}

CTexInstance::~CTexInstance() {}

