#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<DirectXMath.h>
#define debuglog(a) std::cout<<a<<std::endl;
using namespace std;


class Save
{
public:


	struct SaveData {
		std::string name;
		float fdata;
		int datavec[3];
		std::vector<std::vector<double> > dotto;
		DirectX::XMFLOAT4X4 mtx[1000];
		int children[1000];
		char* bonename[1000];
		int lngth[1000];
	};
	
	struct SaveData2 {
		float data1;
		float data2;
		float data3;
		float data4;
		float data5;
		float data6;
		float data7;
		float data8;
		float data9;
		float data10;
		float data11;
		float data12;
		float data13;
		float data14;
		float data15;
		float data16;
		float data17;
		float data18;
		float data19;
		float data20;
		float data21;
		float data22;
		float data23;

		int data50;
	};


	SaveData save1;
	SaveData2 save2;

	// 引数：ファイルパス
	SaveData Loadvin(string _path)
	{
		// 読込データ出力用変数:必要に応じて戻り値等で返してあげたりして
		SaveData saveData;
		// 手順１＆２：引数1ファイルパス 引数2ファイルオープンモード
		ifstream fin(_path, ios::in | ios::binary);
		// 手順３
		if (fin.fail()) {
			SaveData null;
			return null;
		}
		// 手順４
		// 文字列文字数読込
		int stringsize;
		fin.read((char*)&stringsize, sizeof(stringsize));
		// 文字列読込
		saveData.name.resize(stringsize);
		fin.read((char*)saveData.name.data(), stringsize);
		// 浮動点小数値読込
		fin.read((char*)&saveData.fdata, sizeof(saveData.fdata));
		// 整数値配列読込
		fin.read((char*)&saveData.datavec[0], sizeof(saveData.datavec));

		int size = 512;

		saveData.dotto.resize(size);
		for (int i = 0; i < size; i++)
		{
			int psize;
			fin.read((char*)&psize, sizeof(psize));
			// 文字列読込
			saveData.dotto[i].resize(psize);
			for (int a = 0; a < psize; a++)
			{
				fin.read((char*)&saveData.dotto[i].at(a), sizeof(saveData.dotto[i].at(a)));
				//debuglog(saveData.dotto[i].at(a));

			}
		}


		fin.close();

		return saveData;
	}



	// 引数1ファイルパス：引数２セーブデータ
	void Savevin(string _path, SaveData _saveData)
	{
		// 手順１＆２：引数1ファイルパス 引数2ファイルオープンモード
		ofstream fout(_path, ios::trunc | ios::binary);
		// 手順３
		if (fout.fail()) { return; }
		// 手順４
		fout.close();
		fout.open(_path, ios::app | ios::binary);
		// 手順５
		// 文字列文字数書出し
		int stringval = static_cast<int>(_saveData.name.size());
		fout.write((char*)&stringval, sizeof(stringval));
		// 文字列書出し
		fout.write((char*)_saveData.name.c_str(), stringval);
		// 浮動点小数値書出し
		fout.write((char*)&_saveData.fdata, sizeof(_saveData.fdata));
		// 整数値配列読込
		fout.write((char*)&_saveData.datavec[0], sizeof(_saveData.datavec));

		// 文字列文字数書出し
		int dottoval = static_cast<int>(_saveData.dotto.size());

		for (int i = 0;i < dottoval;i++)
		{
			fout.write((char*)&dottoval, sizeof(dottoval));

			for (int a = 0;a < dottoval;a++)
			{
				fout.write((char*)&_saveData.dotto[i].at(a), sizeof(_saveData.dotto[i].at(a)));

			}
		}


		fout.close();
	}

	// 引数1ファイルパス：引数２セーブデータ
	void Savevin2(string _path, SaveData2 _saveData)
	{
		// 手順１＆２：引数1ファイルパス 引数2ファイルオープンモード
		ofstream fout(_path, ios::trunc | ios::binary);
		// 手順３
		if (fout.fail()) { return; }
		// 手順４
		fout.close();
		fout.open(_path, ios::app | ios::binary);
		// 手順５
		// 浮動点小数値書出し
		fout.write((char*)&_saveData.data1, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data2, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data3, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data4, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data5, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data6, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data7, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data8, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data9, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data10, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data11, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data12, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data13, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data14, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data15, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data16, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data17, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data18, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data19, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data20, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data21, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data22, sizeof(_saveData.data1));
		fout.write((char*)&_saveData.data23, sizeof(_saveData.data1));
		// 整数値配列読込
		fout.write((char*)&_saveData.data50, sizeof(_saveData.data50));


		fout.close();
	}


	// 引数：ファイルパス
	SaveData2 Loadvin2(string _path)
	{
		// 読込データ出力用変数:必要に応じて戻り値等で返してあげたりして
		SaveData2 saveData2;
		// 手順１＆２：引数1ファイルパス 引数2ファイルオープンモード
		ifstream fin(_path, ios::in | ios::binary);
		// 手順３
		if (fin.fail()) {
			SaveData2 nulla = {};
			return nulla;
		}
		fin.read((char*)&saveData2.data1, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data2, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data3, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data4, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data5, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data6, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data7, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data8, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data9, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data10, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data11, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data12, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data13, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data14, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data15, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data16, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data17, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data18, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data19, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data20, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data21, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data22, sizeof(saveData2.data1));
		fin.read((char*)&saveData2.data23, sizeof(saveData2.data1));

		// 整数値配列読込
		fin.read((char*)&saveData2.data50, sizeof(saveData2.data50));



		fin.close();

		return saveData2;
	}


	static Save* GetInstance()
	{
		static Save instance;
		return &instance;
	}
};
