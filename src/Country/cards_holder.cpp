#include "cards_holder.hpp"

using namespace CARD;

void Cards_Holder::setDependices(std::shared_ptr<Card_Bank> card_bank)
{
	_card_bank = card_bank;
}

void Cards_Holder::setDependices(std::shared_ptr<Country> country)
{
	_country = country;
}

void Cards_Holder::addCard()
{
	auto card{_card_bank->card(_country)};
	_cards[card->duration() - 1].push_front(std::move(card));
}

void Cards_Holder::update()
{
	_cards.pop_front();
	// _cards.push_back(std::shared_ptr<Card>(new Card(nullptr,0)));
}
