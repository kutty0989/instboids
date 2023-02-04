#include"CHeight_Map.h"
#include"Application.h"
#include"Seiha.h"
#include"noise.h"
#include"player.h"
#define debuglog(a) std::cout<<a<<std::endl;

float CHeight_Map::g_hight;
float CHeight_Map::g_tesselationamount;
float CHeight_Map::g_col;
bool CHeight_Map::mapsave = false;
bool CHeight_Map::mapload = false;
float CHeight_Map::ScaleMap = 2.0f;
std::vector<std::vector<double> > CHeight_Map::vData;
std::vector<std::vector<double> > CHeight_Map::gData;
std::vector<byte> CHeight_Map::bufsrc;
// comptr
using Microsoft::WRL::ComPtr;


// �g�p���钸�_�V�F�[�_�[��
const char* vsfilename[] = {
	"shader/VSTess+Disp.hlsl"
};

// �g�p����s�N�Z���V�F�[�_�[��
const char* psfilename[] = {
	"shader/psheight.hlsl"
};

// �g�p����n���V�F�[�_�[��
const char* hullfilename[] = {
	"shader/HSTess+Disp.hlsl"
};
// �g�p����h���C���V�F�[�_�[��
const char* dsfilename[] = {
	"shader/DSTess+Disp.hlsl"
};

//float cosC;
//float sinC;

// ��`�̏�����
bool CHeight_Map::Init(DirectX::XMFLOAT3 color) {


	bool sts;

	DX11MtxIdentity(m_worldmtx);// �����p��

	// �f�o�C�X���擾
	ID3D11Device* device;
	device = GetDX11Device();


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
		vsfilename[0],			// ���_�V�F�[�_�[�t�@�C����
		layout,					// ���_���C�A�E�g
		numElements);			// �G�������g��
	if (!sts) {
		MessageBox(nullptr, "SetVertexShader error", "error", MB_OK);
		return false;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error", "error", MB_OK);
		return false;
	}

	// �n���V�F�[�_�[�𐶐�
	sts = ShaderHashmap::GetInstance()->SetHullShader(hullfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetHullShader error", "error", MB_OK);
		return false;
	}

	// �h���C���V�F�[�_�[�𐶐�
	sts = ShaderHashmap::GetInstance()->SetDomainShader(dsfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetDomainShader error", "error", MB_OK);
		return false;
	}

	// ���_�o�b�t�@�𐶐�
	sts = CreateVertexBufferWrite(
		device,						// �f�o�C�X�I�u�W�F�N�g
		sizeof(CHeight_Map::Vertex),		// �P���_������o�C�g��
		4,							// ���_��
		m_vertex,					// ���_�f�[�^�i�[�������擪�A�h���X
		&m_vertexbuffer				// ���_�o�b�t�@
	);
	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return false;
	}


	// �C���f�b�N�X�o�b�t�@�𐶐�
	uint32_t index[6] = { 0,1,2,
						 2,1,3 };

	sts = CreateIndexBuffer(
		device,						// �f�o�C�X�I�u�W�F�N�g
		6,							// �C���f�b�N�X��
		index,						// �C���f�b�N�X�i�[�������擪�A�h���X
		m_indexbuffer.GetAddressOf()				// �C���f�b�N�X�o�b�t�@
	);
	if (!sts) {
		MessageBox(nullptr, "CreateIndexBuffer error", "error", MB_OK);
		return false;
	}

	// �萔�o�b�t�@����
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer), &g_pConstantBuffer);
	if (!sts) {
		MessageBox(nullptr, "CreateConstantBuffer error", "error", MB_OK);
		return false;
	}

	// �萔�o�b�t�@����
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer2), &g_pConstantBuffer2);
	if (!sts) {
		MessageBox(nullptr, "CreateConstantBuffer2 error", "error", MB_OK);
		return false;
	}
	sts = CreateConstantBuffer(GetDX11Device(), sizeof(BlendBuffer), &g_pConstantBlendBuffer);
	if (!sts) {
		MessageBox(nullptr, "BlendBuffer error", "error", MB_OK);
		return false;
	}

	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	g_tesselationamount = 64;
	ConstantBuffer cb;
	cb.tessellationAmount = g_tesselationamount;//��������n��
	devcontext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);	// �R���X�^���g�o�b�t�@�X�V
	devcontext->HSSetConstantBuffers(7, 1, &g_pConstantBuffer);				// HULL�V�F�[�_�[�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g
	
	g_hight = 500.0f;
	ConstantBuffer2 cb2;
	cb2.hight = g_hight;//�����ϐ���n��
	devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// �R���X�^���g�o�b�t�@�X�V
	devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DS�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g


	///////////////�QD�摜�̐���///////////////////
	//�e�N�X�`���̍쐬
	D3D11_TEXTURE2D_DESC td;
	td.Width = iPixSize;
	td.Height = iPixSize;
	td.MipLevels = 1;//���ƂȂ�e�N�X�`���̃T�C�Y�𔼕��ɏk���������́@�������ʂ͑����邪�e�N�X�`�����k�����ăT���v�����O����Ď��R�Ɂ@�g��Ȃ��̂łP
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DYNAMIC;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	td.MiscFlags = 0;
	HRESULT hr = device->CreateTexture2D(&td, nullptr, &D3DTexture);
	if (FAILED(hr))
		return hr;

	//�e�N�X�`�������ւ�
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//�p�[�����m�C�Y�v�Z
	Noise perlin;
	std::vector<std::vector<double> > vecData(iPixSize, std::vector<double>(iPixSize));//vecData[iPixSize][iPixSize];
	double dFrequencyX = iPixSize / dFrequency;
	double dFrequencyY = dFrequencyX;
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			vecData[x][y] = perlin.Octave(x / dFrequencyX, y / dFrequencyY, 0.0, iOctaves);
			
		}
	}
	gData = vecData;
	//�p�[�����m�C�Y�v�Z���ʂ��e�N�X�`���ɔ��f
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//�r�b�g�}�b�v�����ŏ�����
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			gData[x][y] = 0.0f;
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(vecData[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(vecData[x][y] * 255);//Green
			//srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(vecData[x][y] * 255);//Blue
		}
	}


	
	vData = vecData;//�s�N�Z�����ۑ�
	//gData = vData;
	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);

	//�V�F�[�_���\�[�X�r���[�̍쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	sts = device->CreateShaderResourceView(D3DTexture.Get(), &srv, &D3DShaderResourceView);
	if (FAILED(sts))
		return sts;

	///////�摜�����I��
	
	// �r���[�|�[�g�T�C�Y�Z�b�g
	SetViewPortSize(DX11GetScreenWidth(), DX11GetScreenHeight());

	// ���_������
	updateVertex(color);
	return true;
}
static int blendtex = 0;
static bool noiseCreateflg = false;

