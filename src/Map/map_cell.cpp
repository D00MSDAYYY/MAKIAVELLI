#include "map_cell.hpp"

Locations *Map_Cell::mapCellOwner(std::optional<Locations *> owner)
{
	if(owner)
		_cell_owner = *owner;
	return _cell_owner;
}

Cell_Type Map_Cell::mapCellType(std::optional<Cell_Type> type)
{
	if(type)
		_cell_type = *type;
	return _cell_type;
}
