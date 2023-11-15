#include "map_cell.hpp"

Locations *Map_Cell::mapCellOwner(Locations * const owner)
{
	if (owner == nullptr)
		return _cell_owner;
	else
	{
		_cell_owner = owner;
		return _cell_owner;
	}
}

Cell_Type Map_Cell::mapCellType(Cell_Type type)
{
	if (type == Cell_Type::OCEAN)
		return _cell_type;
	else
	{
		_cell_type = type;
		return Cell_Type::OCEAN;
	}
}
