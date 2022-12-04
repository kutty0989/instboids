#pragma once

#include	"uncopyable.h"
#include"ModelData.h"
// comptr
using Microsoft::WRL::ComPtr;

// 矩形クラス
class CHeight_Map : public Uncopyable {
public:
	// 頂点データ
	struct Vertex {
		DirectX::XMFLOAT3 pos;		// 座標		
		DirectX::XMFLOAT4 color;	// カラーfloat4 Pos : POSITION
		DirectX::XMFLOAT2 tex;		// テクスチャ
	};




	// 定数バッファ
	struct ConstantBuffer
	{
		float tessellationAmount;
		float gcol;
		float padding[2];
	};

	// 定数バッファ
	struct ConstantBuffer2
	{

		float hight;
		float nbuf[3];

	};

	// ディスプレイスメントマップの高さ
	static float g_hight;
	static float g_devide;
	// テッセレーションファクタ
	static float g_tesselationamount;
	static float g_col;


	float	g_angle = 0.0f;

	XMFLOAT3 m_pos = {};
	XMFLOAT3 m_scale = {};
	XMFLOAT3 m_angle = {};


	DirectX::XMFLOAT4X4 s_mtx = {};
	DirectX::XMFLOAT4X4 p_mtx={};
	DirectX::XMFLOAT4X4 o_mtx={};

	

	//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
	struct SIMPLESHADER_CONSTANT_BUFFER
	{
		XMMATRIX mWVP;//ワールド、ビュー、射影の合成変換行列
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
	bool Init( DirectX::XMFLOAT3 color);



	// 描画
	void Draw();

	void UnInit();

	// 拡大、縮小
	void SetScale(XMFLOAT3 scale);

	// 位置をセット
	void SetPosition(XMFLOAT3 pos);

	// Z軸回転
	void SetRotation(float x,float y,float z);

	void SetUV(XMFLOAT2* muv);
	
	void SetAlpha(float a);

	float HeightColor = 0.0f;

	double GetHeightColor(XMFLOAT2 playerpos);
	
	/// <summary>
	/// 少し前のカラー情報
	/// padの角度の行先のカラー情報を返す
	/// </summary>
	/// <param name="playerpos"></param>
	/// <param name="pad_rigx"></param>
	/// <param name="pad_rigy"></param>
	/// <returns></returns>
	double GetGoHeightColor(XMFLOAT2 playerpos,float pad_rigx,float pad_rigy);




	/// <summary>
	/// パーリーノイズ作成クラス
	/// </summary>
	void NoiseCreate();

	std::vector<std::vector<double>> GetMap() { return vData; };

	void LoadMap(std::vector<std::vector<double>> loadmap);
	
	void ChangeMap();


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
	void updateVertex(DirectX::XMFLOAT3 color);
	// 頂点バッファ更新
	void updateVbuffer();

	// テクスチャセット
	bool LoadTexture(const char* filename, int i) {
		// テクスチャ読み込み
		bool sts = CreateSRVfromFile(filename,
			GetDX11Device(),
			GetDX11DeviceContext(),
			&m_tex, &m_srv[i]);

		if (!sts) {
			std::string str("SRV 作成エラー ");
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

	const int iPixSize = 512;//縦横ピクセル数

   //ノイズ初期設定
	const double dFrequency = 2.0;//周波数 小さくすると山が少なく、大きくすると細かく
	const int iOctaves = 7;//オクターブ　スムーズに変化

	static std::vector<std::vector<double> > vData;
	static std::vector<std::vector<double> > gData;
	static std::vector<byte> bufsrc;
private:
	DirectX::XMFLOAT4X4		m_worldmtx;				// ワールド変換行列
	ComPtr<ID3D11Buffer>	m_vertexbuffer;			// 頂点バッファ
	ComPtr<ID3D11Buffer>	m_indexbuffer;			// インデックスバッファ
	CHeight_Map::Vertex		m_vertex[4];			// 矩形４頂点
	int					m_width = iPixSize;				// 幅
	int					m_height = iPixSize;				// 高さ
	ComPtr<ID3D11ShaderResourceView> m_srv[5];			// SRV			// 高さテクスチャ
	ComPtr<ID3D11Resource> m_tex;					// テクスチャリソース

	ID3D11Buffer* g_pConstantBuffer = nullptr;			// 定数バッファ
	ID3D11Buffer* g_pConstantBuffer2 = nullptr;			// 定数バッファ


	double col;//プレイヤーの場所のカラー高さ情報
	double gocol;//向いてる方向の高さ情報
	float defcol;//プレイヤーの場所と行先の差
	float goangle;//プレイヤーと行先の角度
};