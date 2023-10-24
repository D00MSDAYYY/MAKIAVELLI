#include <list>
#include <deque>

#include "card_bank.hpp"
#include "ResLocPoi.hpp"

const int MAX_YEARS_DEPTH = 5;

enum class SCOPE
{
	ARMY,
	SCIENCE,
	OIL,
	MINERAL,
	FARM,
	INDUSTRY
};

// struct Data_Cards
// {
// 	std::vector<std::pair<uint8_t, uint8_t>> _cards; // duration and index
// };

namespace CAR
{
	using LOC::Locations;
	using POI::Points;
	using RES::Resources;
	class Cards
	{
	private:
		std::deque<std::list<std::shared_ptr<Card>>>
			_cards{MAX_YEARS_DEPTH, {{}}};

		std::shared_ptr<Card_Bank> _card_bank;

		std::shared_ptr<Resources> _resources;
		std::shared_ptr<Locations> _locations;
		std::shared_ptr<Points> _points;

	public:
		Cards() {} //! maybe change

		void setDependices(std::shared_ptr<Card_Bank> card_bank,
						   std::shared_ptr<Locations> locations,
						   std::shared_ptr<Resources> resources,
						   std::shared_ptr<Points> points);

		void getCard();
		void update();

		void operator<<(olc::net::message<MSG_FROM> msg);
		void operator>>(olc::net::message<MSG_FROM> msg);
	};
}
