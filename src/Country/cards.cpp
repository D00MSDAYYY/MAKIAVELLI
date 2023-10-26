#include "cards.hpp"

using namespace CAR;

void CAR::Cards::setDependices(std::shared_ptr<Card_Bank> card_bank)
{
	_card_bank = card_bank;
}

void CAR::Cards::setDependices(std::shared_ptr<Country> country)
{
	_country = country;
}

void Cards::addCard()
{
	auto card{_card_bank->card(_country.lock())};
	_cards[card->duration() - 1].push_front(std::move(card));
}

void Cards::update()
{
	_cards.pop_front();
	// _cards.push_back(std::shared_ptr<Card>(new Card(nullptr,0)));
	// TODO ! create derived classes
}
