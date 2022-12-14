#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp/cimport.h>
#include <unordered_map>
#include <vector>
#include "animationdataassimp.h"
#include "Shader.h"
#include "memory.h"
#include "ModelData.h"
#include "vertexproto.h"
#include "DX11Settransform.h"
#include "CDirectxGraphics.h"
#include "utftosjisconv.h"
#include<iostream>

#include"CDirectInput.h"
const int INTERPOLATENUM = 4;			// ��Ԑ�

#define debuglog(a) std::cout<<a<<std::endl;

std::vector<Texture> ModelData::loadMaterialTextures(
	aiMaterial* mtrl,
	aiTextureType type,
	std::string typeName,
	const aiScene* scene)
{
	std::vector<Texture> textures;		// ���̃}�e���A���Ɋ֘A�Â���DIFFUSE�e�N�X�`���̃��X�g
	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

	dev = CDirectXGraphics::GetInstance()->GetDXDevice();
	devcon = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// �}�e���A������e�N�X�`�������擾��(��{��1��)���[�v����
	for (unsigned int i = 0; i < mtrl->GetTextureCount(type); i++)
	{
		aiString str;

		// �}�e���A�����炉�Ԗڂ̃e�N�X�`���t�@�C�������擾����
		mtrl->GetTexture(type, i, &str);

		// �������Ƀ��[�h���ꂽ�e�N�X�`���ł���΃��[�h���X�L�b�v����
		bool skip = false;

		// ���[�h�ς݃e�N�X�`���������[�v����
		for (unsigned int j = 0; j < m_texturesloaded.size(); j++)
		{
			// �t�@�C�����������ł�������ǂݍ��܂Ȃ�
			if (std::strcmp(m_texturesloaded[j].path.c_str(), str.C_Str()) == 0)
			{
				// �ǂݍ��ݍς݂̃e�N�X�`������DIFFUSE�e�N�X�`���̃��X�g�ɃZ�b�g
				textures.push_back(m_texturesloaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // �܂��ǂݍ��܂�Ă��Ȃ������ꍇ
			Texture tex;

			std::string filename = std::string(str.C_Str());
			std::string filenameonly = ExtractFileName(filename, '\\/');		// �t�@�C�������擾
		//	std::string filenameonly = ExtractFileName(filename, "\\");		// �t�@�C�������擾
			//filename = ExtractFileName(filename, '\\');		// �t�@�C�������擾
			filename = m_directory + filenameonly;				// ���\�[�X�f�B���N�g���{�t�@�C����
		//	MessageBox(nullptr, filename.c_str(), "load tex", MB_OK);

			bool sts = CreateSRVfromFile(
				filename.c_str(),
				dev, devcon, &tex.texres, &tex.texture);
			if (!sts) {
				// �������������t�s�e�W�Őݒ肳��Ă����ꍇ�ɑΉ�
				filenameonly = utf8_to_multi_winapi(std::string(filenameonly.c_str()));
				filename = m_directory + filenameonly;	// ���\�[�X�f�B���N�g���{�t�@�C����

				bool sts = CreateSRVfromFile(
					filename.c_str(),
					dev, devcon, &tex.texres, &tex.texture);
			/*	if (!sts) {
					MessageBox(nullptr, "Texture couldn't be loaded", "Error!", MB_ICONERROR | MB_OK);
					tex.texture = nullptr;
				}*/
			}

			tex.type = typeName;
			tex.path = str.C_Str();
			// �e�N�X�`������DIFFUSE�e�N�X�`���̃��X�g�ɃZ�b�g
			textures.push_back(tex);
			this->m_texturesloaded.push_back(tex);	// ���̃��f���Ɋ֘A�Â����e�N�X�`�����X�g�ɃZ�b�g
		}
	}

	return textures;
}

ModelData::ModelData()
{
}

ModelData::~ModelData()
{
	Exit();
}

void ModelData::CreateBone(aiNode* node)
{
	BONE bone;

	// �m�[�h�����L�[�ɂ��ă{�[������ۑ�
	m_Bone[node->mName.C_Str()] = bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		CreateBone(node->mChildren[n]);
	}
}


bool ModelData::Load(std::string resourcefolder,
	std::string filename)
{
	bool sts = m_assimpscene.Init(filename);
	if (!sts) {
		MessageBox(nullptr, "ModelData load error", "error", MB_OK);
		return false;
	}

	m_directory = resourcefolder;		// ���̃��f���̃e�N�X�`�������݂���f�B���N�g��

	
	// �{�[���𐶐�����
	CreateBone(m_assimpscene.GetScene()->mRootNode);

		// �{�[���̔z��ʒu���i�[����
	unsigned int num = 0;
	for (auto& data : m_Bone) {
		data.second.idx = num;
		num++;
	}


	LoadMaterial();						// ���̃��f���Ŏg�p����Ă���}�e���A�����擾����

	// ai�m�[�h����͂���
	processNode(m_assimpscene.GetScene()->mRootNode, m_assimpscene.GetScene());

	// �{�[���s��i�[�p�̒萔�o�b�t�@�𐶐�����

	ID3D11Device* device;
	device = CDirectXGraphics::GetInstance()->GetDXDevice();

	sts = CreateConstantBufferWrite(device, sizeof(ConstantBufferBoneMatrix), &m_constantbufferbonematrix);
	if (!sts) {
		MessageBox(nullptr, "constant buffer create(bonematrix) fail", "error", MB_OK);
	}

	return true;
}


void ModelData::LoadMaterial() {

	// �}�e���A�������݂��邩�H
	if (m_assimpscene.GetScene()->HasMaterials()) {
		// �}�e���A���� �擾
		int nummaterial = m_assimpscene.GetScene()->mNumMaterials;

		for (int i = 0; i < nummaterial; i++) {
			Material mtrl;

			// i�Ԗڂ̃}�e���A�����擾
			aiMaterial* mat = m_assimpscene.GetScene()->mMaterials[i];

			aiColor3D colordiffuse(1.f, 1.f, 1.f);
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, colordiffuse);
			mtrl.m_Diffuse.x = colordiffuse.r;
			mtrl.m_Diffuse.y = colordiffuse.g;
			mtrl.m_Diffuse.z = colordiffuse.b;
			//mtrl.m_Diffuse.x = 1.0f;
			//mtrl.m_Diffuse.y = 1.0f;
			//mtrl.m_Diffuse.z = 1.0f;

			aiColor3D colorspecular(0.f, 0.f, 0.f);
			mat->Get(AI_MATKEY_COLOR_SPECULAR, colorspecular);
			mtrl.m_Specular.x = colorspecular.r;
			mtrl.m_Specular.y = colorspecular.g;
			mtrl.m_Specular.z = colorspecular.b;

			aiColor3D colorambient(0.f, 0.f, 0.f);
			mat->Get(AI_MATKEY_COLOR_AMBIENT, colorambient);
			mtrl.m_Ambient.x = colorambient.r;
			mtrl.m_Ambient.y = colorambient.g;
			mtrl.m_Ambient.z = colorambient.b;

			aiColor3D coloremissive(0.f, 0.f, 0.f);
			mat->Get(AI_MATKEY_COLOR_EMISSIVE, coloremissive);
			mtrl.m_Emissive.x = coloremissive.r;
			mtrl.m_Emissive.y = coloremissive.g;
			mtrl.m_Emissive.z = coloremissive.b;

			float power;
			mat->Get(AI_MATKEY_SHININESS_STRENGTH, power);
			mtrl.m_SpecularPower = power;

			m_materials.push_back(mtrl);
		}
	}
}

