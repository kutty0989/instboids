#pragma once
#include <memory>
#include <wrl/client.h>
#include<unordered_map>
#include"CModel.h"
#include"CBillBoard.h"

using Microsoft::WRL::ComPtr;

class CBillBoardMgr {
private:
	CBillBoardMgr() {

	}
	std::unordered_map<std::string, std::unique_ptr<CBillBoard>>m_texhashmap;

public:
	CBillBoardMgr(const CBillBoardMgr&) = delete;
	CBillBoardMgr& operator=(const CBillBoardMgr&) = delete;
	CBillBoardMgr(CBillBoardMgr&&) = delete;
	CBillBoardMgr& operator = (CBillBoardMgr&&) = delete;

	static CBillBoardMgr& GetInstance() {
		static CBillBoardMgr Instance;
		return Instance;
	}

	virtual ~CBillBoardMgr() {
		Finalize();
	}
	void Finalize() {
		for (auto itr = m_texhashmap.begin();itr != m_texhashmap.end();itr++) {
			(itr->second)->Dispose();
		}
	}

	bool LoadModel(std::string texfilename, std::string vsfinlename, std::string psfilename) {
		std::unique_ptr<CBillBoard> p;
		p = std::make_unique<CBillBoard>();

		//モデル読み込み
		bool sts = p->LoadTexTure(texfilename.c_str());
		if (!sts) {
			return false;
		}
		//unoredered_mapコンテナに格納
		m_texhashmap[texfilename].swap(p);

		return true;
	}

	CBillBoard* GetModelPtr(std::string key) {
		//存在するかを確かめる
		auto it = m_texhashmap.find(key);
		if (it == m_texhashmap.end()) {
			return nullptr;
		}
		return m_texhashmap[key].get();
	}
};