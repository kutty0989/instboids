//#pragma once
//#include"gameobject.h"
//#include"CModel.h"
//#include"player.h"
//
//class Build :public GameObject {
//private:
//	
//	CModel* m_pmodel;//RDf
//	DirectX::XMFLOAT3 m_direction;
//	DirectX::XMFLOAT3 m_pos;
//	DirectX::XMFLOAT3 m_scale;
//
//	float dx = 0;//vC[Æ¨Ì£@
//	float dy = 0;//vC[Æ¨Ì£@
//	float dist = 0;//vC[Æ¨Ì£
//	float nier = 100;//vC[Æ¨Ì£Ìèl
//	
//	int buildup_cnt = 100;
//	int createcnt = 0;
//	int buildlevel = 1;
//public:
//	bool nier_flg = false;
//	
//	bool Init();
//	bool Init(XMFLOAT3 pos);
//
//	void Draw();
//
//	void Update(std::shared_ptr<BoidsAI>& ImPlayer, std::vector<shared_ptr<BoidsAI>>& in_player_vector);
//
//	bool CreateBuildBoids();
//
//	void Finalize();
//
//
//	static Build* GetInstance()
//	{
//		static Build instance;
//		return &instance;
//	}
//
//	void SetModel(CModel* p) {
//		m_pmodel = p;
//	}
//	CModel* GetModel() {
//		return m_pmodel;
//	}
//
//	void SetInitialPos(float x, float y, float z)
//	{
//		m_pos = { x,y,z };
//	}
//	void SetScale(float x, float y, float z)
//	{
//		m_scale = { x,y,z };
//	}
//
//};
