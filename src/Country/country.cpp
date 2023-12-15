#include "country.hpp"

using AC_POI::Activity_Points;
using CARD::Cards_Holder;
using POI::Points;
using RES::Resources;

Country::Country(int             index,
                 Resources       r,
                 Points          p,
                 Locations       l,
                 Cards_Holder    cards_holder,
                 Activity_Points activity_p)
    : _index{index},
      _resources{std::move(r)},
      _points{std::move(p)},
      _locations{std::move(l)},
      _cards_holder{std::move(cards_holder)},
      _activity_points{std::move(activity_p)}
{
    // CHECK();
}

bool
Country::busy(std::optional<bool> flag)
{
    if(flag) _is_busy = *flag;
    return _is_busy;
}

Cards_Holder&
Country::cardsHolder()
{
    _cards_holder.setDependices(this);
    return _cards_holder;
}

Activity_Points&
Country::activityPoints()
{
    return _activity_points;
}

Points&
Country::points()
{
    return _points.setCountry(this);
}

Resources&
Country::resources()
{
    return _resources.setCountry(this);
}

Locations&
Country::locations()
{
    return _locations.setCountry(this);
}

void
Country::operator<<(olc::net::message<MSG_FROM>& msg)
{
    _resources << msg;
    _points << msg;
    _locations << msg;
    _cards_holder << msg;
    _activity_points << msg;
    msg >> _color;  // TODO! check the order of insertion/extraction
    msg >> _index;
}

void
Country::operator>>(olc::net::message<MSG_FROM>& msg)
{
    msg << uint32_t(_index);
    msg << uint32_t(_color);
    _activity_points >> msg;
    _cards_holder >> msg;
    _locations >> msg;
    _points >> msg;
    _resources >> msg;
}

void
Country::update()
{
    if(_activity_points.currentPoints() > 0) _resources.setCountry(this).update();
}

// void Country::CHECK()
// {
// 	std::cerr << "-------------------" << std::endl;
// 	std::cerr << "CHECK" << std::endl;
// 	std::cerr << "country " << _index<< " address " << this << std::endl;
// 	std::cerr << "locations address " << &_locations << std::endl;
// 	std::cerr << "resources address " << &_resources << std::endl;
// 	std::cerr << "points address " << &_points << std::endl;
// 	std::cerr << "cards holder address " << &_cards_holder << std::endl;
// 	std::cerr << "-------------------" << std::endl;
// }
