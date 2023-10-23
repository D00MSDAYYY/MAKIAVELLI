#pragma once

#include <memory>

namespace LOC
{
	class Locations;
}
using LOC::Locations;

enum class Cell_Type
{
	OCEAN,

	CAPITAL,
	COUNTRY_AREA,

	OIL_LOCATION,
	MINERAL_LOCATION,
	FARM_LOCATION,
	INDUSTRY_LOCATION
};

class Map_Cell
{
private:
	std::weak_ptr<Locations> _cell_owner{};
	Cell_Type _cell_type{Cell_Type::OCEAN};

public:
	Map_Cell(){};

	int color{};
	std::weak_ptr<Locations> mapCellOwner(std::weak_ptr<Locations> owner = {});
	Cell_Type mapCellType(Cell_Type type = Cell_Type::OCEAN);

};
