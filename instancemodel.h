//#pragma once
//#pragma once
//#include <d3d11.h>
//#include <d3dcompiler.h>
//#include <DirectXMath.h>
//#include <string>
//#include <vector>
//#include <wrl/client.h>
//#include"DX11util.h"
//#include"Shader.h"
//#include	"ModelData.h"
//#include	"animationdataassimp.h"
//
//using namespace Microsoft::WRL;
//
//
//
//class InstanceModel
//{
//	// 一つの頂点情報を格納する構造体
//	struct VERTEX
//	{
//		DirectX::XMFLOAT3 pos;
//		DirectX::XMFLOAT3 normal;	// カラー
//		DirectX::XMFLOAT2 tex;		// テクスチャ
//	};
//
//	struct CONSTANT_BUFFER
//	{
//		DirectX::XMMATRIX gWVP;
//	};
//
//	struct PerInstanceData
//	{
//		DirectX::XMMATRIX matrix;
//		DirectX::XMVECTOR color;
//	};
//
//
//public:
//
//	ModelData				m_assimpfile;					// assimpfile
//	enum FILETYPE {
//		eDATFILE,
//		eASSIMPFILE
//	};
//	FILETYPE				m_filetype = eASSIMPFILE;		// ファイルタイプ
//
//
//	// テクスチャセット
//	bool LoadTexture(const char* filename) {
//		// テクスチャ読み込み
//		bool sts = CreateSRVfromFile(filename,
//			GetDX11Device(),
//			GetDX11DeviceContext(),
//			&m_tex, &m_srv);
//		if (!sts) {
//			std::string str("SRV 作成エラー ");
//			std::string strfile(filename);
//			MessageBox(nullptr, (str + strfile).c_str(), "error", MB_OK);
//			return sts;
//		}
//		return sts;
//	}
//
//	void Init(const char* filename, std::string texfolder);
//	void OnCreate(const char* filename, std::string texfolder);
//	bool Update();
//	void RenderInstancing();
//	~InstanceModel();
//
//	XMFLOAT2 c_uv[4] =
//	{
//		{0.0f,0.0f},
//		{1.0f,0.0f},
//		{0.0f,1.0f},
//		{1.0f,1.0f},
//	};
//
//private:
//	void Render();
//
//	//DirectXに必要な変数
//	ComPtr<IDXGISwapChain> mSwapChain;
//
//	ComPtr<ID3D11RasterizerState> mRasterizerState;
//
//	ComPtr<ID3D11RenderTargetView> mRenderTargetView;
//	ComPtr<ID3D11Buffer> mVertexBuffer;
//	ComPtr<ID3D11Buffer> mIndexBuffer;
//	ComPtr<ID3D11Buffer> mPerInstanceBuffer;
//	ComPtr<ID3D11Buffer> mStructerBuffer;
//	ComPtr<ID3D11Buffer> mConstantBuffer;
//	ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
//	ComPtr<ID3D11ShaderResourceView> m_srv;
//	ComPtr<ID3D11Resource> m_tex;					// テクスチャリソース
//	ComPtr<ID3D11VertexShader> mVertexShader;
//	ComPtr<ID3D11PixelShader> mPixelShader;
//	ComPtr<ID3D11InputLayout> mInputLayout;
//
//	DirectX::XMMATRIX mView;
//	DirectX::XMMATRIX mProj;
//	DirectX::XMMATRIX mRotation;
//	DirectX::XMMATRIX mScale;
//	bool mIsInstancing = true;
//	//描画する頂点数
//	int mDrawNum;
//	int mInstanceNum;
//	ID3D11Buffer* g_pConstantBuffer = nullptr;			// 定数バッファ
//};
//
