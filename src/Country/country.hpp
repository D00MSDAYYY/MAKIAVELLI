#pragma once
#include <memory>
#include <utility>

#include "cards_holder.hpp"
#include "activity_points.hpp"
#include "game_network.hpp"

using AC_POI::Activity_Points;
using CARD::Cards_Holder;
using LOC::Locations;
using POI::Points;
using RES::Resources;

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

	int _index{0}; //TODO! maybe in future delete this and only COUNTRY_COLOR and use it like index

	COUNTRY_COLOR _color{COUNTRY_COLOR::PINK};

	std::shared_ptr<Resources> _resources;
	std::shared_ptr<Points> _points;
	std::shared_ptr<Locations> _locations;
	std::shared_ptr<Cards_Holder> _cards_holder;
	std::shared_ptr<Activity_Points> _activity_points;

public:
	Country() {}
	Country(int index,
			std::shared_ptr<Resources> r,
			std::shared_ptr<Points> p,
			std::shared_ptr<Locations> l,
			std::shared_ptr<Cards_Holder> cards_holder,
			std::shared_ptr<Activity_Points> activity_p);


	bool busy(int flag = -1);
	const int index() const { return _index; }

	std::shared_ptr<Resources> resources();
	std::shared_ptr<Points> points();
	std::shared_ptr<Locations> locations();
	std::shared_ptr<Cards_Holder> cardsHolder();
	std::shared_ptr<Activity_Points> activityPoints();

	void operator<<(olc::net::message<MSG_FROM> msg);
	void operator>>(olc::net::message<MSG_FROM> msg);

	void update();
};
