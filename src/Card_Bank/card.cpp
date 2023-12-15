#include "card.hpp"

#include "country.hpp"

using CARD::Card;

CARD::Card::Card(int         index,
                 SCOPE       scope,
                 TARGET      target,
                 EFFECT      effect,
                 std::string description,
                 int         probability,
                 int         duration,
                 int         num_or_coef)
    : _index{index},
      _duration{duration},
      _probability{probability},
      _scope{scope},
      _target{target},
      _effect{effect},
      _num_or_coef{num_or_coef},
      _description{std::move(description)}
{
}

Card::Card(const Card& card, Country* country)
    : Card{card}
{
    _country = country;
    execute();
}

CARD::Card::~Card()
{
    if(_country) unexecute();
}

Card
CARD::tag_invoke(boost::json::value_to_tag<Card>, const boost::json::value& jv)
{
    using namespace boost::json;

    const boost::json::object& obj = jv.as_object();
    return Card{value_to<int>(obj.at("index")),
                toSCOPE(value_to<std::string>(obj.at("SCOPE"))),
                toTARGET(value_to<std::string>(obj.at("TARGET"))),
                toEFFECT(value_to<std::string>(obj.at("EFFECT"))),
                value_to<std::string>(obj.at("descriprton")),
                value_to<int>(obj.at("probability")),
                value_to<int>(obj.at("duration")),
                value_to<int>(obj.at("num_or_coef"))};
}

SCOPE
CARD::toSCOPE(std::string str)
{
    if(str == "ARMY") return SCOPE::ARMY;
    if(str == "SCIENCE") return SCOPE::SCIENCE;
    if(str == "OIL") return SCOPE::OIL;
    if(str == "MINERAL") return SCOPE::MINERAL;
    if(str == "FARM") return SCOPE::FARM;
    if(str == "INDUSTRY") return SCOPE::INDUSTRY;
    if(str == "ALL") return SCOPE::ALL;
    return SCOPE::ALL;  // TODO! what if string is ill?
}

TARGET
CARD::toTARGET(std::string str)
{
    if(str == "LOCATIONS") return TARGET::LOCATIONS;
    if(str == "POINTS") return TARGET::POINTS;
    if(str == "RESOURCES") return TARGET::RESOURCES;
    return TARGET::RESOURCES;
}

EFFECT
CARD::toEFFECT(std::string str)
{
    if(str == "NUMBER") return EFFECT::EFFECT;
    if(str == "COEFFICIENT") return EFFECT::COEFFICIENT;
    return EFFECT::EFFECT;
}
