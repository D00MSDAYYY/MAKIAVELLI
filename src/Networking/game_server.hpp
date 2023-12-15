#pragma once

#include "game_network.hpp"
#include "server_gui.h"

#include <memory>

class Country;

class Game_Server : olc::net::server_interface<MSG_FROM>
{
private:
    std::unordered_map<uint32_t, Country> _players;

    Server_GUI*                           _server_gui{nullptr};

    int                                   _play_num{0};
    int                                   _bot_num{0};
    int                                   _rounds_num{0};
    int                                   _thinking_t_num{0};

    int                                   _curr_round{0};

    virtual bool
    OnClientConnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
    virtual void
    OnClientValidated(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
    virtual void
    OnClientDisconnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client) override;
    virtual void
                 OnMessage(std::shared_ptr<olc::net::connection<MSG_FROM>> client,
                           olc::net::message<MSG_FROM>&                    msg) override;
    // void connectBots(); //TODO! create definition
    std::jthread thread_server_running;

public:
    Game_Server(int         play_num,
                int         bot_num,
                int         rounds,
                int         thinking_time,
                Server_GUI* server_gui = nullptr,
                uint16_t    port       = 0);
    virtual ~Game_Server();

    const std::pair<std::string, int>
    address();
    const std::pair<int, int>
    playNum();
    const std::pair<int, int>
    botNum();
    const std::pair<int, int>
    roundsNum();
    const int
    thinkingTime();
};
