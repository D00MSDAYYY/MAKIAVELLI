#pragma once

#include <vector>
#include "map_cell.hpp"

namespace LOC
{
	class Locations;
}
using LOC::Locations;

class Map
{
private:
	std::vector<std::vector<Map_Cell>> _map;

	int rollX(int x, int d_x);
	int rollY(int y, int d_y);
public:
	Map() {}
	Map(const int numplayers);
	~Map(){};

	bool find(Cell_Type celltype, std::pair<int, int> coord1, std::pair<int, int> coord2);
	bool find(Cell_Type celltype, std::pair<int, int> coord);
	bool isSurroundedBy(Cell_Type celltype, std::pair<int, int> coord);

	int xSize();
	int ySize();

	Map_Cell& cell(std::pair<int, int> coord);

};

