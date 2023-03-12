//#include "Stage.h"
//#include "CCamera.h"
//
//void Stage::ChipDraw(int z, int x) {
//
//	ID3D11DeviceContext* devcontext;
//
//	devcontext = GetDX11DeviceContext();
//
//	DirectX::XMFLOAT4X4 mtx;
//	DirectX::XMFLOAT3 trans = { MAPCHIPWIDTH * x * 0.5f,-MAPCHIPWIDTH,MAPCHIPWIDTH * z  * 0.5f };
//
//	//if (m_map[z][x] == 1)
//	//{
//	//	trans.y += 8.0f;
//	//}
//	//if (m_map[z][x] == 2)
//	//{
//	//	trans.y += 150.0f;
//	//}
//
//
//	//if (m_map[z][x] == 3)
//	//{
//	//	trans.y += 150.0f;
//	//}
//
//	DX11MtxTranslation(trans, mtx);
//
//	m_model.Draw(mtx);
//
//	//���[���h�ϊ��s��Z�b�g
//	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtx);
//
//	//�e�N�X�`���Z�b�g
//
//
//	//devcontext->Draw(4, //�`�悷�钷�_��
//	//	0);//���_�o�b�t�@�̍ŏ�����g��
//}
//
//
//
//bool Stage::Create() {
//	m_model.Init(
//		"assets/dice/BoidsAIBox.x",//�t�@�C����
//		"shader/vs.hlsl",          //���_�V�F�[�_�[
//		"shader/ps.hlsl",          //�s�N�Z���V�F�[�_�[
//		"assets/dice/"//�e�N�X�`���̊i�[�t�H���_
//	);
//
//	ID3D11Device* dev;
//	ID3D11DeviceContext* devcontext;
//
//	dev = GetDX11Device();
//	devcontext = GetDX11DeviceContext();
//
//	for (int i = 0; i < 5;i++)
//	{
//		bool sts;
//
//		sts = CreateSRVfromFile("assets/dice/BLACK.png", dev, devcontext, &m_tex[i], &m_srv[i]);
//
//
//		if (!sts) {
//			MessageBox(nullptr, "load tex error (stage)", "error", MB_OK);
//		}
//	}
//
//
//
//	bool sts = CreateVertexBuffer(dev, sizeof(Vertex), 4, m_v, &m_pVertexBuffer);
//	if (!sts) {
//		MessageBox(nullptr, "CreateVertexBuffer error(stage)", "error", MB_OK);
//	}
//
//	//���_�f�[�^�̒�`
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
//		{"NORMAL", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
//		{"TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
//
//	};
//
//	unsigned int numElements = ARRAYSIZE(layout);
//
//	//���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
//	sts = CreateVertexShader(dev,
//		"shader/vs.hlsl",
//		"main",
//		"vs_5_0",
//		layout,
//		numElements,
//		&m_pVertexShader,
//		&m_pVertexLayout);
//
//	if (!sts) {
//		MessageBox(nullptr, "CreateVertexShader error(stage)", "error", MB_OK);
//	}
//	//�s�N�Z���V�F�[�_�[�𐶐�
//	sts = CreatePixelShader(       //�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
//		dev,                       //�f�o�C�X�I�u�W�F�N�g
//		"shader/pstexcol.hlsl",
//		"main",
//		"ps_5_0",
//		&m_pPixelShader);
//	if (!sts) {
//		MessageBox(nullptr, "CreatePixelShader error(stage)", "error", MB_OK);
//	}
//	return sts;
//}
//
//void Stage::Destroy() {
//
//}
//bool Stage::Init()
//{
//	bool sts = Create();
//	return sts;
//}
//
//void Stage::Update()
//{
//
//}
//
//
//void Stage::Draw()
//{
//
//
//	ID3D11DeviceContext* devcontext;
//
//	devcontext = GetDX11DeviceContext();
//
//	//���_�o�b�t�@���Z�b�g����
//	unsigned int stride = sizeof(Vertex);
//
//	unsigned offset = 0;
//	devcontext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
//
//	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
//
//	devcontext->IASetInputLayout(m_pVertexLayout.Get());//���_�����C�A�E�g�Z�b�g
//
//	devcontext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);//���_�V�F�[�_�[���Z�b�g
//	devcontext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);//�s�N�Z���V�F�[�_�[���Z�b�g
//
//	for (int z = 0; z < MAPSIZEZ; z++) {
//		for (int x = 0; x < MAPSIZEX;x++) {
//
//			ChipDraw(z, x);
//
//
//		}
//
//	}
//
//}
//
//
//
//XMFLOAT2 Stage::GetMapChipNo(XMFLOAT4X4 mtx_x, XMFLOAT4X4 mtx_z)
//{
//	mtx_x._41 = (CCamera::GetInstance()->GetEye().x) / 15.0f;
//
//	mtx_z._43 = (CCamera::GetInstance()->GetEye().z + 100) / 15;
//
//	//printf("���ł�%f,���ł�%f", mtx_x._41, mtx_x._43);
//
//	return XMFLOAT2(mtx_x._41, mtx_z._43);
//	//return
//}
//
//int Stage::Getmap(int x, int y)
//{
//	return m_map[x][y];
//}
//
//void Stage::Finalize()
//{
//	Destroy();
//}