void ModelData::Draw(ID3D11DeviceContext* devcon, XMFLOAT4X4& mtxworld)
{
	// �A�j���[�V�����f�[�^�������Ă��邩�H
	if (m_assimpscene.HasAnimation())
	{	// �{�[���s���萔�o�b�t�@�ɔ��f������
		UpdateBoneMatrixConstantBuffer();
	}

	for (int i = 0; i < m_meshes.size(); i++)
	{   
		// ���[���h�ϊ��s��
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtxworld);
		// �萔�o�b�t�@�Z�b�g����
		m_meshes[i].Draw(devcon);
	}
}
//test
//void ModelData::Drawinstance(ID3D11DeviceContext* devcon)
//{
//	// �A�j���[�V�����f�[�^�������Ă��邩�H
//	if (m_assimpscene.HasAnimation())
//	{	// �{�[���s���萔�o�b�t�@�ɔ��f������
//		UpdateBoneMatrixConstantBuffer();
//	}
//
//	for (int i = 0; i < m_meshes.size(); i++)
//	{
//		// ���[���h�ϊ��s��
//	//	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD, mtxworld);
//		// �萔�o�b�t�@�Z�b�g����
//		m_meshes[i].Drawinstance(devcon);
//	}
//}


void ModelData::DrawOBB() {
	// OBB�`��
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].DrawOBB(m_Bone);
	}
}

void ModelData::UpdateOBB(const XMFLOAT4X4& mtxworld) {
	// ���b�V����OBB�X�V
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].UpdateOBB(m_Bone, mtxworld);
	}
}

