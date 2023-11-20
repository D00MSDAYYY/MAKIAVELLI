#pragma once
#include <boost/json.hpp>
#include <memory>

#include "country.hpp"
#include "game_server.hpp"
#include "card_bank.hpp"

static const int DEFAULT_ID{0};
class Game_Factory
{
private:
	const int MAX_PLAYERS_NUM = 10;
	const int MAX_JSON_INDEX = 5;

	int _num_of_players;

	RES::Resources createResources(int index);
	POI::Points createPoints(int index);
	LOC::Locations createLocations(int index);
	CARD::Cards_Holder createCardsHolder(int index);
	AC_POI::Activity_Points createActivityPoints(int index);

	std::shared_ptr<CARD::Card_Bank> _card_bank{nullptr};
	void createCardBank(std::unordered_map<uint32_t, Country> &pl);
	std::shared_ptr<Map> _map{nullptr};
	void createMap(std::unordered_map<uint32_t, Country> &pl);

	boost::json::array res_ar{};
	boost::json::array points_ar{};
	boost::json::array loc_ar{};
	boost::json::array cards_ar{};

public:
	Game_Factory(int numplay);
	~Game_Factory();

	std::unordered_map<uint32_t, Country> createPlayers();
};