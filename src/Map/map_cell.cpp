#include "map_cell.hpp"

std::weak_ptr<Locations> Map_Cell::mapCellOwner(std::weak_ptr<Locations> owner)
{
	if (owner.expired())
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
