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
				_country.lock()->locations()->oilCoef(_num_or_coef);
			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
		if (_scope == SCOPE::MINERAL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->locations()->mineralCoef(_num_or_coef);
			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
		if (_scope == SCOPE::FARM)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->locations()->farmCoef(_num_or_coef);
			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
		if (_scope == SCOPE::INDUSTRY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->locations()->industryCoef(_num_or_coef);
			if (_effect == EFFECT::NUMBER)
				; //!-----------
		}
	}

	if (_target == TARGET::POINTS)
	{
		if (_scope == SCOPE::ARMY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->armyCoefCost(_num_or_coef);
			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->armyNum(_num_or_coef);
		}
		if (_scope == SCOPE::SCIENCE)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->scienceCoefCost(_num_or_coef); //TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()
 
			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->scienceNum(_num_or_coef);
		}
		if (_scope == SCOPE::OIL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->oilCoefCost(_num_or_coef); // TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()

			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->oilNum(_num_or_coef);
		}
		if (_scope == SCOPE::MINERAL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->mineralCoefCost(_num_or_coef); // TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()

			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->mineralNum(_num_or_coef); // TODO! create a buffer variable to store the half/ third or etc part of initial number of ... to add on a call of unexecute()
		}
		if (_scope == SCOPE::FARM)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->farmCoefCost(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->farmNum(_num_or_coef);
		}
		if (_scope == SCOPE::INDUSTRY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->industryCoefCost(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->industryNum(_num_or_coef);
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
				_country.lock()->resources()->oilCoef(_num_or_coef); //TODO! add option to increase/decrease capital of resources in ... times

			if (_effect == EFFECT::NUMBER)
				_country.lock()->resources()->oilNum(_num_or_coef);
		}
		if (_scope == SCOPE::MINERAL)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->resources()->mineralCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country.lock()->resources()->mineralNum(_num_or_coef);
		}
		if (_scope == SCOPE::FARM)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->resources()->farmCoef(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country.lock()->resources()->farmNum(_num_or_coef);
		}
		if (_scope == SCOPE::INDUSTRY)
		{
			if (_effect == EFFECT::COEFFICIENT)
				_country.lock()->points()->industryCoefCost(_num_or_coef);

			if (_effect == EFFECT::NUMBER)
				_country.lock()->points()->industryNum(_num_or_coef);
		}
	}
}

bool CARD::Card::attach(std::weak_ptr<Country> country)
{
	if(_country.expired())
	{
		_country = country;
		execute();
		return true;
	}
	else
	{
		return false;
	}
}

void CARD::Card::detach()
{
	if (!_country.expired())
	{
		unexecute();
		_country.reset();
	}
}
