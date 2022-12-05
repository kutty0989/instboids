#pragma once
#include	<directxmath.h>
#include    "DX11Settransform.h"
#include"IMgui/imgui.h"
#include<iostream>
#include <math.h>
#include"Bpm_Data.h"
class GameObject {
	uint64_t m_id = 0;						// 識別子
protected:
	DirectX::XMFLOAT3 m_pos{};				// オブジェクトの位置
	DirectX::XMFLOAT4 m_rotation{};				// オブジェクトの位置
	
	DirectX::XMFLOAT4 m_color{};              //カラー/



public:
	DirectX::XMFLOAT4X4 m_mtx{};				// 姿勢

	GameObject() {};
	virtual ~GameObject() {}
	virtual bool Init() = 0;
	virtual void Finalize() = 0;

	// 姿勢を取得
	DirectX::XMFLOAT4X4 GetMtx() {
		return m_mtx;
	}

	// 位置を取得
	DirectX::XMFLOAT3 GetPos() {
		return m_pos;
	}

	// ＩＤを取得
	uint64_t GetID() {
		return m_id;
	}


	enum class STATUS
	{
		LIVE,
		DEAD
	};

	STATUS m_sts;

};