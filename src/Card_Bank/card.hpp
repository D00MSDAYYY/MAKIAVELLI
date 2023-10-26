#pragma once
#include <memory>

class Country;

namespace CAR
{
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

}