#pragma once
#include <memory>
#include <unordered_map>

#include "game_network.hpp"

class Country;
class Server_GUI;

class Game_Server : olc::net::server_interface<MSG_FROM>
{
private:
	std::unordered_map<uint32_t, Country> _players;

	Server_GUI *_server_gui{nullptr};

	int _play_num{};
	int _bot_num{};
	int _rounds{};
	int _thinking_time{};
	
	virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
	virtual void OnClientValidated(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
	virtual void OnMessage(std::shared_ptr<olc::net::connection<MSG_FROM>> client,
				   olc::net::message<MSG_FROM> &msg) override;
	// void connectBots(); //TODO! create definition
	std::jthread thread_server_running;

public:
	Game_Server(int play_num, int bot_num,
				int rounds, int thinking_time, uint16_t port = 0);
	virtual ~Game_Server();
};
