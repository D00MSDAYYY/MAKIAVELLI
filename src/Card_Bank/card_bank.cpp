#include <random>

#include "card_bank.hpp"

using CARD::Card_Bank;
using CARD::Card;

Card_Bank::Card_Bank()
{
	std::ifstream cards_input;
	std::string cards_str_input;
	boost::json::array cards_ar;
	cards_input.open("resources.json");
	cards_input.seekg(0, std::ios::end);
	cards_str_input.resize(cards_input.tellg());
	cards_input.seekg(0, std::ios::beg);
	cards_input.read(&cards_str_input[0], cards_str_input.size());
	cards_input.close();
	cards_ar = boost::json::parse(cards_str_input).as_array();

	for(auto& card : cards_ar)
	{

	}
}

std::shared_ptr<Card> Card_Bank::card(std::weak_ptr<Country> country)
{
	if (!_main_card_buffer.empty()) //! maybe optimize this using if(!_main_card_buffer.empty() && _main_card_buffer.size() != 1) and shuffle in another thread then returning last card
	{ 
		auto tmp{_main_card_buffer.back()};
		_main_card_buffer.pop_back();
		_secondary_card_buffer.push_back(tmp);

		return tmp;
	}
	else
	{
		std::default_random_engine dre{
			uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};
		std::shuffle(_secondary_card_buffer.begin(), _secondary_card_buffer.end(), dre);
		_main_card_buffer = std::move(_secondary_card_buffer);

		auto tmp{_main_card_buffer.back()};
		_main_card_buffer.pop_back();
		_secondary_card_buffer.push_back(tmp);

		return tmp;
	}
}
