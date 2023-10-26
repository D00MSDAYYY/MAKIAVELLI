#pragma once
#include <memory>

namespace CAR
{
	class Cards;
}
using CAR::Cards;
class Country;

class Card
{
private:
	int _card_index;
	int _duration;
	std::weak_ptr<Country> _country;

	virtual void unexecute() = 0;
	virtual void execute() = 0;

public:
	Card(std::weak_ptr<Country> country, int duration);

	int duration() { return _duration; }

	virtual ~Card();
};