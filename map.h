#pragma once
#include<string>
#include<vector>

class MapChip
{
public:
	void MapLoad(std::string _path);
	int mapSizeX = 0;
	int mapSizeY = 0;

	std::vector<std::vector<int>> mapIntData;
	void MapMake();


};