// �`��
void CHeight_Map::Draw() {

	if (noiseCreateflg)
	{
		NoiseCreate();
		noiseCreateflg = false;
	}
	TurnOffZbuffer();
	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	{
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

		ImGui::Begin("Ground");
		ImGui::SetNextWindowSize(ImVec2(300, 300));
	
		ImGui::SliderFloat("Height", &g_hight, 0.0f, 1000.0f);
		ImGui::SliderFloat("tesslation", &g_tesselationamount, 0.0f, 64.0f);

		ImGui::InputDouble("Frequency", &dFrequency);
		ImGui::DragInt("iOctaves", &iOctaves);
		ImGui::DragFloat("scale", &ScaleMap);
		
		if (ImGui::Button("RandomCreate"))
		{
			noiseCreateflg = true;
		}
		if (ImGui::Button("MapSave"))
		{
			mapsave = true;
		}

		if (ImGui::Button("MapLoad"))
		{
			mapload = true;
		}

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

	DX11MtxScale(m_scale.x, m_scale.y, m_scale.z, s_mtx);
	DX11MtxTranslation(m_pos, p_mtx);
	DX11MtxRotationX(m_angle.x, o_mtx);//��]�s��
	//DX11MtxRotationY(m_angle.y, o_mtx);//��]�s��
	//DX11MtxRotationZ(m_angle.z, o_mtx);//��]�s��
	DirectX::XMFLOAT4X4 mtx;
	DX11MtxMultiply(mtx, s_mtx, o_mtx);
	DX11MtxMultiply(m_worldmtx, mtx, p_mtx);//�X�P�[���@���@��]�@���@�ړ�

	//// ���W�ϊ��p�̍s����Z�b�g
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, m_worldmtx);

	unsigned int stride = sizeof(CHeight_Map::Vertex);	// �X�g���C�h���Z�b�g�i�P���_������̃o�C�g���j
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

	//�v���~�e�B�u�g�|���W�[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	// ���_���C�A�E�g�擾
	ID3D11InputLayout* layout;
	layout = ShaderHashmap::GetInstance()->GetVertexLayout(vsfilename[0]);

	// ���_�t�H�[�}�b�g���Z�b�g
	devcontext->IASetInputLayout(layout);

	//�s�N�Z���V�F�[�_�[��TXTUREE�@SRV���Z�b�g	

	SetTexture();

	devcontext->PSSetShaderResources(0, 1, D3DShaderResourceView.GetAddressOf());///�摜�P����PS�Z�b�g�@�`�悷��

	//devcontext->PSSetShaderResources(4, 1, m_srv[3].GetAddressOf());///�p�[���[�m�C�Y��PS�Z�b�g�@�`�悷��
	//�h���C���V�F�[�_�[��TXTUREE�@SRV���Z�b�g
	devcontext->DSSetShaderResources(0, 1, D3DShaderResourceView.GetAddressOf());//�p�[���m�C�Y��DS�ɃZ�b�g���������

	// ���_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[�擾
	ID3D11VertexShader* vs;
	vs = ShaderHashmap::GetInstance()->GetVertexShader(vsfilename[0]);
	ID3D11PixelShader* ps;
	ps = ShaderHashmap::GetInstance()->GetPixelShader(psfilename[0]);

	//�n���V�F�[�_�[
	ID3D11HullShader* hull;
	hull = ShaderHashmap::GetInstance()->GetHullShader(hullfilename[0]);
	//�h���C���V�F�[�_�[�o�^
	ID3D11DomainShader* ds;
	ds = ShaderHashmap::GetInstance()->GetDomainShader(dsfilename[0]);

	//�e�N�X�`���[���h���C���V�F�[�_�[�ɓn��
	devcontext->DSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());
	//�e�N�X�`���[���s�N�Z���V�F�[�_�[�ɓn��
	devcontext->PSSetSamplers(0, 1, CDirectXGraphics::GetInstance()->GetSampState());


	ConstantBuffer cb;
	cb.tessellationAmount = g_tesselationamount;//��������n��
	cb.gcol = g_col;//��������n��
	devcontext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);	// �R���X�^���g�o�b�t�@�X�V
	devcontext->HSSetConstantBuffers(7, 1, &g_pConstantBuffer);				// HULL�V�F�[�_�[�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g
	devcontext->PSSetConstantBuffers(7, 1, &g_pConstantBuffer);				// HULL�V�F�[�_�[�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g


	ConstantBuffer2 cb2;
	cb2.hight = g_hight;
	devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// �R���X�^���g�o�b�t�@�X�V
	devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DS�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g


	//4�p�`�`��
	devcontext->VSSetShader(vs, nullptr, 0);
	devcontext->GSSetShader(nullptr, nullptr, 0);
	devcontext->HSSetShader(hull, nullptr, 0);
	devcontext->DSSetShader(ds, nullptr, 0);
	devcontext->PSSetShader(ps, nullptr, 0);


	//// �h���[�R�[�����s
	devcontext->DrawIndexed(
		6,						// �C���f�b�N�X��
		0,						// �J�n�C���f�b�N�X
		0);						// ����_�C���f�b�N�X
	TurnOnZbuffer();
}

