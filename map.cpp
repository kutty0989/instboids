//#include"map.h"
//#include<iostream>
//#include<sstream>
//#include<fstream>
//using namespace std;
//
//void MapChip::MapLoad(string _path)
//{
//
//	ifstream file(_path);
//
//	if (file.fail())
//	{
//		throw;
//	}
//
//	string str;
//
//	while (getline(file, str))
//	{
//		stringstream ss(str);
//		string buf;
//
//		vector<int> vs;
//		int n = 0;
//
//		while (getline(ss, buf, ','))
//		{
//			if (buf == "ret") {
//				break;
//			}
//
//			stringstream tmp(buf);
//			int tmp_i;
//			tmp >> tmp_i;
//			vs.push_back(tmp_i);
//			n++;
//		}
//		if (buf == "ret")
//		{
//			break;
//		}
//		mapSizeX = n > mapSizeY ? n : mapSizeX;
//		mapIntData.push_back(vs);
//		mapSizeY++;
//
//	}
//
//	MapMake();
//}
//
//
//void MapChip::MapMake()
//{
//	int size = 66;
//
//	for (int m = 0; m < mapSizeY;m++)
//	{
//		for (int n = 0; n < mapSizeX;n++)
//		{
//			if (mapIntData.at(m).at(n) == 0) {
//				continue;
//			}
//
//
//
//		}
//	}
//}