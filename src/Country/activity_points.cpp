#include "activity_points.hpp"

using AC_POI::Activity_Points;

AC_POI::Activity_Points::Activity_Points(int max_p)
	: _current_points{max_p}, _max_points{max_p}
{
}

int Activity_Points::currentPoints(int points)
{
	if (points == 0)
		return _current_points;
	_current_points += points;
	if (_current_points.load() < 0)
		_current_points = 0;
	return 1;
}

int Activity_Points::maxPoints(int points)
{
	if (points == 0)
		return _max_points;
	_max_points += points;
	if (_max_points < 0)
		_max_points = 0;
	return 1;
}

void AC_POI::Activity_Points::operator<<(olc::net::message<MSG_FROM> msg)
{
	uint32_t mp{};
	uint32_t cp{};
	msg >> mp >> cp;
	_current_points = cp;
	_max_points = mp;
}

void AC_POI::Activity_Points::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_current_points) << uint32_t(_max_points);
}
