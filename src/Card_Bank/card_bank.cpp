#include "card_bank.hpp"

std::shared_ptr<Card> Card_Bank::card(std::weak_ptr<Country> country)
{
	return std::move(std::shared_ptr<Card>());
}
