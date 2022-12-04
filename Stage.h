//#pragma once
//#include<wrl/client.h>
//#include"vertexproto.h"
//#include"dx11mathutil.h"
//#include"DX11Settransform.h"
//#include"DX11util.h"
//#include"CModel.h"
//
//using Microsoft::WRL::ComPtr;
//
//class Stage {
//	CModel m_model;
//
//	static constexpr float MAPCHIPWIDTH = 30.0f;
//
//	static constexpr uint16_t MAPSIZEX = 9;
//	static constexpr uint16_t MAPSIZEZ = 9;
//	ComPtr<ID3D11ShaderResourceView> m_srv[5];
//	ComPtr<ID3D11Resource> m_tex[5];
//
//	ModelData				m_assimpfile;					// assimpfile
//
//
//	//���ʂ�`�悷��
//	ComPtr<ID3D11Buffer> m_pVertexBuffer;//���_�o�b�t�@
//	ComPtr<ID3D11Buffer> m_pIndexBuffer;//�C���f�b�N�X�o�b�t�@
//	ComPtr<ID3D11VertexShader> m_pVertexShader;//���_�V�F�[�_�[
//	ComPtr<ID3D11PixelShader> m_pPixelShader;//�s�N�Z���V�F�[�_�[
//	ComPtr<ID3D11InputLayout> m_pVertexLayout;//���_���C�A�E�g
//public:
//	//�}�b�v�z�u
//	int m_map[MAPSIZEX][MAPSIZEZ] = {
//
//		//-4 -3 -2 -1 0 1 2 3 4
//		{1,2,2,2,2,2,2,2,1},//2:�O�[ 2:�`���L�@�Q�F�p�[�@�R�F�Ȃ�
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//		{1,2,2,2,2,2,2,2,1},
//
//	};
//private:
//
//
//	//���ʃ`�b�v
//	Vertex m_v[4] = {
//		{DirectX::XMFLOAT3(-MAPCHIPWIDTH / 2.0f,0,MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(1.0f,0.0f)},
//		{DirectX::XMFLOAT3(MAPCHIPWIDTH / 2.0f,0,MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(1.0f,1.0f)},
//		{DirectX::XMFLOAT3(-MAPCHIPWIDTH / 2.0f,0,-MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(0.0f,0.0f)},
//		{DirectX::XMFLOAT3(MAPCHIPWIDTH / 2.0f,0,-MAPCHIPWIDTH / 2.0f),DirectX::XMFLOAT3(0.0f,1.0f,0.0f),DirectX::XMFLOAT2(0.0f,1.0f)}
//	};
//
//	const char* m_texfilename[5] =
//	{
//
//		"assets/dice/RED_SCISSOR.png",
//		"assets/dice/GREEN_STONE.png",
//		"assets/dice/BLUE_PAPER.png",
//		"assets/dice/BLACK.png",
//			"assets/white.bmp"
//	};
//
//	void ChipDraw(int z, int x);
//public:
//	//�R�s�[�E����͋֎~���邪�A���[�u�͋�����
//	Stage(const Stage&) = delete;
//	Stage& operator = (const Stage&) = delete;
//
//	//�f�t�H���g
//	Stage(Stage&&) = default;
//	Stage() = default;
//	Stage& operator = (Stage&&) = default;
//
//
//	bool Create();   //����
//	void Destroy();//�j��
//	bool Init();//��������
//	void Update();//�X�V
//	void Draw();//�`��
//	void Draw(XMFLOAT4X4& mtxworld);//�`��
//	void Finalize();//�I������
//
//	int Getmap(int x, int y);
//
//	XMFLOAT2 GetMapChipNo(XMFLOAT4X4 mtx_x, XMFLOAT4X4 mtx_z);
//};