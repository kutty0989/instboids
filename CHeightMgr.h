#pragma once
#pragma once
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
	std::unordered_map<std::string, std::unique_ptr<CHeight_Map>>m_texhashmap;

public:

	static std::list<CHeight_Map*>spriteList;

	CHeightMgr(const CHeightMgr&) = delete;
	CHeightMgr& operator=(const CHeightMgr&) = delete;
	CHeightMgr(CHeightMgr&&) = delete;
	CHeightMgr& operator = (CHeightMgr&&) = delete;


	static void Draw()
	{
		for (auto& sprite : spriteList)
		{
			sprite->Draw();
		}
	};

	static CHeightMgr& GetInstance() {
		static CHeightMgr Instance;
		return Instance;
	}

	virtual ~CHeightMgr() {
		Finalize();
	}
	void Finalize() {
		for (auto itr = m_texhashmap.begin();itr != m_texhashmap.end();itr) {
			//(itr->second)->Uninit();
		}
	}

	bool LoadModel(std::string texfilename, std::string vsfinlename, std::string psfilename) {
		std::unique_ptr<CHeight_Map> p;
		p = std::make_unique<CHeight_Map>();

		//モデル読み込み
		bool sts = p->LoadTexture(texfilename.c_str(),0);
		if (!sts) {
			return false;
		}
		//unoredered_mapコンテナに格納
		m_texhashmap[texfilename].swap(p);

		return true;
	}

	CHeight_Map* GetModelPtr(std::string key) {
		//存在するかを確かめる
		auto it = m_texhashmap.find(key);
		if (it == m_texhashmap.end()) {
			return nullptr;
		}
		return m_texhashmap[key].get();
	}
};