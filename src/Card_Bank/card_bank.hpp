#pragma once
#include <vector>
#include <memory>

#include "card.hpp"

class Card_Bank
{
private:
	std::vector<Card> _card_buffer{};

public:
	Card_Bank(){};
	Card_Bank(int number_of_players){};
	~Card_Bank() {}
	std::shared_ptr<Card> card() { return std::shared_ptr<Card>(); };
};