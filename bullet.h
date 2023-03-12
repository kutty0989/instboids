//=============================================================================
//
// 基底の弾の生成クラス [bullet.h]
//
//=============================================================================

#pragma once
#include<DirectXMath.h>
#include<vector>
#include<memory>
#include"gameobject.h"

//前方宣言
class CModel;

//弾ステータス
enum class BULLETSTATUS {
	LIVE,
	DEAD
};

class Bullet :public GameObject {
private:
	
	//弾の行列
	XMFLOAT4X4 rot = {};
	XMFLOAT4X4 scale = {};
	XMFLOAT4X4 trans = {};
	XMFLOAT4X4 world = {};

	XMFLOAT3 angle{ 0,0,0 };//回転角

	CModel* m_pmodel;//３Dモデル
	DirectX::XMFLOAT3 m_direction;//発射方向
	DirectX::XMFLOAT3 m_pos;

	float m_speed = 2.0f;//弾のスピード

	DirectX::XMFLOAT3 m_scale;

	XMFLOAT3 enemypos;//標的の場所
	
	bool goalpoint = false;//目的地についたかの判断
	
public:

	XMFLOAT3 nowpos;
	bool explosion = false;//爆発していいかの変数
	BULLETSTATUS  m_sts;//ステータス
	float m_life = 0;//弾の消滅までの時間
	float explocnt = 0;//爆発までの変数

	//弾の初期化
	bool Init();

	//弾の再生成
	void Remake(XMFLOAT3 pos);

	//弾の描画
	void Draw();

	//更新
	void Update();

	//終了処理
	void Finalize(){};

	//弾のモデルをセット
	void SetModel(CModel* p) {
		m_pmodel = p;
	}

	//弾のモデルを取ってくる
	CModel* GetModel() {
		return m_pmodel;
	}

	//方向をセットする
	void SetDirection(DirectX::XMFLOAT4X4 mtx) {
		m_mtx = mtx;
		m_direction = DirectX::XMFLOAT3(mtx._31, mtx._32, mtx._33);
	}

	//生きているか判断する関数
	bool isLive() {
		if (m_sts == BULLETSTATUS::LIVE) {
			return true;
		}
		else {
			return false;
		}
	}

	//初期値をセットする関数
	void SetInitialPos(float x, float y, float z)
	{
		m_pos = { x,y,z };
	}

	//大きさをセットする関数
	void SetScale(float x, float y, float z)
	{
		m_scale = { x,y,z };
	}

	//爆発のビルボードを描画する為の関数
	void BillBoardExplosion();

};