#include "card.hpp"

using CARD::Card;

Card::Card(std::weak_ptr<Country> country, int duration)
	: _duration{duration}, _country{country}
{
	execute();
}

Card::~Card()
{
	unexecute();
}

std::shared_ptr<Card> CARD::tag_invoke(boost::json::value_to_tag<std::shared_ptr<Card>>, boost::json::value const &jv)
{
	boost::json::object const &obj = jv.as_object();

	
	//TODO! do something with it
	//! in json : "type" : ["oil_down","mineral_up","army_restrict"]
	//! making lambda auto convertingToEnum = [&jv](){for(auto& enum_type : jv.at("type"))
	//! { if (enum_type == MINERAL_UP)}}
}

void CARD::tag_invoke(boost::json::value_from_tag, boost::json::value &jv, std::shared_ptr<Card> const &c)
{
	jv = c->convertToJSONValue();
}
