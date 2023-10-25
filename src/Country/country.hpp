#pragma once
#include <memory>
#include <utility>

#include "cards.hpp"
#include "activity_points.hpp"
#include "game_network.hpp"

using AC_POI::Activity_Points;
using CAR::Cards;
using LOC::Locations;
using POI::Points;
using RES::Resources;

// struct Data_Country
// {
// 	uint8_t _data_index;
// 	Data_Resources _data_resources;
// 	Data_Points _data_points;
// 	Data_Locations _data_locations;
// 	Data_Cards _data_cards;
// 	Data_Activity_Points _data_activity_points;
// };

enum class COUNTRY_COLOR : uint8_t
{
	GREEN,
	YELLOW,
	GRAY,
	MAGENTA,
	CYAN,
	PINK
	// ...
};
class Country
{
private:
	bool is_busy{false};

	int _index{0};

	COUNTRY_COLOR color; // TODO ! maybe change

	std::shared_ptr<Resources> _resources;
	std::shared_ptr<Points> _points;
	std::shared_ptr<Locations> _locations;
	std::shared_ptr<Cards> _cards;
	std::shared_ptr<Activity_Points> _activity_points;

public:
	Country() {}
	Country(int ndx,
			std::shared_ptr<Resources> r,
			std::shared_ptr<Points> p,
			std::shared_ptr<Locations> l,
			std::shared_ptr<Cards> cards,
			std::shared_ptr<Activity_Points> activity_p)
		: _index{ndx},
		  _resources{r},
		  _points{p},
		  _locations{l},
		  _cards{cards},
		  _activity_points{activity_p} {}


	bool busy(int flag = -1);
	const int index() const { return _index; }

	std::shared_ptr<Resources> resources();
	std::shared_ptr<Points> points();
	std::shared_ptr<Locations> locations();
	std::shared_ptr<Cards> cards();
	std::shared_ptr<Activity_Points> activityPoints();

	void operator<<(olc::net::message<MSG_FROM> msg);
	void operator>>(olc::net::message<MSG_FROM> msg);

	void update(); //! calls updateOilRes() ... then activity_points== 0
};