void CHeight_Map::UnInit() {
	ID3D11VertexShader* vs;
	vs = ShaderHashmap::GetInstance()->GetVertexShader(vsfilename[0]);
	ID3D11PixelShader* ps;
	ps = ShaderHashmap::GetInstance()->GetPixelShader(psfilename[0]);
	ID3D11HullShader* hull;
	hull = ShaderHashmap::GetInstance()->GetHullShader(hullfilename[0]);
	ID3D11DomainShader* ds;
	ds = ShaderHashmap::GetInstance()->GetDomainShader(dsfilename[0]);
	// ���_���C�A�E�g�擾
	ID3D11InputLayout* layout;
	layout = ShaderHashmap::GetInstance()->GetVertexLayout(vsfilename[0]);



	// ���_�V�F�[�_�[���
	if (vs) {
		vs->Release();
		vs = nullptr;
	}

	// �s�N�Z���V�F�[�_�[���
	if (ps) {
		ps->Release();
		ps = nullptr;
	}
	// �n���V�F�[�_�[���
	if (hull) {
		hull->Release();
		hull = nullptr;
	}
	// �s�N�Z���V�F�[�_�[���
	if (ds) {
		ds->Release();
		ds = nullptr;
	}

	// ���_���C�A�E�g���
	if (layout) {
		layout->Release();
		layout = nullptr;
	}
}


