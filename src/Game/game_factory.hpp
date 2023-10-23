#pragma once
#include <boost/json.hpp>

#include <memory>
#include <string>
#include <fstream>

#include "country.hpp"
#include "game_server.hpp"
#include "card_bank.hpp"


using LOC::Locations;
using POI::Points;
using RES::Resources;

static const int DEFAULT_ID{0};
class Game_Factory
{
private:
	static const int MAX_PLAYERS_NUM = 10;
	static const int MAX_JSON_INDEX = 5;

	int _num_of_players;

	std::shared_ptr<Resources> createResources(int ndx);
	std::shared_ptr<Points> createPoints(int ndx);
	std::shared_ptr<Locations> createLocations(int ndx);
	std::shared_ptr<Cards> createCards(int ndx);
//!
	std::shared_ptr<Card_Bank> createCardBank();
	//!
	void createMap(std::unordered_map<uint32_t, Country> & pl);

	//------------
	std::ifstream res_input;
	std::string res_str_input;
	boost::json::array res_ar;
	//------------
	std::ifstream points_input;
	std::string points_str_input;
	boost::json::array points_ar;
	//------------
	std::ifstream loc_input;
	std::string loc_str_input;
	boost::json::array loc_ar;

public:
	Game_Factory(int numplay);
	
	std::unordered_map<uint32_t, Country> createPlayers();
};