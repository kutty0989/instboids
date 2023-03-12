#pragma once
//=============================================================================
//
// �RD���f���`�揈�� [CModel.h]
//
//=============================================================================
#include"ModelData.h"
#include"uncopyable.h"
#include<d3d11.h>
#include<vector>
#include"animationdataassimp.h"
#include"obb.h"


using Microsoft::WRL::ComPtr;

class CModel : public Uncopyable {
private:
	//�t�@�C���`��
	enum FILETYPE {
		eDATFILE,
		eASSIMPFILE
	};

	FILETYPE				m_filetype = eASSIMPFILE;		// �t�@�C���^�C�v
	std::vector<AnimationDataAssimp*> m_animationcontainer;
	ID3D11VertexShader* m_pVertexShader = nullptr;		// ���_�V�F�[�_�[���ꕨ
	ID3D11PixelShader* m_pPixelShader = nullptr;		// �s�N�Z���V�F�[�_�[���ꕨ
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// ���_�t�H�[�}�b�g��`

	ID3D11ShaderResourceView* m_texSRV = nullptr;			// �e�N�X�`���r�q�u

	unsigned int	m_AnimFileIdx = 0;

public:

	ModelData				m_assimpfile;					// assimpfile
	//�e�V�F�[�_�[�쐬
	bool Init(const char* filename, const char* vsfile, const char* psfile, std::string texfolder);
	//�V�F�[�_�[���
	void Uninit();
	//���_�X�V
	void Update(
		int m_Frame, int m_preFrame, float m_factor, int animecnt,
		const DirectX::XMFLOAT4X4& mtxworld);
	void Update2(
	 int animecnt,
		const DirectX::XMFLOAT4X4& mtxworld);
	void Draw(DirectX::XMFLOAT4X4& mtxworld);
	unsigned int GetAnimationNum() {	// �A�j���[�V�����������擾

		return m_animationcontainer.size();//[m_AnimFileIdx]->GetScene()->mNumAnimations;
	}

	// �A�j���[�V���������[�h����
	bool LoadAnimation(const char* filename) {
		AnimationDataAssimp* animdata;

		animdata = new AnimationDataAssimp();
		bool sts = animdata->Init(filename);
		if (sts) {
			m_animationcontainer.push_back(animdata);
			return true;
		}
		else {
			MessageBox(nullptr, "Load Animation error", "error", MB_OK);
			return false;
		}
	}

	//���f���̃f�[�^�擾
	const ModelData& GetModelData() {
		return m_assimpfile;
	}

	//�M�Y���`��
	void DrawOBB() {
		m_assimpfile.DrawOBB();
	}

	
	const ModelData& GetModelData() const {
		return m_assimpfile;
	}

	
	void GetOBBList(std::vector<COBB*>& obblist) {

		// ���b�V���f�[�^�擾
		const std::vector<Mesh>& meshes = m_assimpfile.GetMeshes();

		// OBB�S���擾
		for (int i = 0; i < meshes.size(); i++) {
			const Mesh& m = meshes[i];
			for (auto data : m.m_obbvectorcontainer) {
				obblist.push_back(data);
			}
		}
	}
};