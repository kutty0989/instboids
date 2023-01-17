#pragma once
#include<DirectXMath.h>
#include<d3d11.h>
#include"DX11util.h"
#include"Shader.h"
#include"CTex.h"

//////////////////////////////////
//ビルボードクラス
///////////////////////////////


class CBillBoard {
	DirectX::XMFLOAT4X4  m_mtx ={};//ビルボード用の行列
	DirectX::XMFLOAT4X4  o_mtx ={};//ビルボード用の行列
	DirectX::XMFLOAT4X4  t_mtx ={};//ビルボード用の行列
	DirectX::XMFLOAT4X4  s_mtx ={};//ビルボード用の行列
	float m_x = 0;//ビルボードの位置座標
	float m_y = 0;
	float m_z = 0;
	XMFLOAT3 scale = {1,1,1};
	float m_XSize = 100.0f;//ビルボードのXサイズ
	float m_YSize = 100.0f;//ビルボードのXサイズ
	

	DirectX::XMFLOAT4 m_Color = DirectX::XMFLOAT4(1, 1, 1, 1);//頂点カラー値
	ID3D11ShaderResourceView* m_srv = nullptr;//Shader Resourceテクスチャ
	ID3D11Buffer* m_vbuffer = nullptr;//頂点バッファ
	ID3D11BlendState* m_pBlendStateOne = nullptr;
	ID3D11BlendState* m_pBlendStateSrcAlpha = nullptr;
	ID3D11BlendState* m_pBlendStateDefault = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;//頂点シェーダの入れ物
	ID3D11PixelShader* m_pPixelShader = nullptr;//ピクセルシェーダーの入れ物
	ID3D11InputLayout* m_pVertexLayout = nullptr;//頂点フォーマットの定義
	ID3D11Resource* m_res = nullptr;

	
	//頂点フォーマット
	struct MyVertex {
		float x, y, z;
		DirectX::XMFLOAT4 color;
		float tu, tv;
	};
	MyVertex m_Vertex[4] ={};//ビルボードの頂点座標
	DirectX::XMFLOAT2 m_uv[4] ={};//テクスチャ座標
	
		// 定数バッファ
	struct ConstantBuffer2
	{
		float hp;
		float buf[3];

	};
	ID3D11Buffer* g_pConstantBuffer2 = nullptr;			// 定数バッファ

	float hp;


private:

	//ビルボードの頂点座標を計算
	void CalcVertex();
	//ビルボード用の行列を生成
	void CalcBillBoardMatrix(const DirectX::XMFLOAT4X4& camerament);
	//描画
	void Draw();
	//ソースαを設定する
	void SetBlendStateSrcAlpha();
	//ブレンドステートを生成する
	void CreateBlendStateSrcAlpha();
	//加算合成を設定する
	void SetBlendStateOne();
	//ブレンドステートを生成する
	void CreateBlendStateOne();
	//デフォルトのブレンドステートを設定する
	void SetBlendStateDefault();
	//デフォルトのブレンドステートを生成する
	void CreateBelndStateDefault();
	//UV座標をセットする
	void UnInit();

	
public:

	float PMaxX;
	float PMaxY;
	float angle = 0;
	void PartMax(float x, float y);

	void Part(float x, float y);

	void Setsrv(ID3D11ShaderResourceView* srv)
	{
		m_srv = srv;
	}

	void SetUV(DirectX::XMFLOAT2 uv[]) {
		m_uv[0] = uv[0];
		m_uv[1] = uv[1];
		m_uv[2] = uv[2];
		m_uv[3] = uv[3];
		CalcVertex();
	}
	CBillBoard() :m_x(0), m_y(0), m_z(0), m_srv(nullptr) {

	}
	bool Init(float x, float y, float z, float xsize, float ysize, DirectX::XMFLOAT4 color)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_XSize = xsize;
		m_YSize = ysize;
		m_Color = color;
		//デバイス取得
		ID3D11Device* dev = GetDX11Device();
		//デバイスコンテキスト取得
		ID3D11DeviceContext* devcontext = GetDX11DeviceContext();

