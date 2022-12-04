//#include	"S_Enemy.h"
//#include	"drawaxis.h"
//#include    "CCamera.h"
//#include    "DX11Settransform.h"
//#include"IMgui/imgui.h"
//#include<iostream>
//#include"PlayerMgr.h"
////キャラの移動方向
////S_Enemy::DIRECTION g_direction = S_Enemy::DIRECTION::NEUTRAL;
//
//#define debuglog(a) std::cout<<a<<std::endl;
//
//static bool enemy_turn_flg;//敵がターンを消費したかどうか　true消費した　fまだ
//
//bool e = false;
//
//
//bool S_Enemy::Init() {
//
//	// 行列初期化
//	DX11MtxIdentity(m_mtx);
//	return true;
//
//	//シード値決定乱数
//	std::random_device rand_dev;
//
//	//シード値セット
//	m_mt.seed(rand_dev());
//	m_mt2.seed(rand_dev());
//	enemy_turn_flg = false;
//	m_action = S_Enemy::ACTION::ACT_NEUTRAL;
//	
//	
//}
//
//void S_Enemy::Draw() {
//
//	// モデル描画
//	//m_model->Draw(m_mtx);
//
//}
//
//void S_Enemy::DrawWithAxis() {
//
//	// モデル描画
//	drawaxis(m_mtx, 200, m_pos);
//	Draw();
//
//}
//
//struct FLOAT3
//{
//	float x, y, z;
//};
//
////
////void S_Enemy::AutoMove()
////{
////	
////	//乱数生成
////	std::uniform_int_distribution<int32_t> rand4(0, static_cast<int>(S_Enemy::ACTION::MAX_ACTION) - 1);
////
////	if (PlayerMgr::GetInstance()->Player_List.at(0)->judge_flg == false)//プレイヤーの移動判定が終わったフラグ
////	{
////		
////		if (m_action == S_Enemy::ACTION::ACT_NEUTRAL)
////		{
////		
////		
////			g_nowrotcnt = 0;
////			//行列作成（１フレーム分の回転を表す行列を作成）
////			//DX11MakeWorldMatrix(g_mtxframe, g_angle, trans);
////
////
////			//開始位置を保存
////			g_startpos.x = m_mtx._41;//X座標を保存
////			g_startpos.y = m_mtx._42;//Y座標を保存
////			g_startpos.z = m_mtx._43;//Z座標を保存
////
////			m_action = static_cast<ACTION>(rand4(m_mt));
////
////			
////		}
////		//debuglog((int)m_action);
////		//debuglog(e);
////		if((m_action != S_Enemy::ACTION::ACT_NEUTRAL) && (enemy_turn_flg == false))
////		{
////			//移動量の計算
////			XMFLOAT3 pos = { g_startpos.x,0.0f,g_startpos.z };
////
////			float t;
////			float s;
////
////			t = static_cast<float>(g_nowrotcnt + 1) / static_cast<float>(g_rotcnt);
////			s = 1 / static_cast<float>(g_rotcnt);
////
////
////			
////
////			//アクションにより回転をセット
////			switch (m_action) {
////
////			case S_Enemy::ACTION::ACT_LEFT://左回転（Y軸）
////			//終了位置を計算
////				endpos.x = g_startpos.x - 15.0f;
////				//線形保管の式でX座標を計算
////				pos.x = g_startpos.x * (1.0f - t) + endpos.x * t;
////				break;
////			case S_Enemy::ACTION::ACT_RIGHT://右回転（Y軸）
////
////		//終了位置を計算
////				endpos.x = g_startpos.x + 15.0f;
////				//線形保管の式でX座標を計算
////				pos.x = g_startpos.x * (1.0f - t) + endpos.x * t;
////				break;
////			case S_Enemy::ACTION::ACT_UP://上回転（X軸）
////
////				//終了位置を計算
////				endpos.z = g_startpos.z + 15.0f;
////				//線形保管の式でX座標を計算
////				pos.z = g_startpos.z * (1.0f - t) + endpos.z * t;
////				break;
////
////			case S_Enemy::ACTION::ACT_DOWN://上回転（X軸）
////
////				//終了位置を計算
////				endpos.z = g_startpos.z - 15.0f;
////				//線形保管の式でX座標を計算
////				pos.z = g_startpos.z * (1.0f - t) + endpos.z * t;
////				break;
////			}
////		//	////回転数をカウントアップ
////			g_nowrotcnt++;
////			if (g_nowrotcnt >= g_rotcnt) {
////				m_action = S_Enemy::ACTION::ACT_NEUTRAL;
////				enemy_turn_flg = true;
////
////			}
////
////			m_mtx._41 = pos.x;
////			m_mtx._42 = pos.y;
////			m_mtx._43 = pos.z;
////
////		}
////	}
////	//if (PlayerMgr::GetInstance()->Player_List.at(0)->judge_flg)
////	//{
////	//	if (enemy_turn_flg == true)
////	//	{
////	//		enemy_turn_flg = false;
////	//	}
////	//}
////
////
////}
////
//
//void S_Enemy::Action()
//{
//
//}
//
//void S_Enemy::Update() {
//	//if (m_sts == S_ENEMY_STATUS::S_ENEMY_LIVE)
//	//{
//	////	SetPos(XMFLOAT3(0.0f,0.0f,-150.0f));
//	//	AutoMove();
//	//}
//}
//
//void S_Enemy::Finalize() {
//	m_model->Uninit();
//
//}