// ���b�V���̉��
Mesh ModelData::processMesh(aiMesh* mesh, const aiScene* scene, int meshidx)
{
	std::vector<Vertex> vertices;			// ���_
	std::vector<unsigned int> indices;		// �ʂ̍\�����
	std::vector<Texture> textures;			// �e�N�X�`��
	Material mtrl;

	// ���_�����擾
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.m_Pos.x = mesh->mVertices[i].x;
		vertex.m_Pos.y = mesh->mVertices[i].y;
		vertex.m_Pos.z = mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
		if (mesh->HasNormals()) {
			vertex.m_Normal.x = mesh->mNormals[i].x;
			vertex.m_Normal.y = mesh->mNormals[i].y;
			vertex.m_Normal.z = mesh->mNormals[i].z;
		}
		else {
			vertex.m_Normal.x = 0.0f;
			vertex.m_Normal.y = 0.0f;
			vertex.m_Normal.z = 0.0f;
		}

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
		if (mesh->HasTextureCoords(0)) {
			vertex.m_Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.m_Tex.y = mesh->mTextureCoords[0][i].y;
		}


		vertex.m_BoneNum = 0;

		for (unsigned int b = 0; b < 4; b++)
		{
			vertex.m_BoneIndex[b] = -1;
			vertex.m_BoneName[b] = "";
			vertex.m_BoneWeight[b] = 0.0f;
		}


		vertices.push_back(vertex);
	}


	//�{�[���f�[�^������
	for (unsigned int b = 0; b < mesh->mNumBones; b++)
	{
		// ���b�V���Ɋ֘A�Â��Ă�{�[�������擾
		aiBone* bone = mesh->mBones[b];

		// �{�[���I�t�Z�b�g�s����擾
		m_Bone[bone->mName.C_Str()].OffsetMatrix = bone->mOffsetMatrix;

		// �{�[���Ɋ֘A�Â��Ă��钸�_��I�Ѥ�E�F�C�g�l���Z�b�g����
		for (unsigned int widx = 0; widx < bone->mNumWeights; widx++)
		{
			aiVertexWeight weight = bone->mWeights[widx];

			unsigned int vidx = weight.mVertexId;			// ���̃E�G�C�g�Ɋ֘A�Â��Ă钸�_idx

			// ���b�V���̒��̉��Ԗڂ�
			vertices[vidx].m_BoneWeight[vertices[vidx].m_BoneNum] = weight.mWeight;
			vertices[vidx].m_BoneName[vertices[vidx].m_BoneNum] = bone->mName.C_Str();
			// �Y������{�[�����̃C���f�b�N�X�l���Z�b�g
			auto it = vertices[vidx].m_BoneIndex[vertices[vidx].m_BoneNum] = m_Bone[bone->mName.C_Str()].idx;

			vertices[vidx].m_BoneNum++;

			assert(vertices[vidx].m_BoneNum <= 4);
		}
	}


	// �e�N�X�`�������擾����
	if (mesh->mMaterialIndex >= 0)
	{
		// ���̃��b�V���̃}�e���A���C���f�b�N�X�l���擾����
		int	mtrlidx = mesh->mMaterialIndex;

		// ���̃��b�V���̃}�e���A�����擾����
		mtrl = m_materials[mtrlidx];

		// �V�[������}�e���A���f�[�^���擾����
		aiMaterial* material = scene->mMaterials[mtrlidx];

		// ���̃}�e���A���Ɋ֘A�Â����e�N�X�`�������o��
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);

		// ���̃��b�V���Ŏg�p���Ă���e�N�X�`����ۑ�
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	}

	// �ʂ̍\�������擾
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	return Mesh(vertices, indices, textures, mtrl);
}


XMFLOAT4X4 mtx[1000];
char* bonename[1000];
int chide[1000];
int bnum = 0;
int lngth[1000];
void ModelData::UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
{
	BONE* bone = &m_Bone[node->mName.C_Str()];
	auto aa = node->mName;
	
	//�}�g���N�X�̏�Z���Ԃɒ���
	//�i�e�{�[���Ƃ̑��Έʒu�������s�񁖃{�[���s�񁖃{�[���I�t�Z�b�g�s��j
	aiMatrix4x4 worldMatrix;
	// 
	/*
	TReal a1, a2, a3, a4;   // assimp �s��́A�s�D��
	TReal b1, b2, b3, b4;
	TReal c1, c2, c3, c4;
	TReal d1, d2, d3, d4;
	*/

	worldMatrix = matrix;
	worldMatrix *= bone->AnimationMatrix;

	bone->Matrix = worldMatrix;
	bone->Matrix *= bone->OffsetMatrix;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		UpdateBoneMatrix(node->mChildren[n], worldMatrix);
	}
}



