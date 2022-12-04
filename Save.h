#pragma once
#include <iostream>
#include <fstream>
#include <string>
#define debuglog(a) std::cout<<a<<std::endl;
using namespace std;


struct SaveData {
	std::string name;
	float fdata;
	int datavec[3];
	std::vector<std::vector<double> > dotto;
	XMFLOAT4X4 mtx[1000];
	int children[1000];
	char* bonename[1000];
	int lngth[1000];
};

// �����F�t�@�C���p�X
SaveData Loadvin(string _path)
{
	// �Ǎ��f�[�^�o�͗p�ϐ�:�K�v�ɉ����Ė߂�l���ŕԂ��Ă������肵��
	SaveData saveData;
	// �菇�P���Q�F����1�t�@�C���p�X ����2�t�@�C���I�[�v�����[�h
	ifstream fin(_path, ios::in | ios::binary);
	// �菇�R
	if (fin.fail()) { 
		SaveData null;
		return null;
	}
	// �菇�S
	// �����񕶎����Ǎ�
	int stringsize;
	fin.read((char*)&stringsize, sizeof(stringsize));
	// ������Ǎ�
	saveData.name.resize(stringsize);
	fin.read((char*)saveData.name.data(), stringsize);
	// �����_�����l�Ǎ�
	fin.read((char*)&saveData.fdata, sizeof(saveData.fdata));
	// �����l�z��Ǎ�
	fin.read((char*)&saveData.datavec[0], sizeof(saveData.datavec));
	
	int size = 512;

	saveData.dotto.resize(size);
	for (int i = 0; i < size; i++)
	{
		int psize;
		fin.read((char*)&psize, sizeof(psize));
		// ������Ǎ�
		saveData.dotto[i].resize(psize);
		for (int a = 0; a < psize; a++)
		{
			fin.read((char*)&saveData.dotto[i].at(a), sizeof(saveData.dotto[i].at(a)));
			//debuglog(saveData.dotto[i].at(a));

		}
	}

	//int bsize = 1000;
	//
	//for (int i = 0; i < bsize; i++)
	//{
	//	fin.read((char*)&saveData.mtx[i]._11, sizeof(&saveData.mtx[i]._11));
	//	fin.read((char*)&saveData.mtx[i]._12, sizeof(&saveData.mtx[i]._12));
	//	fin.read((char*)&saveData.mtx[i]._13, sizeof(&saveData.mtx[i]._13));
	//	fin.read((char*)&saveData.mtx[i]._14, sizeof(&saveData.mtx[i]._14));
	//	fin.read((char*)&saveData.mtx[i]._21, sizeof(&saveData.mtx[i]._21));
	//	fin.read((char*)&saveData.mtx[i]._22, sizeof(&saveData.mtx[i]._22));
	//	fin.read((char*)&saveData.mtx[i]._23, sizeof(&saveData.mtx[i]._23));
	//	fin.read((char*)&saveData.mtx[i]._24, sizeof(&saveData.mtx[i]._24));
	//	fin.read((char*)&saveData.mtx[i]._31, sizeof(&saveData.mtx[i]._31));
	//	fin.read((char*)&saveData.mtx[i]._32, sizeof(&saveData.mtx[i]._32));
	//	fin.read((char*)&saveData.mtx[i]._33, sizeof(&saveData.mtx[i]._33));
	//	fin.read((char*)&saveData.mtx[i]._34, sizeof(&saveData.mtx[i]._34));

	//	int nsize;
	//	//fin.read((char*)&nsize, sizeof(nsize));
	//	
	//	fin.read((char*)&saveData.lngth[i], sizeof(&saveData.lngth[i]));


	//	debuglog(saveData.lngth[i]);
	//	debuglog(&saveData.lngth[i]);
	//	debuglog(sizeof(&saveData.lngth[i]));
	//
	//	fin.read((char*)&saveData.bonename[i], saveData.lngth[i]);
	//
	//
	//fin.read((char*)&saveData.children[i], sizeof(saveData.children[i]));
	//}


	fin.close();

	return saveData;
}

// ����1�t�@�C���p�X�F�����Q�Z�[�u�f�[�^
void Savevin(string _path, SaveData _saveData)
{
	// �菇�P���Q�F����1�t�@�C���p�X ����2�t�@�C���I�[�v�����[�h
	ofstream fout(_path, ios::trunc | ios::binary);
	// �菇�R
	if (fout.fail()) { return; }
	// �菇�S
	fout.close();
	fout.open(_path, ios::app | ios::binary);
	// �菇�T
	// �����񕶎������o��
	int stringval = static_cast<int>(_saveData.name.size());
	fout.write((char*)&stringval, sizeof(stringval));
	// �����񏑏o��
	fout.write((char*)_saveData.name.c_str(), stringval);
	// �����_�����l���o��
	fout.write((char*)&_saveData.fdata, sizeof(_saveData.fdata));
	// �����l�z��Ǎ�
	fout.write((char*)&_saveData.datavec[0], sizeof(_saveData.datavec));
	
	// �����񕶎������o��
	int dottoval = static_cast<int>(_saveData.dotto.size());

	for (int i = 0;i < dottoval;i++)
	{
		fout.write((char*)&dottoval, sizeof(dottoval));
		
		for (int a = 0;a < dottoval;a++)
		{
			fout.write((char*)&_saveData.dotto[i].at(a), sizeof(_saveData.dotto[i].at(a)));
		
		}
	}

	//// �����񕶎������o��
	//int bval = 1000;
	////fout.write((char*)&bval, sizeof(bval));

	//for (int b = 0; b < 1000; b++)
	//{
	//	fout.write((char*)&_saveData.mtx[b]._11, sizeof(_saveData.mtx[b]._11));
	//	fout.write((char*)&_saveData.mtx[b]._12, sizeof(_saveData.mtx[b]._12));
	//	fout.write((char*)&_saveData.mtx[b]._13, sizeof(_saveData.mtx[b]._13));
	//	fout.write((char*)&_saveData.mtx[b]._14, sizeof(_saveData.mtx[b]._14));
	//	fout.write((char*)&_saveData.mtx[b]._21, sizeof(_saveData.mtx[b]._21));
	//	fout.write((char*)&_saveData.mtx[b]._22, sizeof(_saveData.mtx[b]._22));
	//	fout.write((char*)&_saveData.mtx[b]._23, sizeof(_saveData.mtx[b]._23));
	//	fout.write((char*)&_saveData.mtx[b]._24, sizeof(_saveData.mtx[b]._24));
	//	fout.write((char*)&_saveData.mtx[b]._31, sizeof(_saveData.mtx[b]._31));
	//	fout.write((char*)&_saveData.mtx[b]._32, sizeof(_saveData.mtx[b]._32));
	//	fout.write((char*)&_saveData.mtx[b]._33, sizeof(_saveData.mtx[b]._33));
	//	fout.write((char*)&_saveData.mtx[b]._34, sizeof(_saveData.mtx[b]._34));
	//	
	//	fout.write((char*)&_saveData.lngth[b], sizeof(_saveData.lngth[b]));
	//	
	//	fout.write(_saveData.bonename[b], _saveData.lngth[b]);
	//	
	//	fout.write((char*)&_saveData.children[b], sizeof(_saveData.children));
	//
	//}

	fout.close();
}
