#pragma once
//========================================================
//CLight.h
//			ライティングを設定するクラス
//========================================================

#include	<DirectXMath.h>
#include	"memory.h"
#include	"Shader.h"
#include	"DX11util.h"

class CLight {

	//ライトの変数
	ALIGN16 struct ConstantBufferLight {
		DirectX::XMFLOAT4 LightDirection;
		DirectX::XMFLOAT4 EyePos;
		DirectX::XMFLOAT4 Ambient;
	};

	//ライトの種類
	enum class LightType {
		DIRECTIONAL,
		POINT,
		SPOT
	};

	LightType			m_type;
	DirectX::XMFLOAT3	m_eyepos;//カメラの場所
	DirectX::XMFLOAT4	m_lightpos;		// w=0の時は方向 w=1の時は位置
	ID3D11Buffer*       m_pConstantBufferLight = nullptr;
	DirectX::XMFLOAT4	m_ambient;//アンビエント
public:

	//ライトの初期処理
	bool Init(DirectX::XMFLOAT3 eyepos,DirectX::XMFLOAT4 lightpos) {
		m_lightpos = lightpos;
		m_eyepos = eyepos;
		m_type = LightType::DIRECTIONAL;

		// コンスタントバッファ作成
		bool sts = CreateConstantBuffer(
			GetDX11Device(),				// デバイス
			sizeof(ConstantBufferLight),		// サイズ
			&m_pConstantBufferLight);			// コンスタントバッファ４
		if (!sts) {
			MessageBox(NULL, "CreateBuffer(constant buffer Light) error", "Error", MB_OK);
			return false;
		}

		Update();

		return true;
	}

	void Update() {
		ConstantBufferLight		cb;

		cb.EyePos.w = 1.0;
		cb.EyePos.x = m_eyepos.x;
		cb.EyePos.y = m_eyepos.y;
		cb.EyePos.z = m_eyepos.z;

		cb.LightDirection.x = m_lightpos.x;
		cb.LightDirection.y = m_lightpos.y;
		cb.LightDirection.z = m_lightpos.z;
		cb.LightDirection.w = m_lightpos.w;

		cb.Ambient = m_ambient;

		GetDX11DeviceContext()->UpdateSubresource(m_pConstantBufferLight, 
			0, 
			nullptr, 
			&cb, 
			0, 0);

		// コンスタントバッファ4をｂ3レジスタへセット（頂点シェーダー用）
		GetDX11DeviceContext()->VSSetConstantBuffers(4, 1, &m_pConstantBufferLight);
		// コンスタントバッファ4をｂ3レジスタへセット(ピクセルシェーダー用)
		GetDX11DeviceContext()->PSSetConstantBuffers(4, 1, &m_pConstantBufferLight);

	}

	//ライト解放処理
	void Uninit() {
		if (m_pConstantBufferLight) {
			m_pConstantBufferLight->Release();
			m_pConstantBufferLight = nullptr;
		}
	}

	//カメラの場所を設定
	void SetEyePos(DirectX::XMFLOAT3 eyepos) {
		m_eyepos = eyepos;
	}

	//ライトの場所を設定
	void SetLightPos(DirectX::XMFLOAT4 lightpos) {
		m_lightpos = lightpos;
	}
	//環境光を設定
	void SetAmbient(DirectX::XMFLOAT4 amb) {
		m_ambient = amb;
	}
};