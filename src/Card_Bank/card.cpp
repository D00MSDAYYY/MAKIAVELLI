#include "card.hpp"
#include "country.hpp"

using CARD::Card;

void CARD::Card::execute()
{
	if (_target == TARGET::LOCATIONS)
	{
		if (_scope == SCOPE::ARMY)
			; //!-----------
		if (_scope == SCOPE::SCIENCE)
			; //!-----------
		if (_scope == SCOPE::OIL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->locations()->oilCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
		if (_scope == SCOPE::MINERAL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->locations()->mineralCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
		if (_scope == SCOPE::FARM)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->locations()->farmCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
		if (_scope == SCOPE::INDUSTRY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->locations()->industryCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
	}

	if (_target == TARGET::POINTS)
	{
		if (_scope == SCOPE::ARMY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->armyCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country->points()->armyNum(_num_or_coef);
		}
		if (_scope == SCOPE::SCIENCE)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->scienceCoef(_num_or_coef); //TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()
 
			if (_effect == EFFECT::NUMBER)
				_country->points()->scienceNum(_num_or_coef);
		}
		if (_scope == SCOPE::OIL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->oilCoef(_num_or_coef); // TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()

			if (_effect == EFFECT::NUMBER)
				_country->points()->oilNum(_num_or_coef);
		}
		if (_scope == SCOPE::MINERAL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->mineralCoef(_num_or_coef); // TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()

			if (_effect == EFFECT::NUMBER)
				_country->points()->mineralNum(_num_or_coef); // TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()
		}
		if (_scope == SCOPE::FARM)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->farmCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country->points()->farmNum(_num_or_coef);
		}
		if (_scope == SCOPE::INDUSTRY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->industryCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country->points()->industryNum(_num_or_coef);
		}
	}

	if (_target == TARGET::RESOURCES)
	{
		if (_scope == SCOPE::ARMY)
			;
		if (_scope == SCOPE::SCIENCE)
			;
		if (_scope == SCOPE::OIL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->resources()->oilCoef(_num_or_coef); //TODO! add option to increase/decrease capital of resources in ... times

			if (_effect == EFFECT::NUMBER)
				_country->resources()->oilNum(_num_or_coef);
		}
		if (_scope == SCOPE::MINERAL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->resources()->mineralCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country->resources()->mineralNum(_num_or_coef);
		}
		if (_scope == SCOPE::FARM)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->resources()->farmCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country->resources()->farmNum(_num_or_coef);
		}
		if (_scope == SCOPE::INDUSTRY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country->points()->industryCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country->points()->industryNum(_num_or_coef);
		}
	}
}