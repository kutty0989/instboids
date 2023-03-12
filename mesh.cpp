//=============================================================================
//
// モデルのメッシュ画像クラス [mesh.cpp]
//
//=============================================================================

#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <unordered_map>
#include "memory.h"
#include "CDirectxGraphics.h"
#include "shader.h"
#include "vertexproto.h"
#include "Mesh.h"
#include "DX11util.h"
#include "obb.h"
#include "dx11mathutil.h"

using namespace std;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Material mtrl) {

	// 真っ白のSRVを一つ作っておく
	bool sts = CreateSRVfromFile("assets/white.bmp", GetDX11Device(), GetDX11DeviceContext(), &m_whiteres, &m_whitesrv);
	if (!sts) {
		MessageBox(nullptr, "white,bmp load error", "error", MB_OK);
	}

	m_vertices = vertices;
	m_indices = indices;
	m_dev = CDirectXGraphics::GetInstance()->GetDXDevice();
	m_textures = textures;
	m_mtrl = mtrl;
	setupMesh();

	std::vector<XMFLOAT3> tempv;

	// ボーンを登録
	for (int i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (vertices[i].m_BoneName[j] != "") {
				m_bonevertices[vertices[i].m_BoneName[j]] = tempv;
			}
		}
	}

	// 頂点を登録
	for (int i = 0; i < vertices.size(); i++) {
		for (int j = 0; j < 4; j++) {
			// ボーン存在チェック
			auto itr = m_bonevertices.find(vertices[i].m_BoneName[j].c_str());
			if (itr != m_bonevertices.end()) {
				std::vector<XMFLOAT3>& vv = m_bonevertices[vertices[i].m_BoneName[j].c_str()];
				vv.push_back(vertices[i].m_Pos);
			}
		}
	}

	// OBB作成
	for (auto data : m_bonevertices) {
		COBB* pb = new COBB();
		pb->CalculateOBB(data.second);
		pb->CreateBoxMesh();
		pb->SetName(data.first.data());			// 名前(ﾎﾞｰﾝ名)をセット
		m_obbvectorcontainer.push_back(pb);
	}
}


void Mesh::DrawOBB(std::map<std::string, BONE>& bone) {

	for (int i = 0; i < m_obbvectorcontainer.size(); i++) {
		// ボーン存在チェック(アニメーションにのみ存在するボーンがあった場合は無視する)
//		auto itr = bone.find(m_obbvectorcontainer[i]->GetName());
//		if (itr != bone.end()) {
		m_obbvectorcontainer[i]->Draw();
		//		}
	}
}

void Mesh::UpdateOBB(std::map<std::string, BONE>& bone, const XMFLOAT4X4& mtxworld) {

	for (int i = 0; i < m_obbvectorcontainer.size(); i++) {

		// ボーン存在チェック(モデルの頂点データに存在するボーンにのみ対応)
//		auto itr = bone.find(m_obbvectorcontainer[i]->GetName());
//		if (itr != bone.end()) {

			// ボーンに対応した行列を取り出す
		aiMatrix4x4 aimtx = bone[m_obbvectorcontainer[i]->GetName()].Matrix;

		XMFLOAT4X4 dxmtx;
		dxmtx = DX11MtxaiToDX(aimtx);		// aiMatrixをDX行列へ

		// ワールド変換行列を掛け算
		DX11MtxMultiply(dxmtx, dxmtx, mtxworld);
		// OBBの姿勢・位置を更新
		m_obbvectorcontainer[i]->Update(dxmtx);
		//		}
	}
}

void Mesh::Draw(ID3D11DeviceContext* devcon)
{
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	// 頂点バッファをセット
	devcon->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// インデックスバッファをセット
	devcon->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// トポロジーをセット
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// SRVをセット
	if (m_textures.size() >= 1) {
		devcon->PSSetShaderResources(0, 1, &m_textures[0].texture);			// debug ts
	}
	else {
		// 真っ白SRVをセット
		devcon->PSSetShaderResources(0, 1, &m_whitesrv);					// debug ts
	}
	// マテリアルをVSへセット
	devcon->VSSetConstantBuffers(3, 1, &m_cbmtrl);
	devcon->PSSetConstantBuffers(3, 1, &m_cbmtrl);

	// インデックスバッファを利用して描画
	devcon->DrawIndexed(static_cast<unsigned int>(m_indices.size()), 0, 0);
}

