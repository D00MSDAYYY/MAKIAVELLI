#pragma once
#include <memory>
#include <unordered_map>

#include "game_network.hpp"
#include "country.hpp"

class Player_Client : public olc::net::client_interface<MSG_FROM>
{
private:
	int _this_country_index{};
	std::unordered_map<uint32_t, Country> _countries;

	//! void OnMessage(olc::net::message<MSG_FROM> &msg) override;

public:
	Player_Client(const std::string &host, const uint16_t port);

	void exchangeRes(SCOPE give_scope, const int give_res,
					 SCOPE receive_scope, const int receive_res);
	void buyPoints(SCOPE scope, const int points);
	void buyLocations(SCOPE scope, std::vector<std::pair<int, int>> coords);
};