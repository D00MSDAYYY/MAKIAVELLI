#pragma once
#include <memory>
#include <unordered_map>

#include "game_network.hpp"
#include "country.hpp"

class Client_GUI;

class Player_Client : public olc::net::client_interface<MSG_FROM>
{
private:
	int _this_country_index{};
	std::unordered_map<int, Country> _countries;
	Client_GUI *_client_gui{nullptr};

	std::jthread thread_updating;
	void OnMessage(olc::net::message<MSG_FROM> &msg) override;

public:
	Player_Client(const std::string &host, const uint16_t port,
				  Client_GUI *client_gui = nullptr);
	~Player_Client(){};

	// void exchangeRes(SCOPE give_scope, const int give_res,
	// 				 SCOPE receive_scope, const int receive_res);
	// void buyPoints(SCOPE scope, const int points);
	// void buyLocations(SCOPE scope, std::vector<std::pair<int, int>> cells);

	const std::unordered_map<int, Country> &countries();
	const int thisCountryIndex() { return _this_country_index; }
};