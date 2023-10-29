#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <boost/json.hpp>

#include "card.hpp"

namespace CARD
{
	class Card_Bank
	{
	private:
		std::vector<std::shared_ptr<Card>> _main_card_buffer{}; //! change this in future to hold only boost::json::array cards_ar like in game_factory
		std::vector<std::shared_ptr<Card>> _secondary_card_buffer{};

	public:
		Card_Bank();
		~Card_Bank(){}

		std::shared_ptr<Card> card(std::weak_ptr<Country> country);
	};
}