#pragma once
//========================================================
//AnimationDataAssimp.h
//			アシンプ内のアニメーションを行うクラス
//========================================================
#include "assimpscene.h"

class AnimationDataAssimp {
private:
	AssimpScene		m_assimpscene;
public:
	//アシンプの読み子み
	bool Init(std::string filename);
	//シーンの取得
	const aiScene* GetScene() {
		return m_assimpscene.GetScene();
	}
	//終了処理
	void Exit();
};