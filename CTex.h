#pragma once
#include	"uncopyable.h"

// comptr
using Microsoft::WRL::ComPtr;

// 矩形クラス
class CTex : public Uncopyable {
public:
	// 頂点データ
	struct Vertex {
		DirectX::XMFLOAT3 pos;		// 座標		
		DirectX::XMFLOAT4 color;	// カラー
		DirectX::XMFLOAT2 tex;		// テクスチャ
	};

	// ビューポートのサイズをセット
	bool SetViewPortSize(uint32_t width, uint32_t height) {

		ComPtr<ID3D11Buffer> CBViewPort;

		// ビューポート用の定数バッファ
		struct ConstantBufferViewPort {
			uint32_t	Width[4];			// ビューポート幅
			uint32_t	Height[4];			// ビューポート高さ
		};

		// ビューポート定数バッファに値をセット
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

		// 頂点シェーダーにセット
		GetDX11DeviceContext()->VSSetConstantBuffers(9, 1, CBViewPort.GetAddressOf());

		return true;
	}

	// 矩形の初期化
	bool Init(uint32_t width, uint32_t height, DirectX::XMFLOAT3 color);

	// 描画
	void Draw();

	void UnInit();

	// 拡大、縮小
	void SetScale(float sx, float sy, float sz);

	// 位置をセット
	void SetPosition(float x, float y, float z);

	// Z軸回転
	void SetRotation(float angle);

	void SetUV(XMFLOAT2* muv);

	void SetAlpha(float a);

	ComPtr<ID3D11ShaderResourceView> GetSrv() {
		return m_srv;
	};

	// 矩形の進行方向を取得（元画像が上向きに作られていることを前提）
	DirectX::XMFLOAT3 GetForward() {
		DirectX::XMFLOAT3 forward;
		forward.x = m_worldmtx._21;
		forward.y = m_worldmtx._22;
		forward.z = m_worldmtx._23;
		return forward;
	}

	// 矩形の横方向を取得
	DirectX::XMFLOAT3 GetSide() {
		DirectX::XMFLOAT3 side;
		side.x = m_worldmtx._11;
		side.y = m_worldmtx._12;
		side.z = m_worldmtx._13;
		return side;
	}


	// 頂点データ更新
	void updateVertex(uint32_t width, uint32_t height, DirectX::XMFLOAT3 color);
	// 頂点バッファ更新
	void updateVbuffer();

	// テクスチャセット
	bool LoadTexture(const char* filename) {
		// テクスチャ読み込み
		bool sts = CreateSRVfromFile(filename,
			GetDX11Device(),
			GetDX11DeviceContext(),
			&m_tex, &m_srv);
		if (!sts) {
			std::string str("SRV 作成エラー ");
			std::string strfile(filename);
			MessageBox(nullptr, (str + strfile).c_str(), "error", MB_OK);
			return sts;
		}
		return sts;
	}



	static CTex* GetInstance() {
		static CTex instance;
		return &instance;
	}

	//DirectX::XMFLOAT4X4 s_mtx;
	//DirectX::XMFLOAT4X4 p_mtx;
	//DirectX::XMFLOAT4X4 o_mtx;

	XMFLOAT3 m_pos = {};
	XMFLOAT3 m_scale = {};
	float m_angle;
	float m_Alpha = 1.0f;
	XMFLOAT2 c_uv[4] =
	{
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f},
	};



	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> D3DShaderResourceView;


private:
	DirectX::XMFLOAT4X4		m_worldmtx;				// ワールド変換行列
	ComPtr<ID3D11Buffer>	m_vertexbuffer;			// 頂点バッファ
	ComPtr<ID3D11Buffer>	m_indexbuffer;			// インデックスバッファ
	CTex::Vertex			m_vertex[4];			// 矩形４頂点
	float					m_width;				// 幅
	float					m_height;				// 高さ
	ComPtr<ID3D11ShaderResourceView> m_srv;			// SRV
	ComPtr<ID3D11Resource> m_tex;					// テクスチャリソース
};