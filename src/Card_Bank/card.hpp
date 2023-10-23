#pragma once
#include <memory>

namespace CAR
{
	class Cards;
}
using CAR::Cards;

class Card
{
private:
	int _index;
	int _duration;
	Cards* _cards;
	virtual void unexecute(){};

public:
	Card() {}

	Card(int duration)
		: _duration{duration}{}

	int duration() { return _duration; }

	virtual void execute(Cards *cards){};
	virtual ~Card() {}
};