#pragma once
#include <memory>
#include <wrl/client.h>
#include<unordered_map>
#include"CModel.h"

using Microsoft::WRL::ComPtr;

const std::string zonbie = "assets/HangingIdle.fbx";
//const std::string zonbie = "assets/human_run.fbx";
//const std::string human = "assets/human_run.fbx";
//const std::string zonbie = "assets/3danime/zombie1.fbx";


class ModelMgr {
private:
	ModelMgr() {

	}
	std::unordered_map<std::string, std::unique_ptr<CModel>>m_modelhashmap;
	
public:
	ModelMgr(const ModelMgr&) = delete;
	ModelMgr& operator=(const ModelMgr&) = delete;
	ModelMgr(ModelMgr&&) = delete;
	ModelMgr& operator = (ModelMgr&&) = delete;

	static ModelMgr& GetInstance() {
		static ModelMgr Instance;
		return Instance;
	}

	virtual ~ModelMgr() {
		Finalize();
	}
	void Finalize() {
		for (auto itr = m_modelhashmap.begin();itr != m_modelhashmap.end();itr++) {
			(itr->second)->Uninit();
		}
	}

	bool LoadModel(std::string modelfilename, std::string vsfinlename, std::string psfilename, std::string texfilefolder) {
		std::unique_ptr<CModel> p;
		p = std::make_unique<CModel>();
	
		if (modelfilename == zonbie)
		{
			p->LoadAnimation("assets/3danime/ZombieIdle.fbx");
			p->LoadAnimation("assets/3danime/ZombieWalk.fbx");
			p->LoadAnimation("assets/3danime/ZombieRunning.fbx");

		}
	/*	if (modelfilename == human)
		{
			p->LoadAnimation("assets/3danime/human_run.fbx");
		
		}*/

		//���f���ǂݍ���
		bool sts = p->Init(modelfilename.c_str(), vsfinlename.c_str(), psfilename.c_str(), texfilefolder.c_str());
		if (!sts) {
			return false;
		}

		//unoredered_map�R���e�i�Ɋi�[
		m_modelhashmap[modelfilename].swap(p);

		
		return true;
	}

	CModel* GetModelPtr(std::string key) {
		//���݂��邩���m���߂�
		auto it = m_modelhashmap.find(key);
		if (it == m_modelhashmap.end()) {
			return nullptr;
		}
		return m_modelhashmap[key].get();
	}
};