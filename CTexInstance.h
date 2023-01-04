#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <wrl/client.h>
#include"DX11util.h"
#include"Shader.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
//�E�B���h�E�̉���
static const UINT WindowWidth = 500;
//�E�B���h�E�̏c��
static const UINT WindowHeight = 400;

// ��̒��_�����i�[����\����
struct VERTEX
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;	// �J���[
	DirectX::XMFLOAT2 tex;		// �e�N�X�`��
};

struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX gWVP;
};

struct PerInstanceData
{
	DirectX::XMMATRIX matrix;
	DirectX::XMVECTOR color;

};



class CTexInstance
{
public:

	// �e�N�X�`���Z�b�g
	bool LoadTexture(const char* filename) {
		// �e�N�X�`���ǂݍ���
		bool sts = CreateSRVfromFile(filename,
			GetDX11Device(),
			GetDX11DeviceContext(),
			&m_tex, &m_srv);
		if (!sts) {
			std::string str("SRV �쐬�G���[ ");
			std::string strfile(filename);
			MessageBox(nullptr, (str + strfile).c_str(), "error", MB_OK);
			return sts;
		}
		return sts;
	}

	void Init(int num, const char* filename);
	bool Update(XMFLOAT3 pos[]);
	void RenderInstancing();
	~CTexInstance();

	XMFLOAT2 c_uv[4] =
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};

private:
	void Render();

	//DirectX�ɕK�v�ȕϐ�
	ComPtr<IDXGISwapChain> mSwapChain;

	ComPtr<ID3D11RasterizerState> mRasterizerState;

	ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	ComPtr<ID3D11Buffer> mVertexBuffer;
	ComPtr<ID3D11Buffer> mIndexBuffer;
	ComPtr<ID3D11Buffer> mPerInstanceBuffer;
	ComPtr<ID3D11Buffer> mConstantBuffer;
	ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
	ComPtr<ID3D11ShaderResourceView> m_srv;
	ComPtr<ID3D11Resource> m_tex;					// �e�N�X�`�����\�[�X
	ComPtr<ID3D11VertexShader> mVertexShader;
	ComPtr<ID3D11PixelShader> mPixelShader;
	ComPtr<ID3D11InputLayout> mInputLayout;

	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProj;
	DirectX::XMMATRIX mRotation;
	DirectX::XMMATRIX mScale;
	bool mIsInstancing = true;
	//�`�悷�钸�_��
	int mDrawNum;
	int mInstanceNum;
	ID3D11Buffer* g_pConstantBuffer = nullptr;			// �萔�o�b�t�@

};