		//頂点データの定義
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{	"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
			{	"COLOR", 0,DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
			{	"TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		unsigned int numElements = ARRAYSIZE(layout);
		//頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
		bool sts = CreateVertexShader(dev,
			"shader/vsbillboard.hlsl",
			"main",
			"vs_5_0",
			layout,
			numElements,
			&m_pVertexShader,
			&m_pVertexLayout);

		if (!sts)
		{
			MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
			return false;
		}
		//ピクセルシェーダーを生成
		sts = CreatePixelShader(
			dev, "shader/psbillboard.hlsl",
			"main",
			"ps_5_0",
			&m_pPixelShader);
		if (!sts)
		{
			MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
			return false;
		}
		CalcVertex();//ビルボード用の頂点データを作成

		CreateBlendStateSrcAlpha();//アルファブレンディング用のブレンドステートを生成
		CreateBlendStateOne();//加算合成用ブレンドステート生成
		CreateBelndStateDefault();//でファルとのブレンドステート生成

		// 定数バッファ生成
		sts = CreateConstantBuffer(GetDX11Device(), sizeof(ConstantBuffer2), &g_pConstantBuffer2);
		if (!sts) {
			MessageBox(nullptr, "CreateConstantBuffer2 error", "error", MB_OK);
			return false;
		}


		hp = 1.0f;
		ConstantBuffer2 cb2;
		cb2.hp = hp;//高さ変数を渡す
		devcontext->UpdateSubresource(g_pConstantBuffer2, 0, nullptr, &cb2, 0, 0);		// コンスタントバッファ更新
		devcontext->DSSetConstantBuffers(8, 1, &g_pConstantBuffer2);					// DSへコンスタントバッファをb0レジスタへセット


		return true;
	}
	void Dispose()
	{
		if (m_vbuffer != nullptr) {
			m_vbuffer->Release();
			m_vbuffer = nullptr;
		}
		if (m_srv != nullptr)
		{
			m_srv->Release();
			m_srv = nullptr;
		}
	
		if (m_pBlendStateOne != nullptr)
		{
			m_pBlendStateOne->Release();
			m_pBlendStateOne = nullptr;
		}
		if (m_pBlendStateSrcAlpha != nullptr) {
			m_pBlendStateSrcAlpha->Release();
			m_pBlendStateSrcAlpha = nullptr;
		}
		if (m_pBlendStateDefault != nullptr)
		{
			m_pBlendStateDefault->Release();
			m_pBlendStateDefault = nullptr;
		}
		if (m_pPixelShader != nullptr) {
			m_pPixelShader->Release();
			m_pPixelShader = nullptr;
		}
		if (m_pVertexShader != nullptr) {
			m_pVertexShader->Release();
			m_pVertexShader = nullptr;
		}
		if (m_pVertexLayout != nullptr)
		{
			m_pVertexLayout->Release();
			m_pVertexLayout = nullptr;
		}

	}
	//デストラクタ
	virtual ~CBillBoard()
	{
		Dispose();
	}
	//UV座標をセットする
	void SetUV(float u[], float v[]) {
		m_Vertex[0].tu = u[0];
		m_Vertex[0].tv = v[0];

		m_Vertex[1].tu = u[1];
		m_Vertex[1].tv = v[1];

		m_Vertex[2].tu = u[2];
		m_Vertex[2].tv = v[2];

		m_Vertex[3].tu = u[3];
		m_Vertex[3].tv = v[3];
	
		CalcVertex();//ビルボード用の頂点データを作成
	}
		//位置を指定
	void SetPosiotion(float x, float y, float z);
	void SetScale(float x, float y, float z);
	//ビルボードを描画
	void DrawBillBoard(const DirectX::XMFLOAT4X4& cameramat);
	//ビルボード描画加算合成
	void DrawBillBoardAdd(const DirectX::XMFLOAT4X4& cameramat);
		//ビルボードをＺ軸を中心にして回転させて描画
	void DrawRotateBillBoard(const DirectX::XMFLOAT4X4& cameramat, float radian);
	//サイズをセット
	void SetSize(float x, float y);
	//テクスチャ読み込み
	bool LoadTexTure(const char* filname);

	void SetHp(float hpp)
	{
		hp = hpp;
	}
};