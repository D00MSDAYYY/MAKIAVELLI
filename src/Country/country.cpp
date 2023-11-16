#include "country.hpp"

using AC_POI::Activity_Points;
using CARD::Cards_Holder;
using POI::Points;
using RES::Resources;

bool Country::busy(int flag)
{
	if (flag == -1)
		return is_busy;
	if (flag == false)
		is_busy = false;
	if (flag == true)
		is_busy = true;
	return is_busy;
}
Cards_Holder &Country::cardsHolder()
{
	_cards_holder.setDependices(this);
	return _cards_holder;
}

Activity_Points &Country::activityPoints()
{
	return _activity_points;
}

Points &Country::points()
{
	_points.setDependices(this);
	return _points;
}

Resources &Country::resources()
{
	_resources.setDependices(this);
	return _resources;
}

Locations &Country::locations()
{
	_locations.setDependices(this);
	return _locations;
}

void Country::operator<<(olc::net::message<MSG_FROM> msg)
{
	_resources << msg;
	_points << msg;
	_locations << msg;
	_cards_holder << msg;
	_activity_points << msg;
	msg >> _index;
	msg >> _color; // TODO! check the order of insertion/extraction
}

void Country::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_index);
	msg << uint32_t(_color);
	_resources >> msg;
	_points >> msg;
	_locations >> msg;
	_cards_holder >> msg;
	_activity_points >> msg;
}

void Country::update()
{
	std::cerr << "in country update " << std::endl;
	CHECK();
	_resources.setDependices(this);
	_resources.update();
}

void Country::CHECK()
{
	std::cerr << "-------------------" << std::endl;
	std::cerr << "CHECK" << std::endl;
	std::cerr << "country " << _index<< " address " << this << std::endl;
	std::cerr << "locations address " << &_locations << std::endl;
	std::cerr << "resources address " << &_resources << std::endl;
	std::cerr << "points address " << &_points << std::endl;
	std::cerr << "cards holder address " << &_cards_holder << std::endl;
	std::cerr << "-------------------" << std::endl;
}

Country::Country(int index,
				 Resources r,
				 Points p,
				 Locations l,
				 Cards_Holder cards_holder,
				 Activity_Points activity_p)
	: _index{index},
	  _resources{std::move(r)},
	  _points{std::move(p)},
	  _locations{std::move(l)},
	  _cards_holder{std::move(cards_holder)},
	  _activity_points{std::move(activity_p)}
{
	std::cerr << "in county constr" << std::endl;
	CHECK();
}
