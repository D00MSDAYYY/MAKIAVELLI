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
	return 42;
}
const std::unique_ptr<Cards_Holder>& Country::cardsHolder()
{
	return _cards_holder;
}

const std::unique_ptr<Activity_Points>& Country::activityPoints()
{
	return _activity_points;
}

const std::unique_ptr<Points>& Country::points()
{
	return _points;
}

const std::unique_ptr<Resources>& Country::resources()
{
	return _resources;
}

const std::unique_ptr<Locations>& Country::locations()
{
	return _locations;
}

void Country::operator<<(olc::net::message<MSG_FROM> msg)
{
	*_resources << msg;
	*_points << msg;
	*_locations << msg;
	*_cards_holder << msg;
	*_activity_points << msg;
	msg >> _index;
	msg >> _color; // TODO! check the order of insertion/extraction
}

void Country::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_index);
	msg << uint32_t(_color);
	*_resources >> msg;
	*_points >> msg;
	*_locations >> msg;
	*_cards_holder >> msg;
	*_activity_points >> msg;
}

void Country::update()
{
	_resources->update();
}

Country::Country(int index,
				 std::unique_ptr<Resources> r,
				 std::unique_ptr<Points> p,
				 std::unique_ptr<Locations> l,
				 std::unique_ptr<Cards_Holder> cards_holder,
				 std::unique_ptr<Activity_Points> activity_p)
	: _index{index},
	  _resources{std::move(r)},
	  _points{std::move(p)},
	  _locations{std::move(l)},
	  _cards_holder{std::move(cards_holder)},
	  _activity_points{std::move(activity_p)}
{

	_locations->setDependices(std::unique_ptr<Country>(this));
	_resources->setDependices(std::unique_ptr<Country>(this));
	_points->setDependices(std::unique_ptr<Country>(this));
	_cards_holder->setDependices(std::shared_ptr<Country>(this));
}
