#pragma once
#pragma once
#include	<d3d11.h>
#include	"DatFile.h"
#include"DatFileLoader.h"
#include"ModelData.h"

class CModelInstance {
private:
	ModelData m_assimpfile;
	DatFile					m_datfile;						// datファイル
	ID3D11VertexShader* m_pVertexShader = nullptr;		// 頂点シェーダー入れ物
	ID3D11PixelShader* m_pPixelShader = nullptr;		// ピクセルシェーダー入れ物
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// 頂点フォーマット定義

	ID3D11ShaderResourceView* m_texSRV = nullptr;			// テクスチャＳＲＶ
	int						m_instancecount = 0;			// インスタンシング数
	ID3D11Buffer* m_pInstanceBuffer;				// インスタンス用行列格納頂点バッファ
	void* m_initdata = nullptr;			// インスタンスバッファの初期化データ
public:
	bool InitiInstancing(int instancecnt, const char* filename, const char* vsfile, const char* psfile);
	bool Init(const char* filename, const char* vsfile, const char* psfile);
	void Uninit();
	void Update(XMFLOAT4X4 mat[]);							// インスタンスバッファ更新
	void Draw();
	void DrawInstance();
	DatFileLoader* GetDatFileData() {
		return m_datfile.GetDatFileLoader();
	}
};
