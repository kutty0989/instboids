#pragma once
#include	<directxmath.h>
#include    "DX11Settransform.h"
#include"IMgui/imgui.h"
#include<iostream>
#include <math.h>
#include"Bpm_Data.h"
class GameObject {
	uint64_t m_id = 0;						// ���ʎq
protected:
	DirectX::XMFLOAT3 m_pos{};				// �I�u�W�F�N�g�̈ʒu
	DirectX::XMFLOAT4 m_rotation{};				// �I�u�W�F�N�g�̈ʒu
	
	DirectX::XMFLOAT4 m_color{};              //�J���[/



public:
	DirectX::XMFLOAT4X4 m_mtx{};				// �p��

	GameObject() {};
	virtual ~GameObject() {}
	virtual bool Init() = 0;
	virtual void Finalize() = 0;

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

	STATUS m_sts;

};