//go ���̍��W�l
//to�@�s��̍��W�l
//ratio�@���݂̐i�s�����@0.0f�`1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}


// �g��A�k��
void CHeight_Map::SetScale(XMFLOAT3 scale) {
	m_scale = scale;
}

// �ʒu���Z�b�g
void CHeight_Map::SetPosition(XMFLOAT3 pos) {
	m_pos = pos;
}

// Z����]
void CHeight_Map::SetRotation(float x,float y,float z) {
	m_angle.x= x;
	m_angle.y= y;
	m_angle.z= z;
}
void CHeight_Map::SetUV(XMFLOAT2* muv)
{
	c_uv[0] = muv[0];
	c_uv[1] = muv[1];
	c_uv[2] = muv[2];
	c_uv[3] = muv[3];

}

void CHeight_Map::SetAlpha(float a)
{
	m_Alpha = a;

}



// ���_�f�[�^�X�V
void CHeight_Map::updateVertex(DirectX::XMFLOAT3 color) {

	

		CHeight_Map::Vertex	v[4] = {
			// ���W													// �J���[	// UV	
			XMFLOAT3(-m_width / 2.0f,	 m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[0],
			XMFLOAT3(m_width / 2.0f,	 m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[1],
			XMFLOAT3(-m_width / 2.0f,	 -m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[2],
			XMFLOAT3(m_width / 2.0f,	 -m_height / 2.0f,0.0f),	XMFLOAT4(color.x,color.y,color.z,m_Alpha),		c_uv[3],
		};
		for (int i = 0; i < 4; i++) {
			m_vertex[i] = v[i];
		}
		//}
	
}

// ���_�o�b�t�@�X�V
void CHeight_Map::updateVbuffer() {
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetDX11DeviceContext()->Map(m_vertexbuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(m_vertex), sizeof(CHeight_Map::Vertex) * 4);
		GetDX11DeviceContext()->Unmap(m_vertexbuffer.Get(), 0);
	}
}


void CHeight_Map::NoiseCreate()
{
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//�e�N�X�`�������ւ�
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//�p�[�����m�C�Y�v�Z
	Noise perlin;
	std::vector<std::vector<double> > vecData(iPixSize, std::vector<double>(iPixSize));//vecData[iPixSize][iPixSize];
	double dFrequencyX = iPixSize / dFrequency;
	double dFrequencyY = dFrequencyX;
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			vecData[x][y] = perlin.Octave(x / dFrequencyX, y / dFrequencyY, 0.0, iOctaves);


		}
	}
	
	//�p�[�����m�C�Y�v�Z���ʂ��e�N�X�`���ɔ��f
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//�r�b�g�}�b�v�����ŏ�����
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
	
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(vecData[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(vData[x][y] * 255);//Green
		//	srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(vecData[x][y] * 255);//Blue
		}
	}
	vData = vecData;
	//gData = vData;

	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);


}

std::vector<std::vector<double>> CHeight_Map::CreateOnly()
{
	//�p�[�����m�C�Y�v�Z
	Noise perlin;
	std::vector<std::vector<double> > vecData(iPixSize, std::vector<double>(iPixSize));//vecData[iPixSize][iPixSize];
	double dFrequencyX = iPixSize / dFrequency;
	double dFrequencyY = dFrequencyX;
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			vecData[x][y] = perlin.Octave(x / dFrequencyX, y / dFrequencyY, 0.0, iOctaves);
		}
	}
	vData = vecData;

	return vecData;
}

