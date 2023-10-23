#pragma once
#include <memory>
#include <unordered_map>

#include "game_network.hpp"
#include "country.hpp"
#include "ResLocPoi.hpp"

class Game_Server;
enum class SCOPE;

class Player_Client : public olc::net::client_interface<MSG_FROM>
{
private:
	std::string _game_server{};

	std::unordered_map<uint32_t, Data_Resources> _resources;
	std::unordered_map<uint32_t, Data_Points> _points;
	std::unordered_map<uint32_t, Data_Locations> _locations;
	
	void OnMessage(olc::net::message<MSG_FROM> &msg) override;
	void redrawInterface();

public:
	Player_Client(std::string address);

	void exchangeRes(SCOPE give_scope, const int give_res,
					 SCOPE receive_scope, const int receive_res);
	void buyPoints(SCOPE scope, const int points);
	void buyLocations(SCOPE scope, const int locations);

	void run(const std::string &host, const uint16_t port);

	// Data_Points points() const;
	// Data_Resources resources() const;
	// Data_Locations location() const;
};