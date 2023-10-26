#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <boost/json.hpp>

#include "card.hpp"

class Card_Bank
{
private:
	std::vector<Card> _card_buffer{};

	std::ifstream cards_input;
	std::string cards_str_input;
	boost::json::array cards_ar;

public:
	Card_Bank(){};
	~Card_Bank() {}
	std::shared_ptr<Card> card(std::weak_ptr<Country> country);
};