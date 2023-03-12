#pragma once
//=============================================================================
//
// �e�N�X�`���[�Ǘ��N���X [TexMgr.h]
//
//=============================================================================
#include<list>
#include<DirectXMath.h>
#include"granate.h"
#include"Score.h"

class TexMgr
{
public:

	//����������
	void Init();

	void Remake(DirectX::XMFLOAT4X4 mtx, XMFLOAT3 pos);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�I������
	void Finalize();

	//�X�R�A�̃C���X�g�𐧍�
	void ScoreCreate(XMFLOAT3 pos);

	static TexMgr* GetInstance()
	{
		static TexMgr instance;
		return &instance;
	}

	
	std::vector <std::unique_ptr<Score>> g_scorevector;//�X�R�A�̃C���X�g�z��


private:


};
