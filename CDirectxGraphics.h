#pragma once
//========================================================
//CDirectxGraphics.h
//			�r���{�[�h�̐������s�����߂̃N���X
//========================================================
#include	<d3d11.h>
#include	<wrl/client.h>

using Microsoft::WRL::ComPtr;

class CDirectXGraphics {
private:
	CDirectXGraphics() {}
	ComPtr<ID3D11Device>			m_lpDevice;					// DIRECT3DDEVICE11�f�o�C�X

	ComPtr<ID3D11DeviceContext>		m_lpImmediateContext;		// DIRECT3DDEVICE11�f�o�C�X�R���e�L�X�g
	ComPtr<IDXGISwapChain>			m_lpSwapChain;				// �X���b�v�`�F�C��

	ComPtr<ID3D11RenderTargetView>	m_lpRenderTargetView;		// �����_�[�^�[�Q�b�g�r���[
	ComPtr<ID3D11Texture2D>			m_depthStencilBuffer;		// �y�o�b�t�@�A�X�e���V���o�b�t�@
	ComPtr<ID3D11DepthStencilState>	m_depthStencilState;		// �y�o�b�t�@�A�X�e���V���X�e�[�g
	ComPtr<ID3D11DepthStencilView>	m_depthStencilView;			// �y�o�b�t�@�A�X�e���V���r���[
	ComPtr<ID3D11RasterizerState>	m_rasterState;				// ���X�^�[�X�e�[�^�X
	ComPtr<ID3D11RasterizerState>	m_cissorState;				// �V�U�[�@���X�^�[�X�e�[�^�X

	ID3D11ShaderResourceView*       m_pHeightTexture;//�e�N�X�`���[
	ID3D11Resource*					m_pTexture;	
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;


	D3D_DRIVER_TYPE					m_DriverType;				// �h���C�o�^�C�v
	D3D_FEATURE_LEVEL				m_FeatureLevel;				// �@�\���x��

	ComPtr<ID3D11BlendState>		m_alphaEnableBlendingState;		// �A���t�@�u�����h�X�e�[�g�i�L���j
	ComPtr<ID3D11BlendState>		m_alphaDisableBlendingState;	// �A���t�@�u�����h�X�e�[�g�i�����j

	ComPtr<ID3D11SamplerState>		m_samplerstate;					// �T���v���[�X�e�[�g
	
	// �r���[�|�[�g��ݒ�
	D3D11_VIEWPORT vp[2];

	const char *tex = "sample.png";


	int								m_Width = 0;				// �o�b�N�o�b�t�@�w�T�C�Y
	int								m_Height = 0;				// �o�b�N�o�b�t�@�x�T�C�Y
public:

	//�R���X�g���N�^
	CDirectXGraphics(const CDirectXGraphics&) = delete;
	CDirectXGraphics& operator=(const CDirectXGraphics&) = delete;
	CDirectXGraphics(CDirectXGraphics&&) = delete;
	CDirectXGraphics& operator=(CDirectXGraphics&&) = delete;

	//�f�X�g���N�^
	~CDirectXGraphics() {
		Exit();
	}

	static CDirectXGraphics* GetInstance() {
		static CDirectXGraphics instance;
		return &instance;
	}

	// ��������
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool fullscreen);

	void MultiViewPortDraw(int vp_num);
	

	// �I������
	void Exit();

	// �f�o�C�XGET
	ID3D11Device*	GetDXDevice() const {
		return m_lpDevice.Get();
	}

	// �C�~�f�B�G�C�g�f�o�C�XGET
	ID3D11DeviceContext* GetImmediateContext() const {
		return m_lpImmediateContext.Get();
	}

	// SWAP�`�F�C��GET
	IDXGISwapChain* GetSwapChain()const {
		return m_lpSwapChain.Get();
	}
	//�T���v���[GET
	ID3D11SamplerState*const* GetSampState() {
		return m_samplerstate.GetAddressOf();
	}

	// �����_�����O�^�[�Q�b�gGET
	ID3D11RenderTargetView* GetRenderTargetView() const {
		return m_lpRenderTargetView.Get();
	}

	// depthstencil view
	ID3D11DepthStencilView* GetDepthStencilView() const {
		return m_depthStencilView.Get();
	}

	// �r���[�|�[�g�̍������擾����
	int GetViewPortHeight() const {
		return m_Height;
	}

	// �r���[�|�[�g�̕����擾����
	int GetViewPortWidth() const {
		return m_Width;
	}

	// �A���t�@�u�����h�L����
	void TurnOnAlphaBlending();

	// �A���t�@�u�����h������
	void TurnOffAlphaBlending();

	// �V�U�[�L����
	void TurnOnLeftScissor();
	void TurnOnRightScissor();

	// �V�U�[������
	void TurnOffScissor();


	// Z�o�b�t�@������
	void TurnOffZbuffer() {
		ID3D11RenderTargetView*  rtvtable[1];

		rtvtable[0] = m_lpRenderTargetView.Get();

		m_lpImmediateContext->OMSetRenderTargets(
			1,										// �^�[�Q�b�g
			rtvtable,								// �r���[�e�[�u��
			nullptr									// �[�x�o�b�t�@�Ȃ�
		);
	}

	// Z�o�b�t�@�L����
	void TurnOnZBuffer() {
		ID3D11RenderTargetView*  rtvtable[1];

		rtvtable[0] = m_lpRenderTargetView.Get();

		m_lpImmediateContext->OMSetRenderTargets(
			1,										// �^�[�Q�b�g
			rtvtable,								// �r���[�e�[�u��
			m_depthStencilView.Get()				// �[�x�o�b�t�@�Ȃ�
		);
	}


};
