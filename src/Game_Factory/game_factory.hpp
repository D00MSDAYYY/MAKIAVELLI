#pragma once
#include "country.hpp"

#include <boost/json.hpp>
#include <memory>

static const int DEFAULT_ID{0};

class Game_Factory
{
private:
    const int          MAX_PLAYERS_NUM = 10;
    const int          MAX_JSON_INDEX  = 5;

    int                _num_of_players;

    boost::json::array res_ar{};
    boost::json::array points_ar{};
    boost::json::array loc_ar{};
    boost::json::array cards_ar{};

    RES::Resources
    createResources(int index);
    POI::Points
    createPoints(int index);
    LOC::Locations
    createLocations(int index);
    CARD::Cards_Holder
    createCardsHolder(int index);
    AC_POI::Activity_Points
                                     createActivityPoints(int index);

    std::shared_ptr<CARD::Card_Bank> _card_bank{nullptr};
    std::shared_ptr<Map>             _map{nullptr};

    void
    createCardBank(std::unordered_map<uint32_t, Country>& pl);
    void
    createMap(std::unordered_map<uint32_t, Country>& pl);

public:
    Game_Factory(int numplay);
    ~Game_Factory();

    std::unordered_map<uint32_t, Country>
    createPlayers();
};
