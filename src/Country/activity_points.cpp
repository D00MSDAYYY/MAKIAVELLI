#include "activity_points.hpp"

using ACPOI::Activity_Points;

ACPOI::Activity_Points::Activity_Points(int max_p)
	: _current_points{max_p}, _max_points{max_p}
{
}

Data_Activity_Points ACPOI::Activity_Points::convertToData()
{
	return Data_Activity_Points{uint8_t{_current_points},
								uint8_t{_max_points}};
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
