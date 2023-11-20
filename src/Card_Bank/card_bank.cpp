#include <random>

#include "card_bank.hpp"
#include <iostream>

using CARD::Card;
using CARD::Card_Bank;

Card_Bank::Card_Bank(std::vector<Card> card_buffer)
	: _main_card_buffer{std::move(card_buffer)} {}

Card Card_Bank::card(Country *country)
{
	auto returning_lambda{[this, country]() 
						  {
							  auto tmp{_main_card_buffer.back()};
							  _main_card_buffer.pop_back();
							  _secondary_card_buffer.push_back(tmp);

							  return Card{tmp, country};
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
