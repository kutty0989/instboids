#pragma once
#pragma once
#include <memory>
#include <wrl/client.h>
#include<unordered_map>

#include"CModelInstance.h"
using Microsoft::WRL::ComPtr;

//const std::string zonbie = "assets/human_run.fbx";
//const std::string human = "assets/human_run.fbx";
//const std::string zonbie = "assets/3danime/zombie1.fbx";


class InstanceModelMgr {
private:
	InstanceModelMgr() {

	}
	
public:
	std::unordered_map<std::string, std::unique_ptr<CModelInstance>>m_modelinstancehashmap;

	InstanceModelMgr(const InstanceModelMgr&) = delete;
	InstanceModelMgr& operator=(const InstanceModelMgr&) = delete;
	InstanceModelMgr(InstanceModelMgr&&) = delete;
	InstanceModelMgr& operator = (InstanceModelMgr&&) = delete;

	static InstanceModelMgr& GetInstance() {
		static InstanceModelMgr Instance;
		return Instance;
	}

	virtual ~InstanceModelMgr() {
		Finalize();
	}
	void Finalize() {
		for (auto itr = m_modelinstancehashmap.begin();itr != m_modelinstancehashmap.end();itr++) {
			(itr->second)->Uninit();
		}
	}

	


	bool LoadInstanceModel(int num, std::string modelfilename, std::string vsfinlename, std::string psfilename, std::string texfoldername) {
		std::unique_ptr<CModelInstance> p;
		p = std::make_unique<CModelInstance>();


		/*	if (modelfilename == human)
			{
				p->LoadAnimation("assets/3danime/human_run.fbx");

			}*/

			//モデル読み込み
		bool sts = p->InitiInstancing(num, modelfilename.c_str(), vsfinlename.c_str(), psfilename.c_str(),texfoldername.c_str());
		if (!sts) {
			return false;
		}

		//unoredered_mapコンテナに格納
		m_modelinstancehashmap[modelfilename].swap(p);


		return true;
	}

	bool InstanceDraw(std::string modelfilename) {

		GetInstanceModelPtr(modelfilename)->DrawInstance();
		//m_modelinstancehashmap[modelfilename]->DrawInstance();

		return true;
	}
	bool InstanceUpdate(std::string modelfilename, XMFLOAT4X4 mat[]) {
	//	GetInstanceModelPtr(modelfilename)->Update(mat);

	//	m_modelinstancehashmap[modelfilename]->Update(mat);

		return true;
	}


	CModelInstance* GetInstanceModelPtr(std::string key) {
		//存在するかを確かめる
		auto it = m_modelinstancehashmap.find(key);
		if (it == m_modelinstancehashmap.end()) {
			return nullptr;
		}
		return m_modelinstancehashmap[key].get();
	}
};