#include <random>

#include "card_bank.hpp"
#include <iostream>

using CARD::Card;
using CARD::Card_Bank;

Card_Bank::Card_Bank()
{
	std::ifstream cards_input;
	std::string cards_str_input;
	boost::json::array cards_ar;
	cards_input.open("/Users/matvejzajcev/Desktop/MAKIAVELLI/json_files/resources.json");
	cards_input.seekg(0, std::ios::end);
	cards_str_input.resize(cards_input.tellg());
	cards_input.seekg(0, std::ios::beg);
	cards_input.read(&cards_str_input[0], cards_str_input.size());
	cards_input.close();
	cards_ar = boost::json::parse(cards_str_input).as_array();
	//TODO! insert code to fill the buffer of cards
}

std::shared_ptr<Card> Card_Bank::card(Country* country)
{
	auto returning_lambda{[this, country]() -> auto
						  {
							  auto tmp{_main_card_buffer.back()};
							  _main_card_buffer.pop_back();
							  _secondary_card_buffer.push_back(tmp);

							  return std::shared_ptr<Card>{new Card{*tmp, country}};
						  }};

	if (!_main_card_buffer.empty()) //! maybe optimize this using if(!_main_card_buffer.empty() && _main_card_buffer.size() != 1) and shuffle in another thread then returning last card
	{
		return returning_lambda();
	}
	else
	{
		std::default_random_engine dre{
			uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};
		std::shuffle(_secondary_card_buffer.begin(), _secondary_card_buffer.end(), dre);
		_main_card_buffer = std::move(_secondary_card_buffer);

		return returning_lambda();
	}
}