void CHeight_Map::LoadMap(std::vector<std::vector<double>> loadmap)
{

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//�e�N�X�`�������ւ�
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


	//�p�[�����m�C�Y�v�Z���ʂ��e�N�X�`���ɔ��f
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//�r�b�g�}�b�v�����ŏ�����
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(loadmap[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(loadmap[x][y] * 255);//Green
		//	srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(loadmap[x][y] * 255);//Blue
		}
	}

	vData = loadmap;
	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);

}

void CHeight_Map::BlendMap(std::vector<std::vector<double>> loadmap)
{
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//�e�N�X�`�������ւ�
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//�r�b�g�}�b�v�����ŏ�����
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			//2���̒n�ʂ̍����������ԂŐ��`�⊮
			auto blendcolor = LeapID<double>(static_cast<byte>(vData[x][y]*255), static_cast<byte>(loadmap[x][y]*255),Seiha::pertime);
			srcData[(x + y * iPixSize) * 4] = blendcolor;//Red
		
			gData[x][y] = blendcolor;
		}
	}


	if (Seiha::pertime == 0.0f)
	{
		vData = gData;
		
	}
	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);
}

void CHeight_Map::ChangeMap()
{

	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();


	//�e�N�X�`�������ւ�
	D3D11_MAPPED_SUBRESOURCE msr;
	devcontext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


	//�p�[�����m�C�Y�v�Z���ʂ��e�N�X�`���ɔ��f
	std::vector<byte> srcData(iPixSize * iPixSize * 4, 0);//srcData[iPixSize * iPixSize * 4] = {0};//�r�b�g�}�b�v�����ŏ�����
	for (int x = 0; x < iPixSize; x++)
	{
		for (int y = 0; y < iPixSize; y++)
		{
			srcData[(x + y * iPixSize) * 4] = static_cast<byte>(vData[x][y] * 255);//Red
		//	srcData[(x + y * iPixSize) * 4 + 1] = static_cast<byte>(gData[x][y] * 255);//Green
		//	srcData[(x + y * iPixSize) * 4 + 2] = static_cast<byte>(vData[x][y] * 255);//Blue
		}
	}
	vData = vData;

	memcpy(msr.pData, &srcData.front(), srcData.size());
	devcontext->Unmap(D3DTexture.Get(), 0);

}





static int multitex = 0;
static bool soil = false;
static bool snow = false;
static bool grass = false;

int CHeight_Map::onetex = 0;
int CHeight_Map::twotex = 0;
int CHeight_Map::theretex = 0;

float CHeight_Map::blendone = 1.0f;
float CHeight_Map::blendtwo = 1.0f;
float CHeight_Map::blendthere = 1.0f;
float CHeight_Map::blendfour = 1.0f;


