//#pragma once
//#pragma once
//#include	"gameobject.h"
//#include	"CModel.h"
//#include	"dx11mathutil.h"
//#include	"CDirectInput.h"
//#include<random>
//
//class S_Enemy :public GameObject {
//private:
//	CModel* m_model = nullptr;						// ÇRÇcÉÇÉfÉã
//
//	//èÛë‘
//	enum class S_ENEMY_STATUS {
//		S_ENEMY_LIVE = 0,
//		S_ENEMY_DEAD,
//	};
//
//	enum class ACTION {
//	
//		ACT_NEUTRAL,
//
//		ACT_LEFT,
//		ACT_RIGHT,
//		ACT_UP,
//		ACT_DOWN,
//
//		
//		MAX_ACTION
//	};
//
//	std::mt19937  m_mt;//óêêîî≠ê∂óp
//	std::mt19937  m_mt2;
//
//	//âÒì]âÒêî
//	//const int g_movecnt = 30;
//	//ç°ÇÃâÒì]âÒêî
//	int g_nowrotcnt = 0;
//
//	DirectX::XMFLOAT3 g_startpos;
//
//	const int  g_rotcnt = 8;
//
//	XMFLOAT2 addpower;
//	XMFLOAT3 endpos;
//
//
//
//	ACTION   m_action;//ÉAÉNÉVÉáÉìéÌï 
//
//
//	void Action();
//
//	
//
//	
//public:
//	S_ENEMY_STATUS m_sts = S_ENEMY_STATUS::S_ENEMY_LIVE;
//
//
//
//	bool Init();
//
//	void Draw();
//
//	void DrawWithAxis();
//
//	void Update();
//
//	void Finalize();
//
//	void AutoMove();
//
//
//	bool isLive() {
//		if (m_sts == S_ENEMY_STATUS::S_ENEMY_LIVE) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	void isDead()
//	{
//		m_sts = S_ENEMY_STATUS::S_ENEMY_DEAD;
//	}
//
//
//	//bool CheckInputDirection();
//
//	const CModel* GetModel()
//	{
//		return m_model;
//	}
//
//	void SetModel(CModel* model)
//	{
//		m_model = model;
//	}
//	void SetPos(XMFLOAT3 pos)
//	{
//		m_pos = pos;
//	}
//
//	void SetColor(XMFLOAT4 col)
//	{
//		m_color = col;
//	}
//	
//};