//void ModelData::Update(
//	int m_Frame, int m_preFrame, float m_factor, int animecnt,
//	const XMFLOAT4X4& mtxworld,
//	unsigned int animfileno,
//	std::vector<AnimationDataAssimp*>& animationcontainer) {
//
//	// 0�Ԗڂ̃V�[�������o��
//	const aiScene* s = animationcontainer[animecnt]->GetScene();
//	
//	// �A�j���[�V�����f�[�^�������Ă��邩�H
//	if (s->HasAnimations())
//	{
//		//�A�j���[�V�����f�[�^����{�[���}�g���N�X�Z�o
//		aiAnimation* animation = s->mAnimations[0];
//
//		auto it = animation;
//		animationreset = false;
//		// �{�[���̐��������[�v
//		for (unsigned int c = 0; c < animation->mNumChannels; c++)
//		{
//			aiNodeAnim* nodeAnim = animation->mChannels[c];
//
//			// �{�[�����݃`�F�b�N(�A�j���[�V�����ɂ̂ݑ��݂���{�[�����������ꍇ�͖�������)
//			auto itr = m_Bone.find(nodeAnim->mNodeName.C_Str());
//
//	
//			if (itr != m_Bone.end()) {
//				BONE* bone = &m_Bone[nodeAnim->mNodeName.C_Str()];
//
//				int f1, f2;
//
//				f1 = m_Frame % nodeAnim->mNumRotationKeys;//�ȈՎ���   
//				aiQuaternion rot1 = nodeAnim->mRotationKeys[f1].mValue; // �N�I�[�^�j�I��
//
//				f1 = m_Frame % nodeAnim->mNumPositionKeys;//�ȈՎ���
//				aiVector3D pos1 = nodeAnim->mPositionKeys[f1].mValue;
//
//				f2 = m_preFrame % nodeAnim->mNumRotationKeys;//�ȈՎ���  
//				aiQuaternion rot2 = nodeAnim->mRotationKeys[f2].mValue; // �N�I�[�^�j�I��
//
//				f2 = m_preFrame % nodeAnim->mNumPositionKeys;//�ȈՎ���	
//				aiVector3D pos2 = nodeAnim->mPositionKeys[f2].mValue;
//
//				// ���
//				rot1.Interpolate(rot1, rot1, rot2, m_factor);
//				pos1.x = pos1.x * (1.0f - m_factor) + pos2.x * (m_factor);
//				pos1.y = pos1.y * (1.0f - m_factor) + pos2.y * (m_factor);
//				pos1.z = pos1.z * (1.0f - m_factor) + pos2.z * (m_factor);
//
//				bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot1, pos1);
//			}
//			
//		}
//	
//
//		//�ċA�I�Ƀ{�[���}�g���N�X���X�V
//		UpdateBoneMatrix(m_assimpscene.GetScene()->mRootNode, aiMatrix4x4());
//
//		// ���b�V����OBB�X�V
////		for (int i = 0; i < m_meshes.size(); i++)
////		{
////			m_meshes[i].UpdateOBB(m_Bone,mtxworld);
////		}
//
//	
//		if (m_Frame >= animation->mDuration)
//		{
//			animationreset = true;
//			m_Frame = 0;
//		}
//
//
//	}
//
//}

