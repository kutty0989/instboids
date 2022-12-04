#pragma once
#include	<unordered_map>
#include	<d3d11.h>
#include	<string>
#include	"dx11util.h"
#include	"shader.h"

class ShaderHashmap {
public:
	ShaderHashmap(const ShaderHashmap&) = delete;
	ShaderHashmap& operator=(const ShaderHashmap&) = delete;
	ShaderHashmap(ShaderHashmap&&) = delete;
	ShaderHashmap& operator=(ShaderHashmap&&) = delete;

	static ShaderHashmap* GetInstance() {
		static ShaderHashmap instance;
		return &instance;
	}

public:
	// �s�N�Z���V�F�[�_�[�Z�b�g
	bool SetPixelShader(std::string filename) {
		ID3D11PixelShader* psh;

		// �f�o�C�X�擾
		ID3D11Device* device;
		device = GetDX11Device();

		// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
		bool sts = CreatePixelShader(device,
			filename.c_str(),
			"main",
			"ps_5_0",
			&psh);

		if (!sts) {
			MessageBox(nullptr, "CreatePixel Shader error", "error", MB_OK);
			return false;
		}

		// unordered_map�R���e�i�Ɋi�[
		m_pshashmap[filename] = psh;

		return true;
	}

	// �n���V�F�[�_�[�Z�b�g
	bool SetHullShader(std::string filename) {
		ID3D11HullShader* psh;

		// �f�o�C�X�擾
		ID3D11Device* device;
		device = GetDX11Device();

		// �n���V�F�[�_�[�I�u�W�F�N�g�𐶐�
		bool sts = CreateHullShader(device,
			filename.c_str(),
			"main",
			"hs_5_0",
			&psh);

		if (!sts) {
			MessageBox(nullptr, "CreateHull Shader error", "error", MB_OK);
			return false;
		}

		// unordered_map�R���e�i�Ɋi�[
		m_hullhashmap[filename] = psh;

		return true;
	}


	// �h���C���V�F�[�_�[�Z�b�g
	bool SetDomainShader(std::string filename) {
		ID3D11DomainShader* psh;

		// �f�o�C�X�擾
		ID3D11Device* device;
		device = GetDX11Device();

		// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
		bool sts = CreateDomainShader(device,
			filename.c_str(),
			"main",
			"ds_5_0",
			&psh);

		if (!sts) {
			MessageBox(nullptr, "CreateHull Shader error", "error", MB_OK);
			return false;
		}

		// unordered_map�R���e�i�Ɋi�[
		m_dshashmap[filename] = psh;

		return true;
	}


	// ���_�V�F�[�_�[�Z�b�g
	bool SetVertexShader(std::string filename,
		D3D11_INPUT_ELEMENT_DESC* layout,
		unsigned int numElements) {

		

		// �f�o�C�X�擾
		ID3D11Device* device;
		device = GetDX11Device();
		ID3D11VertexShader* vsh;
		ID3D11InputLayout* vlayout;
		ID3DBlob* pBlob = nullptr;

		void* ShaderObject;
		size_t	ShaderObjectSize;

		// �t�@�C���̊g���q�ɍ��킹�ăR���p�C��
		HRESULT hr = CompileShader(
			filename.c_str(),
			"main",
			"vs_5_0",
			&ShaderObject,
			ShaderObjectSize,
			&pBlob);
		if (FAILED(hr))
		{
			if (pBlob)pBlob->Release();
			return false;
		}

		// ���_�V�F�[�_�[�𐶐�
		hr = device->CreateVertexShader(
			ShaderObject,
			ShaderObjectSize,
			nullptr,
			&vsh);
		if (FAILED(hr))
		{
			if (pBlob)pBlob->Release();
			return false;
		}

		// ���_�f�[�^��`����
		hr = device->CreateInputLayout(
			layout,
			numElements,
			ShaderObject,
			ShaderObjectSize,
			&vlayout);
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateInputLayout error", "error", MB_OK);
			pBlob->Release();
			return false;
		}

		// unordered_map�R���e�i�Ɋi�[
		m_vshashmap[filename] = vsh;
		m_layouthashmap[filename] = vlayout;

		// ���������
		if (pBlob)pBlob->Release();

		return true;
	}	// ���_�V�F�[�_�[�擾
	ID3D11VertexShader* GetVertexShader(std::string filenamekey) {
		// ���݂��邩���m���߂�
		auto it = m_vshashmap.find(filenamekey);
		if (it == m_vshashmap.end()) {
			return nullptr;
		}
		return m_vshashmap[filenamekey].Get();
	}

	// �s�N�Z���V�F�[�_�[�擾
	ID3D11PixelShader* GetPixelShader(std::string filenamekey) {
		// ���݂��邩���m���߂�
		auto it = m_pshashmap.find(filenamekey);
		if (it == m_pshashmap.end()) {
			return nullptr;
		}
		return m_pshashmap[filenamekey].Get();
	}

	// �n���V�F�[�_�[�擾
	ID3D11HullShader* GetHullShader(std::string filenamekey) {
		// ���݂��邩���m���߂�
		auto it = m_hullhashmap.find(filenamekey);
		if (it == m_hullhashmap.end()) {
			return nullptr;
		}
		return m_hullhashmap[filenamekey].Get();
	}

	// �h���C���V�F�[�_�[�擾
	ID3D11DomainShader* GetDomainShader(std::string filenamekey) {
		// ���݂��邩���m���߂�
		auto it = m_dshashmap.find(filenamekey);
		if (it == m_dshashmap.end()) {
			return nullptr;
		}
		return m_dshashmap[filenamekey].Get();
	}


	// ���_���C�A�E�g�擾
	ID3D11InputLayout* GetVertexLayout(std::string filenamekey) {
		// ���݂��邩���m���߂�
		auto it = m_layouthashmap.find(filenamekey);
		if (it == m_layouthashmap.end()) {
			MessageBox(nullptr, "Layout nullptr error", "error", MB_OK);
			return nullptr;
		}
		return m_layouthashmap[filenamekey].Get();
	}

	// �I������
	void Exit() {

		// ���
		for (auto data : m_vshashmap) {
			data.second->Release();
		}

		m_vshashmap.clear();

		// ���
		for (auto data : m_pshashmap) {
			data.second->Release();
		}

		m_pshashmap.clear();

		// ���
		for (auto data : m_hullhashmap) {
			data.second->Release();
		}

		m_hullhashmap.clear();

		// ���
		for (auto data : m_dshashmap) {
			data.second->Release();
		}

		m_dshashmap.clear();
		// ���
		for (auto data : m_layouthashmap) {
			data.second->Release();
		}

		m_layouthashmap.clear();
	}
private:
	ShaderHashmap() {}
	std::unordered_map<std::string, ComPtr<ID3D11VertexShader>> m_vshashmap;
	std::unordered_map<std::string, ComPtr<ID3D11PixelShader>> m_pshashmap;
	std::unordered_map<std::string, ComPtr<ID3D11HullShader>> m_hullhashmap;
	std::unordered_map<std::string, ComPtr<ID3D11DomainShader>> m_dshashmap;
	std::unordered_map<std::string, ComPtr<ID3D11InputLayout>> m_layouthashmap;
};