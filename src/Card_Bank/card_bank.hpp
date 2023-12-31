#pragma once
#include "card.hpp"

#include <boost/json.hpp>
#include <vector>

class Country;

namespace CARD
{
class Card_Bank
{
private:
    std::vector<Card> _main_card_buffer{};
    // change this in future to hold only boost::json::array
    // cards_ar like in game_factory
    std::vector<Card> _secondary_card_buffer{};

public:
    Card_Bank(std::vector<Card> card_buffer);

    ~Card_Bank() {}

    Card
    card(Country* country);
};
}  // namespace CARD
