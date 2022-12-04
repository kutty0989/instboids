#pragma once

#include	"uncopyable.h"
#include"ModelData.h"
// comptr
using Microsoft::WRL::ComPtr;

// ��`�N���X
class CHeight_Map : public Uncopyable {
public:
	// ���_�f�[�^
	struct Vertex {
		DirectX::XMFLOAT3 pos;		// ���W		
		DirectX::XMFLOAT4 color;	// �J���[float4 Pos : POSITION
		DirectX::XMFLOAT2 tex;		// �e�N�X�`��
	};




	// �萔�o�b�t�@
	struct ConstantBuffer
	{
		float tessellationAmount;
		float gcol;
		float padding[2];
	};

	// �萔�o�b�t�@
	struct ConstantBuffer2
	{

		float hight;
		float nbuf[3];

	};

	// �f�B�X�v���C�X�����g�}�b�v�̍���
	static float g_hight;
	static float g_devide;
	// �e�b�Z���[�V�����t�@�N�^
	static float g_tesselationamount;
	static float g_col;


	float	g_angle = 0.0f;

	XMFLOAT3 m_pos = {};
	XMFLOAT3 m_scale = {};
	XMFLOAT3 m_angle = {};


	DirectX::XMFLOAT4X4 s_mtx = {};
	DirectX::XMFLOAT4X4 p_mtx={};
	DirectX::XMFLOAT4X4 o_mtx={};

	

	//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
	struct SIMPLESHADER_CONSTANT_BUFFER
	{
		XMMATRIX mWVP;//���[���h�A�r���[�A�ˉe�̍����ϊ��s��
	};

	// �r���[�|�[�g�̃T�C�Y���Z�b�g
	bool SetViewPortSize(uint32_t width, uint32_t height) {

		ComPtr<ID3D11Buffer> CBViewPort;

		// �r���[�|�[�g�p�̒萔�o�b�t�@
		struct ConstantBufferViewPort {
			uint32_t	Width[4];			// �r���[�|�[�g��
			uint32_t	Height[4];			// �r���[�|�[�g����
		};

		// �r���[�|�[�g�萔�o�b�t�@�ɒl���Z�b�g
		bool sts = CreateConstantBufferWrite(
			GetDX11Device(),
			sizeof(ConstantBufferViewPort),
			&CBViewPort);
		if (!sts) {
			return false;
		}




		ConstantBufferViewPort cb;
		cb.Width[0] = width;
		cb.Height[0] = height;



		D3D11_MAPPED_SUBRESOURCE pData;

		HRESULT hr = GetDX11DeviceContext()->Map(CBViewPort.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		if (SUCCEEDED(hr)) {
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(ConstantBufferViewPort));
			GetDX11DeviceContext()->Unmap(CBViewPort.Get(), 0);
		}
		else {
			return false;
		}

		// ���_�V�F�[�_�[�ɃZ�b�g
		GetDX11DeviceContext()->VSSetConstantBuffers(9, 1, CBViewPort.GetAddressOf());

		return true;
	}

	// ��`�̏�����
	bool Init( DirectX::XMFLOAT3 color);



	// �`��
	void Draw();

	void UnInit();

	// �g��A�k��
	void SetScale(XMFLOAT3 scale);

	// �ʒu���Z�b�g
	void SetPosition(XMFLOAT3 pos);

	// Z����]
	void SetRotation(float x,float y,float z);

	void SetUV(XMFLOAT2* muv);
	
	void SetAlpha(float a);

	float HeightColor = 0.0f;

	double GetHeightColor(XMFLOAT2 playerpos);
	
	/// <summary>
	/// �����O�̃J���[���
	/// pad�̊p�x�̍s��̃J���[����Ԃ�
	/// </summary>
	/// <param name="playerpos"></param>
	/// <param name="pad_rigx"></param>
	/// <param name="pad_rigy"></param>
	/// <returns></returns>
	double GetGoHeightColor(XMFLOAT2 playerpos,float pad_rigx,float pad_rigy);




	/// <summary>
	/// �p�[���[�m�C�Y�쐬�N���X
	/// </summary>
	void NoiseCreate();

	std::vector<std::vector<double>> GetMap() { return vData; };

	void LoadMap(std::vector<std::vector<double>> loadmap);
	
	void ChangeMap();


	// ��`�̐i�s�������擾�i���摜��������ɍ���Ă��邱�Ƃ�O��j
	DirectX::XMFLOAT3 GetForward() {
		DirectX::XMFLOAT3 forward;
		forward.x = m_worldmtx._21;
		forward.y = m_worldmtx._22;
		forward.z = m_worldmtx._23;
		return forward;
	}

	// ��`�̉��������擾
	DirectX::XMFLOAT3 GetSide() {
		DirectX::XMFLOAT3 side;
		side.x = m_worldmtx._11;
		side.y = m_worldmtx._12;
		side.z = m_worldmtx._13;
		return side;
	}


	// ���_�f�[�^�X�V
	void updateVertex(DirectX::XMFLOAT3 color);
	// ���_�o�b�t�@�X�V
	void updateVbuffer();

	// �e�N�X�`���Z�b�g
	bool LoadTexture(const char* filename, int i) {
		// �e�N�X�`���ǂݍ���
		bool sts = CreateSRVfromFile(filename,
			GetDX11Device(),
			GetDX11DeviceContext(),
			&m_tex, &m_srv[i]);

		if (!sts) {
			std::string str("SRV �쐬�G���[ ");
			std::string strfile(filename);
			MessageBox(nullptr, (str + strfile).c_str(), "error", MB_OK);
			return sts;
		}
		return sts;
	}



	static CHeight_Map* GetInstance() {
		static CHeight_Map instance;
		return &instance;
	}


	float m_Alpha = 1.0f;


	XMFLOAT2 c_uv[4] = 
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> D3DShaderResourceView;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> D3DTexture;

	const int iPixSize = 512;//�c���s�N�Z����

   //�m�C�Y�����ݒ�
	const double dFrequency = 2.0;//���g�� ����������ƎR�����Ȃ��A�傫������ƍׂ���
	const int iOctaves = 7;//�I�N�^�[�u�@�X���[�Y�ɕω�

	static std::vector<std::vector<double> > vData;
	static std::vector<std::vector<double> > gData;
	static std::vector<byte> bufsrc;
private:
	DirectX::XMFLOAT4X4		m_worldmtx;				// ���[���h�ϊ��s��
	ComPtr<ID3D11Buffer>	m_vertexbuffer;			// ���_�o�b�t�@
	ComPtr<ID3D11Buffer>	m_indexbuffer;			// �C���f�b�N�X�o�b�t�@
	CHeight_Map::Vertex		m_vertex[4];			// ��`�S���_
	int					m_width = iPixSize;				// ��
	int					m_height = iPixSize;				// ����
	ComPtr<ID3D11ShaderResourceView> m_srv[5];			// SRV			// �����e�N�X�`��
	ComPtr<ID3D11Resource> m_tex;					// �e�N�X�`�����\�[�X

	ID3D11Buffer* g_pConstantBuffer = nullptr;			// �萔�o�b�t�@
	ID3D11Buffer* g_pConstantBuffer2 = nullptr;			// �萔�o�b�t�@


	double col;//�v���C���[�̏ꏊ�̃J���[�������
	double gocol;//�����Ă�����̍������
	float defcol;//�v���C���[�̏ꏊ�ƍs��̍�
	float goangle;//�v���C���[�ƍs��̊p�x
};