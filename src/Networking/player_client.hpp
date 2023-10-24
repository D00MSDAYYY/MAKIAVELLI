#pragma once
#include <memory>
#include <unordered_map>

#include "game_network.hpp"
#include "country.hpp"
#include "ResLocPoi.hpp"

#include "player_gui.hpp"

class Game_Server;
enum class SCOPE;

class Player_Client : public olc::net::client_interface<MSG_FROM>
{
private:
	int _this_country_index{};
	std::unordered_map<uint32_t, Country> _countries;

	void OnMessage(olc::net::message<MSG_FROM> &msg) override;

	std::shared_ptr<Player_GUI> player_gui{new Player_GUI{this}};

public:
	Player_Client(std::string address);

	void exchangeRes(SCOPE give_scope, const int give_res,
					 SCOPE receive_scope, const int receive_res);
	void buyPoints(SCOPE scope, const int points);
	void buyLocations(SCOPE scope, std::vector<std::pair<unsigned int, unsigned int>> coords);

	void run(const std::string &host, const uint16_t port);

	// Data_Points points() const;
	// Data_Resources resources() const;
	// Data_Locations location() const;
};