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
	bool is_busy{false};

	int _index{0}; // TODO! maybe in future delete this and only COUNTRY_COLOR and use it like index

	COUNTRY_COLOR _color{COUNTRY_COLOR::PINK};

	std::unique_ptr<AC_POI::Activity_Points> _activity_points;
	std::unique_ptr<RES::Resources> _resources;
	std::unique_ptr<CARD::Cards_Holder> _cards_holder;

	std::unique_ptr<LOC::Locations> _locations;
	std::unique_ptr<POI::Points> _points;

public:
	Country() {}
	Country(int index,
			std::unique_ptr<RES::Resources> r,
			std::unique_ptr<POI::Points> p,
			std::unique_ptr<LOC::Locations> l,
			std::unique_ptr<CARD::Cards_Holder> cards_holder,
			std::unique_ptr<AC_POI::Activity_Points> activity_p);
	bool busy(int flag = -1);
	const int index() const { return _index; }

	const std::unique_ptr<RES::Resources> &resources();
	const std::unique_ptr<POI::Points> &points();
	const std::unique_ptr<LOC::Locations> &locations();
	const std::unique_ptr<CARD::Cards_Holder> &cardsHolder();
	const std::unique_ptr<AC_POI::Activity_Points> &activityPoints();

	void operator<<(olc::net::message<MSG_FROM> msg);
	void operator>>(olc::net::message<MSG_FROM> msg);

	void update();
};
