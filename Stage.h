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
//	//平面を描画する
//	ComPtr<ID3D11Buffer> m_pVertexBuffer;//頂点バッファ
//	ComPtr<ID3D11Buffer> m_pIndexBuffer;//インデックスバッファ
//	ComPtr<ID3D11VertexShader> m_pVertexShader;//頂点シェーダー
//	ComPtr<ID3D11PixelShader> m_pPixelShader;//ピクセルシェーダー
//	ComPtr<ID3D11InputLayout> m_pVertexLayout;//頂点レイアウト
//public:
//	//マップ配置
//	int m_map[MAPSIZEX][MAPSIZEZ] = {
//
//		//-4 -3 -2 -1 0 1 2 3 4
//		{1,2,2,2,2,2,2,2,1},//2:グー 2:チョキ　２：パー　３：なし
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
//	//平面チップ
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
//	//コピー・代入は禁止するが、ムーブは許可する
//	Stage(const Stage&) = delete;
//	Stage& operator = (const Stage&) = delete;
//
//	//デフォルト
//	Stage(Stage&&) = default;
//	Stage() = default;
//	Stage& operator = (Stage&&) = default;
//
//
//	bool Create();   //生成
//	void Destroy();//破棄
//	bool Init();//初期処理
//	void Update();//更新
//	void Draw();//描画
//	void Draw(XMFLOAT4X4& mtxworld);//描画
//	void Finalize();//終了処理
//
//	int Getmap(int x, int y);
//
//	XMFLOAT2 GetMapChipNo(XMFLOAT4X4 mtx_x, XMFLOAT4X4 mtx_z);
//};