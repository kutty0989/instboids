//========================================================
//AnimationDataAssimp.cpp
//			アシンプ内のアニメーションを行うクラス
//========================================================
#include	<windows.h>
#include	"AnimationDataAssimp.h"

/// <summary>
/// アシンプ読み込み
/// </summary>
/// <param name="filename">ファイル名</param>
/// <returns>成否</returns>
bool AnimationDataAssimp::Init(std::string filename) {

	bool sts = m_assimpscene.Init(filename);
	if (!sts) {
		MessageBox(nullptr, "SkinAnimationDataAssimp load error", "error", MB_OK);
	}

	return true;
}

/// <summary>
/// 終了処理
/// </summary>
void AnimationDataAssimp::Exit() {
	m_assimpscene.Exit();
}