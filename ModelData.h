#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <assimp\scene.h>
#include <map>
#include <assimp\Importer.hpp>
#include "dx11mathutil.h"
#include "Mesh.h"
#include "CDirectxGraphics.h"
#include "animationdataassimp.h"



class ModelData
{
public:
	bool animationreset = false;


	ModelData();
	~ModelData();

	// �R�s�[�֎~
	ModelData(const ModelData&) = delete;
	ModelData& operator=(const ModelData&) = delete;

	// ���[�u�֎~
	ModelData(ModelData&&) = delete;
	ModelData& operator=(ModelData&&) = delete;

	bool Load(std::string resourcefolder, std::string filename);

	void Draw(ID3D11DeviceContext* devcon, DirectX::XMFLOAT4X4& mtxworld);
	void Drawinstance(ID3D11DeviceContext* devcon);
	
	void Update(int m_Frame, int m_preFrame, float m_factor, int animecnt,
		const XMFLOAT4X4& mtxworld,
		unsigned int animfileno,
		std::vector<AnimationDataAssimp*>& animationcontainer);
	
	void Update2(int animecnt,
		const XMFLOAT4X4& mtxworld,
		unsigned int animfileno,
		std::vector<AnimationDataAssimp*>& animationcontainer);

	void DrawOBB();

	void Exit();

	const std::vector<Mesh>& GetMeshes()const {
		return m_meshes;
	}
	void UpdateOBB(const XMFLOAT4X4& mtxworld);

	void LoadMaterial();						// �}�e���A����ǂݍ���
private:


	AssimpScene m_assimpscene;					// assimp scene
	std::vector<Mesh> m_meshes;					// ���b�V���̏W�������f��
	std::string m_directory;					// �e�N�X�`���t�@�C���̈ʒu
	std::vector<Texture> m_texturesloaded;		// ���Ƀ��[�h����Ă���e�N�X�`��
	std::vector<Material> m_materials;			// �}�e���A���Q

	void processNode(aiNode* node, const aiScene* scene);				// �m�[�h�����
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, int meshidx);	// ���b�V�������
																																				// �}�e���A���ɑΉ������e�N�X�`�����擾����
	std::vector<Texture> loadMaterialTextures(
		aiMaterial* mat,
		aiTextureType type,
		std::string typeName,
		const aiScene* scene);


	int m_Frame = 0;								// �t���[���ԍ�
	std::vector<const aiScene*> m_sceneAnimContainer;	// �A�j���[�V�����R���e�i

	int m_cnt = 0;								// �L�[�t���[����ԗp
	int m_preFrame = 0;							// �L�[�t���[����ԗp
	float m_factor = 0.0f;						// �L�[�t���[����ԗp
	std::map<std::string, BONE> m_Bone;			//�{�[���f�[�^�i�m�[�h�̖��O�ŎQ�Ɓj
	ID3D11Buffer* m_constantbufferbonematrix;	// �{�[���s��i�[�p�萔�o�b�t�@	
	
	void CreateBone(aiNode* node);			// �{�[������
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);	// �{�[���s��X�V
	void UpdateBoneMatrixConstantBuffer();	// �{�[���s���萔�o�b�t�@�ɔ��f������

};

