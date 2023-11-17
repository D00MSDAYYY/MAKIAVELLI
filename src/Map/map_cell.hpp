#pragma once

#include <memory>
#include <optional>

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

	OIL,
	MINERAL,
	FARM,
	INDUSTRY
};

class Map_Cell
{
private:
	Locations *_cell_owner{};
	Cell_Type _cell_type{Cell_Type::OCEAN};

public:
	Map_Cell(){};
	Locations *mapCellOwner(std::optional<Locations *> owner = std::nullopt);
	Cell_Type mapCellType(std::optional<Cell_Type> type = std::nullopt);
};
