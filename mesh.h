#pragma once
//=============================================================================
//
// モデルのメッシュ画像クラス [mesh.h]
//
//=============================================================================
#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <wrl/client.h>
#include "obb.h"
#include <unordered_map>
#include <map>
#include "vertexproto.h"

// テクスチャ構造体
struct Texture {
	std::string type;							// テクスチャ種類
	std::string path;							// テクスチャパス名
	ID3D11Resource*	texres;						// テクスチャリソース
	ID3D11ShaderResourceView *texture;			// SRV
};

using Microsoft::WRL::ComPtr;

class Mesh {
public:
	ID3D11ShaderResourceView*    m_whitesrv;	// 真っ白ＳＲＶ
	ID3D11Resource*				m_whiteres;	// 真っ白RES

	std::vector<Vertex> m_vertices;			// 頂点データ
	std::vector<unsigned int> m_indices;	// インデックス
	std::vector<Texture> m_textures;		// テクスチャ
	ID3D11Device* m_dev;					// デバイス	
	Material m_mtrl;						// マテリアル

	std::unordered_map<std::string, std::vector<DirectX::XMFLOAT3>>	m_bonevertices;		// ボーン毎の頂点データ

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures,Material mtrl);

	void Draw(ID3D11DeviceContext *devcon);
	void Drawinstance(ID3D11DeviceContext *devcon);
	std::vector<COBB*> m_obbvectorcontainer;		// OBBリスト

	void Close();

	void DrawOBB(std::map<std::string, BONE>& bone);
	void UpdateOBB(std::map<std::string, BONE>& bone, const XMFLOAT4X4& mtxworld);

	ID3D11Buffer* m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11Buffer* m_IndexBuffer = nullptr;		// インデックスバッファ
	ID3D11Buffer* m_cbmtrl = nullptr;			// マテリアル用コンスタントバッファ

private:
	
	bool setupMesh();
	void updatevertexbuffer();
};