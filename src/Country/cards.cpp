#include "cards.hpp"

using namespace CAR;

void CAR::Cards::setDependices(std::shared_ptr<Card_Bank> card_bank,
							   std::shared_ptr<Locations> locations,
							   std::shared_ptr<Resources> resources,
							   std::shared_ptr<Points> points)
{
	_card_bank = card_bank;
	_locations = locations;
	_resources = resources;
	_points = points;
}


void Cards::getCard()
{
	auto card{_card_bank->card()};
	card->execute(this);
	_cards[card->duration() - 1].push_front(std::move(card));
}

void Cards::update()
{
	_cards.pop_front();
	_cards.push_back({std::make_shared<Card>(Card(0))}); //! check this with debugger
}