void Mesh::Drawinstance(ID3D11DeviceContext* devcon)
{
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	// 頂点バッファをセット
	devcon->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// インデックスバッファをセット
	devcon->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// トポロジーをセット
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// SRVをセット
	if (m_textures.size() >= 1) {
		devcon->PSSetShaderResources(0, 1, &m_textures[0].texture);			// debug ts
	}
	else {
		// 真っ白SRVをセット
		devcon->PSSetShaderResources(0, 1, &m_whitesrv);					// debug ts
	}
	// マテリアルをVSへセット
	devcon->VSSetConstantBuffers(3, 1, &m_cbmtrl);
	devcon->PSSetConstantBuffers(3, 1, &m_cbmtrl);

	// インデックスバッファを利用して描画
	devcon->DrawIndexedInstanced(static_cast<unsigned int>(m_indices.size()),100,0, 0, 0);
}

void Mesh::Close()
{
	for (int i = 0; i < m_obbvectorcontainer.size(); i++) {
		delete m_obbvectorcontainer[i];
	}
	m_obbvectorcontainer.erase(m_obbvectorcontainer.begin(), m_obbvectorcontainer.end());

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_cbmtrl->Release();
}

bool Mesh::setupMesh()
{
	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(m_dev,
		static_cast<unsigned int>(sizeof(Vertex)),			// ストライド
		static_cast<unsigned int>(m_vertices.size()),		// 頂点数
		m_vertices.data(),									// 頂点データ
		&m_VertexBuffer);
	if (!sts) {
		return false;
	}

	// インデックスバッファ生成
	sts = CreateIndexBuffer(m_dev,
		static_cast<unsigned int>(m_indices.size()),
		m_indices.data(),
		&m_IndexBuffer);
	if (!sts) {
		return false;
	}

	// マテリアル用コンスタントバッファ生成
	sts = CreateConstantBufferWrite(m_dev,
		sizeof(ConstantBufferMaterial),
		&m_cbmtrl);
	if (!sts) {
		return false;
	}

	ID3D11DeviceContext* devicecontext;
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// 定数バッファ更新
	D3D11_MAPPED_SUBRESOURCE pData;

	ConstantBufferMaterial cb;

	cb.AmbientMaterial.w = 1.0f;
	cb.AmbientMaterial.x = m_mtrl.m_Ambient.x;
	cb.AmbientMaterial.y = m_mtrl.m_Ambient.y;
	cb.AmbientMaterial.z = m_mtrl.m_Ambient.z;

	cb.DiffuseMaterial.w = 1.0f;
	cb.DiffuseMaterial.x = m_mtrl.m_Diffuse.x;
	cb.DiffuseMaterial.y = m_mtrl.m_Diffuse.y;
	cb.DiffuseMaterial.z = m_mtrl.m_Diffuse.z;

	cb.SpecularMaterial.w = 1.0f;
	cb.SpecularMaterial.x = m_mtrl.m_Specular.x;
	cb.SpecularMaterial.y = m_mtrl.m_Specular.y;
	cb.SpecularMaterial.z = m_mtrl.m_Specular.z;

	HRESULT hr = devicecontext->Map(m_cbmtrl, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(ConstantBufferMaterial));
		devicecontext->Unmap(m_cbmtrl, 0);
	}

	return true;
}

void Mesh::updatevertexbuffer() {

	HRESULT hr;

	ID3D11DeviceContext* devicecontext;

	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	D3D11_MAPPED_SUBRESOURCE pData;

	// 定数バッファ更新
	hr = devicecontext->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		//			memcpy_s(pData.pData, pData.RowPitch, (void*)m_deformvertices.data(), sizeof(aiVertex)*m_deformvertices.size());
		memcpy_s(pData.pData, pData.RowPitch, (void*)m_vertices.data(), sizeof(Vertex) * m_vertices.size());
		devicecontext->Unmap(m_VertexBuffer, 0);
	}
}