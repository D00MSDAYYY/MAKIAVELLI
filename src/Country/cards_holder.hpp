#include <list>
#include <deque>

#include "card_bank.hpp"
#include "ResLocPoi.hpp"

const int MAX_YEARS_DEPTH = 5;




namespace CARD
{
	using LOC::Locations;
	using POI::Points;
	using RES::Resources;
	class Cards_Holder
	{
	private:
		std::deque<std::list<std::shared_ptr<Card>>> _cards{MAX_YEARS_DEPTH, {{}}};

		std::weak_ptr<Country> _country;
		std::shared_ptr<Card_Bank> _card_bank;

		std::shared_ptr<Resources> _resources;
		std::shared_ptr<Locations> _locations;
		std::shared_ptr<Points> _points;

	public:
		Cards_Holder() {}
		void setDependices(std::shared_ptr<Card_Bank> card_bank);
		void setDependices(std::shared_ptr<Country> country);

		void addCard();

		void update();

		void operator<<(olc::net::message<MSG_FROM> msg);
		void operator>>(olc::net::message<MSG_FROM> msg);
	};
}
