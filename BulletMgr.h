#pragma once
//=============================================================================
//
// �o���b�g�}�l�[�W���[ [BulletMgr.h]
//
//=============================================================================

#include"bullet.h"

class BulletMgr
{
public:

	void Init();//�o���b�g�̐����܂Ƃ�

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);//�V�����e����蒼��

	void Update();//�ꏊ���X�V

	void Draw();//�`��

	void Finalize();//�I������


	static BulletMgr* GetInstance()
	{
		static BulletMgr instance;
		return &instance;
	}


	void BulletCreate();//�o���b�g�̐���

	std::list<std::unique_ptr<Bullet>> g_bullets;//�e�̔z��

private:


};