#pragma once
#include	<directxmath.h>
#include    "DX11Settransform.h"
#include"IMgui/imgui.h"
#include<iostream>
#include <math.h>
#include"dx11mathutil.h"
#include"Bpm_Data.h"
class GameObject {
	
protected:
	DirectX::XMFLOAT3 m_pos{};				// �I�u�W�F�N�g�̈ʒu
	DirectX::XMFLOAT4 m_rotation{};				// �I�u�W�F�N�g�̈ʒu
	
	DirectX::XMFLOAT4 m_color{};              //�J���[/
	unsigned int			m_id;			// �h�c


public:
	 void Init() {
		DirectX::XMFLOAT3 p = { 0, 0, 0 };
		SetPosition(p);
		DX11QtIdentity(m_rotation);
	}

	 void Uninit() {

	}

	 void Draw() {

	}

	 void Update(const DirectX::XMFLOAT4& q, const DirectX::XMFLOAT3& pos) {
	}

	DirectX::XMFLOAT4X4 m_mtx{};				// �p��

	// �p�����擾
	DirectX::XMFLOAT4X4 GetMtx() {
		return m_mtx;
	}

	// �ʒu���擾
	DirectX::XMFLOAT3 GetPos() {
		return m_pos;
	}

	// �h�c���擾
	uint64_t GetID() {
		return m_id;
	}


	enum class STATUS
	{
		LIVE,
		DEAD
	};

	

	void SetPosition(const DirectX::XMFLOAT3& pos) {
		m_pos = pos;
	}

	void SetRotation(const DirectX::XMFLOAT4& qt) {
		m_rotation = qt;
	}

	DirectX::XMFLOAT4 GetRotation() const {
		return m_rotation;
	}

	DirectX::XMFLOAT3 GetPosition() const {
		return m_pos;
	}
	STATUS m_sts;

};