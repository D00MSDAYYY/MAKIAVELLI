#include "card.hpp"

Card::Card(std::weak_ptr<Country> country, int duration)
	: _duration{duration}, _country{country}
{
	execute();
}

Card::~Card()
{
	unexecute();
}
