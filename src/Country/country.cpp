#include "country.hpp"

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

std::shared_ptr<Cards> Country::cards()
{
	return _cards;
}

std::shared_ptr<Activity_Points> Country::activityPoints()
{
	return _activity_points;
}

std::shared_ptr<Points> Country::points()
{
	return _points;
}

std::shared_ptr<Resources> Country::resources()
{
	return _resources;
}

std::shared_ptr<Locations> Country::locations()
{
	return _locations;
}

void Country::operator<<(olc::net::message<MSG_FROM> msg)
{
	*_resources << msg;
	*_points << msg;
	*_locations << msg;
	*_cards << msg;
	*_activity_points << msg;
	msg >> _index;
	msg >> _color; //TODO! check the order of insertion/extraction
}

void Country::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_index);
	msg << uint32_t(_color);
	*_resources >> msg;
	*_points >> msg;
	*_locations >> msg;
	*_cards >> msg;
	*_activity_points >> msg;
}

void Country::update()
{
	_resources->updateRes();
}
