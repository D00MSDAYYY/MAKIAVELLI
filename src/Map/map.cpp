#include <random>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#include <iostream>

#include "map.hpp"

Map::Map(int numplayers)
{
	switch (numplayers)
	{
	case 3:
	{
		_map.resize(50);
		for (auto &column : _map)
			column.resize(50);
		break;
	}
	case 4:
	{
		_map.resize(40);
		for (auto &column : _map)
			column.resize(40);
		break;
	}
	case 5:
	{
		_map.resize(40);
		for (auto &column : _map)
			column.resize(40);
		break;
	}
	case 6:
	{
		_map.resize(45);
		for (auto &column : _map)
			column.resize(45);
		break;
	}
	case 7:
	{
		_map.resize(50);
		for (auto &column : _map)
			column.resize(50);
		break;
	}
	case 8:
	{
		_map.resize(55);
		for (auto &column : _map)
			column.resize(55);
		break;
	}

	default:
		_map.resize(100);
		for (auto &column : _map)
			column.resize(100);
		break;
	}
}

bool Map::find(Cell_Type celltype, std::pair<int, int> coord)
{
	return find(celltype, coord, coord);
}

bool Map::find(Cell_Type celltype, std::pair<int, int> coord1, std::pair<int, int> coord2)
{
	bool is_finded{false};

	for (int i{0};
		 &cell({coord1.first + i, coord1.second}) != &cell({coord2.first + 2, coord1.second});
		 ++i)
	{
		for (int j{0};
			 &cell({coord1.first + i, coord1.second + j}) != &cell({coord1.first + i, coord2.second + 2});
			 ++j)
		{
			if (cell({coord1.first + i, coord1.second + j}).mapCellType() == celltype)
			{
				is_finded = true;
				break;
			}
		}
	}

	return is_finded;
}

bool Map::isSurroundedBy(Cell_Type celltype, std::pair<int, int> coord)
{

	int count{0};

	for (int i{0};
		 &cell({coord.first + i - 1, coord.second}) != &cell({coord.first + 2, coord.second});
		 ++i)
	{
		for (int j{0};
			 &cell({coord.first + i - 1, coord.second + j - 1}) != &cell({coord.first + i - 1, coord.second + 2});
			 ++j)
		{
			if (cell({coord.first + i - 1, coord.second + j - 1}).mapCellType() == Cell_Type::COUNTRY_AREA ||
				cell({coord.first + i - 1, coord.second + j - 1}).mapCellType() == Cell_Type::CAPITAL)
				++count;
		}
	}

	if (cell({coord.first, coord.second}).mapCellType() == Cell_Type::CAPITAL)
		--count;

	return (count > 7) ? true : false;
}

int Map::rollX(int x, int d_x)
{
	int size = _map.size();
	return ((x + d_x) % size + size) % size;
}

int Map::rollY(int y, int d_y)
{
	int size = _map[0].size();
	return ((y + d_y) % size + size) % size;
}

Map_Cell &Map::cell(std::pair<int, int> coord)
{
	return _map[rollX(coord.first, 0)][rollY(coord.second, 0)];
}

int Map::xSize()
{
	return _map.size();
}

int Map::ySize()
{
	return _map[0].size();
}

