#pragma once
//=============================================================================
//
// �n�C�g�}�b�v�����Ǘ��N���X[CHeightMgr.h]
//
//=============================================================================
#include <memory>
#include <wrl/client.h>
#include<unordered_map>
#include"CModel.h"
#include"CHeight_Map.h"

using Microsoft::WRL::ComPtr;

class CHeightMgr {
private:
	CHeightMgr() {

	}
	std::unordered_map<std::string, std::unique_ptr<CHeight_Map>>m_texhashmap;//�n�C�g�}�b�v���}�b�v�œZ�߂�

public:

	//�R���X�g���N�^
	CHeightMgr(const CHeightMgr&) = delete;
	CHeightMgr& operator=(const CHeightMgr&) = delete;
	CHeightMgr(CHeightMgr&&) = delete;
	CHeightMgr& operator = (CHeightMgr&&) = delete;

	//�V���O���g��
	static CHeightMgr& GetInstance() {
		static CHeightMgr Instance;
		return Instance;
	}

	//�f�X�g���N�^�@�I������
	virtual ~CHeightMgr() {
		Finalize();
	}
	void Finalize() {
		for (auto itr = m_texhashmap.begin();itr != m_texhashmap.end();itr) {
			//(itr->second)->Uninit();
		}
	}

	//�J���[���Ɏg���摜��z��Ɋi�[
	bool LoadModel(std::string texfilename, std::string vsfinlename, std::string psfilename) {
		std::unique_ptr<CHeight_Map> p;
		p = std::make_unique<CHeight_Map>();

		//���f���ǂݍ���
		bool sts = p->LoadTexture(texfilename.c_str(),0);
		if (!sts) {
			return false;
		}
		//unoredered_map�R���e�i�Ɋi�[
		m_texhashmap[texfilename].swap(p);

		return true;
	}


	CHeight_Map* GetModelPtr(std::string key) {
		//���݂��邩���m���߂�
		auto it = m_texhashmap.find(key);
		if (it == m_texhashmap.end()) {
			return nullptr;
		}
		return m_texhashmap[key].get();
	}
};