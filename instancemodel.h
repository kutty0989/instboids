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
//#include	"animationdataassimp.h"
//#include	"ModelData.h"
//#include"PlayerMgr.h"
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dcompiler.lib")
//
//using namespace Microsoft::WRL;
//
//
//
//
//
//class InstanceModel
//{
//public:
//
//	// 一つの頂点情報を格納する構造体
//	struct VERTEX
//	{
//		DirectX::XMFLOAT3 pos;
//		DirectX::XMFLOAT3 normal;
//		DirectX::XMFLOAT2 tex;		// テクスチャ
//	};
//
//
//
//	struct PerInstanceData
//	{
//		DirectX::XMMATRIX matrix;
//		DirectX::XMVECTOR color;
//	};
//
//
//	enum FILETYPE {
//		eDATFILE,
//		eASSIMPFILE
//	};
//	FILETYPE				m_filetype = eASSIMPFILE;		// ファイルタイプ
//	std::vector<AnimationDataAssimp*> m_animationcontainer;
//	ModelData				m_assimpfile;					// assimpfile
//
//
//
//	XMVECTOR temppos;
//
//
//	unsigned int	m_AnimFileIdx = 0;
//
//	// アニメーションをロードする
//	bool LoadAnimation(const char* filename) {
//		AnimationDataAssimp* animdata;
//
//		animdata = new AnimationDataAssimp();
//		bool sts = animdata->Init(filename);
//		if (sts) {
//			m_animationcontainer.push_back(animdata);
//			return true;
//		}
//		else {
//			MessageBox(nullptr, "Load Animation error", "error", MB_OK);
//			return false;
//		}
//	}
//	const ModelData& GetModelData() {
//		return m_assimpfile;
//	}
//
//
//	InstanceModel();
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
//
//	bool Init(const char* filename, std::string texfolder);
//	void Uninit();
//	void Update(
//		int m_Frame, int m_preFrame, float m_factor, int animecnt,
//		const DirectX::XMFLOAT4X4& mtxworld);
//	void Update2(
//		int animecnt,
//		const DirectX::XMFLOAT4X4& mtxworld);
//	void Draw(DirectX::XMFLOAT4X4& mtxworld);
//	void Draw2(DirectX::XMFLOAT4X4& mtxworld);
//	void CalcPlayer(DirectX::XMFLOAT4X4& mtxworld);
//	unsigned int GetAnimationNum() {	// アニメーション総数を取得
//
//		return m_animationcontainer.size();//[m_AnimFileIdx]->GetScene()->mNumAnimations;
//	}
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
//
//};
//
