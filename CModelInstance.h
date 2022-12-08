#pragma once
#pragma once
#include	<d3d11.h>
#include	"DatFile.h"
#include"DatFileLoader.h"
#include"ModelData.h"

class CModelInstance {
private:
	enum FILETYPE {
		eDATFILE,
		eASSIMPFILE
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

	ComPtr<ID3D11Buffer> mPerInstanceBuffer;
	ComPtr<ID3D11Buffer> mConstantBuffer;

	FILETYPE				m_filetype = eASSIMPFILE;		// ファイルタイプ

	ModelData m_assimpfile;
	DatFile					m_datfile;						// datファイル
	ID3D11VertexShader* m_pVertexShader = nullptr;		// 頂点シェーダー入れ物
	ID3D11PixelShader* m_pPixelShader = nullptr;		// ピクセルシェーダー入れ物
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// 頂点フォーマット定義

	//ID3D11ShaderResourceView* m_texSRV = nullptr;			// テクスチャＳＲＶ
	int						m_instancecount = 0;			// インスタンシング数
	ID3D11Buffer* m_pInstanceBuffer;				// インスタンス用行列格納頂点バッファ
	void* m_initdata = nullptr;			// インスタンスバッファの初期化データ

	ID3D11Buffer* m_pVertexBuffer;		// 頂点バッファ
	ID3D11Buffer* m_pIndexBuffer;			// インデックスバッファ
//	DatFileLoader* m_datfile;				// datファイルデータ
	ID3D11ShaderResourceView** m_srv;					// シェーダーリソースビュー
	ID3D11Buffer* m_cb3;					// コンスタントバッファ(マテリアル用)
	ID3D11Resource* m_tex;
public:
	bool InitiInstancing(int instancecnt, const char* filename, const char* vsfile, const char* psfile, std::string texfoldername);
	bool Init(const char* filename, const char* vsfile, const char* psfile);
	void Uninit();
	void Update(XMFLOAT4X4 mat[]);							// インスタンスバッファ更新
	void Draw();
	void DrawInstance();
	DatFileLoader* GetDatFileData() {
		return m_datfile.GetDatFileLoader();
	}
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProj;
	DirectX::XMMATRIX mRotation;
	DirectX::XMMATRIX mScale;
	std::vector<Vertex> ver;
	std::vector<unsigned int> ind;

	void GetVertex() {

		// メッシュデータ取得
		const std::vector<Mesh>& meshes = m_assimpfile.GetMeshes();

		// OBB全件取得
		for (int i = 0; i < meshes.size(); i++) {
			const Mesh& m = meshes[i];
			for (auto data : m.m_vertices) {
				ver.emplace_back(data);
			}
			for (auto data : m.m_indices) {
				ind.emplace_back(data);
			}
		}
	}

};
