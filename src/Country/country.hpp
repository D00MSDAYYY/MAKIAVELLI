#pragma once
#include <memory>
#include <utility>

#include "cards_holder.hpp"
#include "game_network.hpp"

#include "resources.hpp"
#include "points.hpp"
#include "locations.hpp"
#include "activity_points.hpp"

enum class COUNTRY_COLOR : uint32_t
{
	RED,
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
	bool _is_busy{false};

	int _index{0}; // TODO! maybe in future delete this and only COUNTRY_COLOR and use it like index

	COUNTRY_COLOR _color{COUNTRY_COLOR::PINK};

	AC_POI::Activity_Points _activity_points;
	CARD::Cards_Holder _cards_holder;
	LOC::Locations _locations;
	POI::Points _points;
	RES::Resources _resources;

public:
	Country() {}
	Country(int index,
			RES::Resources r,
			POI::Points p,
			LOC::Locations l,
			CARD::Cards_Holder cards_holder,
			AC_POI::Activity_Points activity_p);
	~Country(){}
	bool busy(std::optional<bool> flag = std::nullopt);
	const int index() { return _index; }

	RES::Resources &resources();
	POI::Points &points();
	LOC::Locations &locations();
	CARD::Cards_Holder &cardsHolder();
	AC_POI::Activity_Points &activityPoints();

	void operator<<(olc::net::message<MSG_FROM>& msg);
	void operator>>(olc::net::message<MSG_FROM>& msg);

	void update();

	// void CHECK();
};