void ModelData::Update2(int animecnt, const XMFLOAT4X4& mtxworld, unsigned int animfileno, std::vector<AnimationDataAssimp*>& animationcontainer)
{// 0�Ԗڂ̃V�[�������o��
	const aiScene* s = animationcontainer[animecnt]->GetScene();

	// �A�j���[�V�����f�[�^�������Ă��邩�H
	if (s->HasAnimations())
	{
		//�A�j���[�V�����f�[�^����{�[���}�g���N�X�Z�o
		aiAnimation* animation = s->mAnimations[0];

		auto it = animation;
		animationreset = false;
		// �{�[���̐��������[�v
		for (unsigned int c = 0; c < animation->mNumChannels; c++)
		{
			aiNodeAnim* nodeAnim = animation->mChannels[c];

			// �{�[�����݃`�F�b�N(�A�j���[�V�����ɂ̂ݑ��݂���{�[�����������ꍇ�͖�������)
			auto itr = m_Bone.find(nodeAnim->mNodeName.C_Str());


			if (itr != m_Bone.end()) {
				BONE* bone = &m_Bone[nodeAnim->mNodeName.C_Str()];

				int f1, f2;

				f1 = m_Frame % nodeAnim->mNumRotationKeys;//�ȈՎ���   
				aiQuaternion rot1 = nodeAnim->mRotationKeys[f1].mValue; // �N�I�[�^�j�I��

				f1 = m_Frame % nodeAnim->mNumPositionKeys;//�ȈՎ���
				aiVector3D pos1 = nodeAnim->mPositionKeys[f1].mValue;

				f2 = m_preFrame % nodeAnim->mNumRotationKeys;//�ȈՎ���  
				aiQuaternion rot2 = nodeAnim->mRotationKeys[f2].mValue; // �N�I�[�^�j�I��

				f2 = m_preFrame % nodeAnim->mNumPositionKeys;//�ȈՎ���	
				aiVector3D pos2 = nodeAnim->mPositionKeys[f2].mValue;

				// ���
				rot1.Interpolate(rot1, rot1, rot2, m_factor);
				pos1.x = pos1.x * (1.0f - m_factor) + pos2.x * (m_factor);
				pos1.y = pos1.y * (1.0f - m_factor) + pos2.y * (m_factor);
				pos1.z = pos1.z * (1.0f - m_factor) + pos2.z * (m_factor);

				bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot1, pos1);
			}

		}


		//�ċA�I�Ƀ{�[���}�g���N�X���X�V
		UpdateBoneMatrix(m_assimpscene.GetScene()->mRootNode, aiMatrix4x4());

		// ���b�V����OBB�X�V
//		for (int i = 0; i < m_meshes.size(); i++)
//		{
//			m_meshes[i].UpdateOBB(m_Bone,mtxworld);
//		}


		if (m_Frame >= animation->mDuration)
		{
			animationreset = true;
			m_Frame = 0;
		}

		if (m_cnt % INTERPOLATENUM == 0) {
			m_preFrame = m_Frame;
			m_Frame++;
			m_factor = 0;
		}
		m_factor = 1.0f / (float)(m_cnt % INTERPOLATENUM + 1);

		m_cnt++;

	}

}


void ModelData::Exit()
{
	// �e�N�X�`�����\�[�X���������
	for (auto tex : m_texturesloaded)
	{
		if (tex.texture != nullptr) {
			tex.texture->Release();
		}
	}

	// ���b�V���̉��
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].Close();
	}
	// �萔�o�b�t�@���
	if (m_constantbufferbonematrix) {
		m_constantbufferbonematrix->Release();
		m_constantbufferbonematrix = nullptr;
	}
	// �V�[��(�A�j���[�V�����p��)�̉��
	for (auto s : m_sceneAnimContainer) {
		aiReleaseImport(s);
	}

	// assimp scene ���
	m_assimpscene.Exit();

}

// �m�[�h�̉��
void ModelData::processNode(aiNode* node, const aiScene* scene)
{
	// �m�[�h���̃��b�V���̐������[�v����
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		int meshindex = node->mMeshes[i];			// �m�[�h��i�Ԗڃ��b�V���̃C���f�b�N�X���擾
		aiMesh* mesh = scene->mMeshes[meshindex];	// �V�[�����烁�b�V���{�̂����o��

		m_meshes.push_back(this->processMesh(mesh, scene, meshindex));
	}

	// �q�m�[�h�ɂ��Ă����
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

void ModelData::UpdateBoneMatrixConstantBuffer() {

	ConstantBufferBoneMatrix cb;
	DirectX::XMFLOAT4X4 mtx;

	// �{�[���s���萔�o�b�t�@�ɃZ�b�g
	unsigned int num = 0;
	for (auto data : m_Bone) {
		// aiMatrix4X4��XMFLOAT4X4�֕ϊ�(�]�u����)
		mtx = DX11MtxaiToDX(data.second.Matrix);

		// �]�u����
		DX11MtxTranspose(mtx,mtx);

		cb.mBoneMatrix[num] = mtx;
		
		num++;
	}
	


	ID3D11DeviceContext* devicecontext;

	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	D3D11_MAPPED_SUBRESOURCE pData;

	// �{�[���s��i�[�p�萔�o�b�t�@�X�V
	HRESULT hr = devicecontext->Map(m_constantbufferbonematrix, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ConstantBufferBoneMatrix));
		devicecontext->Unmap(m_constantbufferbonematrix, 0);
	}

	

	// GPU�֒萔�o�b�t�@���Z�b�g
	devicecontext->VSSetConstantBuffers(5, 1, &m_constantbufferbonematrix);
}
