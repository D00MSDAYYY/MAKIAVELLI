#pragma once

#include "card_bank.hpp"
#include "game_network.hpp"

#include <deque>
#include <list>

const int MAX_YEARS_DEPTH = 5;

class Counry;

namespace CARD
{
class Cards_Holder
{
private:
    std::deque<std::list<Card>> _cards{MAX_YEARS_DEPTH, {{}}};

    Country*                    _country;
    std::shared_ptr<Card_Bank>  _card_bank;

public:
    Cards_Holder() {}

    ~Cards_Holder();

    void
    setDependices(std::shared_ptr<Card_Bank> card_bank);
    void
    setDependices(Country* country);

    void
    addCard();
    void
    update();

    void
    operator<<(olc::net::message<MSG_FROM>& msg){};
    void
    operator>>(olc::net::message<MSG_FROM>& msg){};
};
}  // namespace CARD
