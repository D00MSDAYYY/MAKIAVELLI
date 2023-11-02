#pragma once
#include <memory>
#include <unordered_map>

#include "game_network.hpp"
#include "game_factory.hpp"

class Game_Server : olc::net::server_interface<MSG_FROM>
{
private:
	std::unordered_map<uint32_t, Country> _players;

	int _play_num{};
	int _bot_num{};
	int _rounds{};
	int _thinking_time{};
	

	bool OnClientConnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
	void OnClientValidated(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
	void OnClientDisconnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
	void OnMessage(std::shared_ptr<olc::net::connection<MSG_FROM>> client,
				   olc::net::message<MSG_FROM> &msg) override;
	void connectBots(); //TODO! create definition

public:
	Game_Server(int play_num, int bot_num,
				int rounds, int thinking_time, uint16_t port = 0);
	~Game_Server();

	void run();
};
