#pragma once
#pragma once
#pragma once
#include <memory>
#include <wrl/client.h>
#include<unordered_map>
#include"CModel.h"
#include"CTex.h"

using Microsoft::WRL::ComPtr;

class CTexMgr {
private:
	CTexMgr() {

	}
	std::unordered_map<std::string, std::unique_ptr<CTex>>m_texhashmap;

public:
	CTexMgr(const CTexMgr&) = delete;
	CTexMgr& operator=(const CTexMgr&) = delete;
	CTexMgr(CTexMgr&&) = delete;
	CTexMgr& operator = (CTexMgr&&) = delete;

	static CTexMgr& GetInstance() {
		static CTexMgr Instance;
		return Instance;
	}

	virtual ~CTexMgr() {
		Finalize();
	}
	void Finalize() {
		for (auto itr = m_texhashmap.begin();itr != m_texhashmap.end();itr++) {
			(itr->second)->UnInit();
		}
	}

	bool LoadModel(std::string texfilename, std::string vsfinlename, std::string psfilename) {
		std::unique_ptr<CTex> p;
		p = std::make_unique<CTex>();

		//モデル読み込み
		bool sts = p->LoadTexture(texfilename.c_str());
		if (!sts) {
			return false;
		}
		//unoredered_mapコンテナに格納
		m_texhashmap[texfilename].swap(p);

		return true;
	}

	CTex* GetModelPtr(std::string key) {
		//存在するかを確かめる
		auto it = m_texhashmap.find(key);
		if (it == m_texhashmap.end()) {
			return nullptr;
		}
		return m_texhashmap[key].get();
	}
};