void CHeight_Map::SetTexture()
{


	// �f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* devcontext;
	devcontext = GetDX11DeviceContext();

	if (g_col == 0)
	{
		{
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

			ImGui::Begin("BaseTex_One");
			ImGui::SetNextWindowSize(ImVec2(300, 400));
			//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

			ImGui::Checkbox("soil", &soil);
			ImGui::Checkbox("snow", &snow);
			ImGui::Checkbox("grass", &grass);
			ImGui::End();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		if (soil)
		{
			onetex = 1;
			g_col = 1;
		}
		else if (snow)
		{
			g_col = 1;
			onetex = 2;
		}
		else if (grass)
		{
			g_col = 1;
			onetex = 3;
		}
	}
	if (g_col >= 1)
	{
		devcontext->PSSetShaderResources(1, 1, m_srv[onetex - 1].GetAddressOf());///�����ɂ���ĕς���摜�Q��PS�Z�b�g�@�`�悷��

		if (g_col == 1)
		{
			soil = false;
			snow = false;
			grass = false;

			{
				ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

				ImGui::Begin("BaseTex_One");
				ImGui::SetNextWindowSize(ImVec2(300, 400));
				//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

				ImGui::Checkbox("soil", &soil);
				ImGui::Checkbox("snow", &snow);
				ImGui::Checkbox("grass", &grass);
				ImGui::End();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			if (soil)
			{
				twotex = 1;
				g_col = 2;
			}
			else if (snow)
			{
				g_col = 2;
				twotex = 2;
			}
			else if (grass)
			{
				g_col = 2;
				twotex = 3;
			}
		}
	}
	if (g_col >= 2)
	{
		devcontext->PSSetShaderResources(2, 1, m_srv[twotex - 1].GetAddressOf());///�����ɂ���ĕς���摜�Q��PS�Z�b�g�@�`�悷��

		if (g_col == 2)
		{
			soil = false;
			snow = false;
			grass = false;

			{
				ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
				ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

				ImGui::Begin("BaseTex_TWO");
				ImGui::SetNextWindowSize(ImVec2(300, 400));
				//	int it = Player::GetInstance()->iseconds % Player::GetInstance()->judge_seconds;

				ImGui::Checkbox("soil", &soil);
				ImGui::Checkbox("snow", &snow);
				ImGui::Checkbox("grass", &grass);
				ImGui::End();
				ImGui::PopStyleColor();
				ImGui::PopStyleColor();

			}
			if (soil)
			{
				theretex = 1;
				g_col = 3;
			}
			else if (snow)
			{
				g_col = 3;
				theretex = 2;
			}
			else if (grass)
			{
				g_col = 3;
				theretex = 3;
			}
		}
	}
	if (g_col >= 3)
	{
		soil = false;
		snow = false;
		grass = false;
		devcontext->PSSetShaderResources(3, 1, m_srv[theretex - 1].GetAddressOf());///�����ɂ���ĕς���摜�Q��PS�Z�b�g�@�`�悷��

		g_col = 4;
	
	}
	if (g_col >= 4)
	{
		
		
		cb10.blendone = blendone;//�����ϐ���n��
		cb10.blendtwo = blendtwo;//�����ϐ���n��
		cb10.blendthere = blendthere;//�����ϐ���n��
		cb10.blendfour = blendfour;//�����ϐ���n��
		devcontext->UpdateSubresource(g_pConstantBlendBuffer, 0, nullptr, &cb10, 0, 0);		// �R���X�^���g�o�b�t�@�X�V
		devcontext->PSSetConstantBuffers(10, 1, &g_pConstantBlendBuffer);					// DS�փR���X�^���g�o�b�t�@��b0���W�X�^�փZ�b�g

	//	soil = false;
	//	snow = false;
	//	grass = false;
	//	devcontext->PSSetShaderResources(4, 1, m_srv[theretex - 1].GetAddressOf());///�����ɂ���ĕς���摜�Q��PS�Z�b�g�@�`�悷��

		{
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

			ImGui::Begin("BlendTex");
			ImGui::SetNextWindowSize(ImVec2(300, 400));
			ImGui::DragFloat("one", &blendone);
			ImGui::DragFloat("two", &blendtwo);
	
			ImGui::End();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
	//	if (soil)
	//	{
	//		theretex = 1;
	//		g_col = 2;
	//	}
	//	else if (snow)
	//	{
	//		g_col = 2;
	//		theretex = 2;
	//	}
	//	else if (grass)
	//	{
	//		g_col = 2;
	//		theretex = 3;
	//	}
	//
	}

}

double CHeight_Map::GetHeightColor(XMFLOAT2 playerpos)
{
	int p_posx = (int)playerpos.x;//�z��T�����邽�߂ɃL���X�g�Ō��𗎂Ƃ�
	int p_posy = (int)playerpos.y;

	double col = vData[p_posx][p_posy];//���Ƃ����l�Ō��Ă���
	double xcol = vData[p_posx+1][p_posy];//�������̂P��
	double ycol = vData[p_posx][p_posy+1];//�������̂P��
	
	float xf = playerpos.x;
	float yf = playerpos.y;

	float xx = xf - p_posx;//�����������l�����Ă���
	float yy = yf - p_posy;

	//���������������`�⊮�ō��������߂�
	float xxcol = LeapID<float>(col, xcol, xx);
	float yycol = LeapID<float>(col, ycol, yy);

	col = (xxcol + yycol) / 2.0f;//�������Ƃ������𑫂��ĂP�_�́i�J���[�j����lar

	
	return col;
}


double CHeight_Map::GetGoHeightColor(XMFLOAT2 playerpos,float anglex, float angley)
{
	float to_pposx = playerpos.x + anglex;
	float to_pposy = playerpos.y - angley;
	double tocol =  GetHeightColor(XMFLOAT2(to_pposx,to_pposy));//�s��̃J���[�@����

	return tocol;
}
