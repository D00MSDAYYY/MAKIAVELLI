#include "activity_points.hpp"

using AC_POI::Activity_Points;

AC_POI::Activity_Points::Activity_Points(const Activity_Points &acpoi)
{
	_current_points = acpoi._current_points.load();
	_max_points = acpoi._max_points.load();
}

const Activity_Points &AC_POI::Activity_Points::operator=(const Activity_Points &acpoi)
{
	_current_points = acpoi._current_points.load();
	_max_points = acpoi._max_points.load();
	return *this;
}

int Activity_Points::currentPoints(std::optional<int> points)
{
	if (points)
	{
		_current_points += *points;
		if (_current_points < 0)
			_current_points = 0;
	}
	return _current_points;
}

int Activity_Points::maxPoints(std::optional<int> points)
{
	if (points)
	{
		_max_points += *points;
		if (_max_points < 0)
			_max_points = 0;
	}
	return _max_points;
}

void AC_POI::Activity_Points::operator<<(olc::net::message<MSG_FROM>& msg)
{
	uint32_t mp{};
	uint32_t cp{};
	msg >> mp;
	msg >> cp;
	_current_points = cp;
	_max_points = mp;
}

void AC_POI::Activity_Points::operator>>(olc::net::message<MSG_FROM>& msg)
{
	msg << uint32_t(_current_points);
	msg << uint32_t(_max_points);
}
