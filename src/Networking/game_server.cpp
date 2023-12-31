// #include <algorithm>
// #include <utility>
#include "game_server.hpp"

#include "game_factory.hpp"
#include "text_message.hpp"

#include <chrono>
#include <stop_token>
#include <thread>

Game_Server::Game_Server(int         play_num,
                         int         bot_num,
                         int         rounds,
                         int         thinking_time,
                         Server_GUI* server_gui,
                         uint16_t    port)
    : olc::net::server_interface<MSG_FROM>(port),
      _play_num{ play_num },
      _bot_num{ bot_num },
      _rounds_num{ rounds },
      _thinking_t_num{ thinking_time },
      _server_gui{ server_gui }
{
    Game_Factory factory{ _play_num + _bot_num };
    _players              = factory.createPlayers();

    thread_server_running = std::jthread{
        [this](std::stop_token quit_token)
        {
            Start();
            std::jthread thread_updating{ [this](std::stop_token stop_token)
                                          {
                                              while(!stop_token.stop_requested())
                                              {
                                                  Update(-1, true);
                                              }
                                          } };

            // while (m_deqConnections.size() < _players.size())
            // {
            // 	std::this_thread::sleep_for(std::chrono::seconds(3));
            // }
            std::this_thread::sleep_for(std::chrono::seconds(1));

            for(_curr_round = 0; _curr_round < _rounds_num; ++_curr_round)
            {
                for(auto& [ID, country]:
                    _players)  //! this is very silly way to iterate over the
                               //! players, because then we extract the node
                               //! with country on disconnection of the client
                               //! and after connect again and set the node  new
                               //! (bigger) index we violate the order of
                               //! players in queue
                {
                    if(_server_gui) _server_gui->redraw();

                    country.activityPoints().currentPoints(
                        country.activityPoints().maxPoints());
                    country.update();

                    olc::net::message<MSG_FROM> msg_active_country{};
                    msg_active_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
                    country >> msg_active_country;
                    MessageAllClients(msg_active_country);

                    if(quit_token.stop_requested()) return;
                    std::this_thread::sleep_for(std::chrono::seconds(7));
                    country.activityPoints().currentPoints(
                        -country.activityPoints().maxPoints());
                    olc::net::message<MSG_FROM> msg_inactive_country{};
                    msg_inactive_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
                    country >> msg_inactive_country;
                    MessageAllClients(msg_inactive_country);
                }
            }
        }
    };
}

Game_Server::~Game_Server() { _server_gui = nullptr; }

const std::pair<std::string, int>
Game_Server::address()
{
    return { m_asioAcceptor.local_endpoint().address().to_string(),
             m_asioAcceptor.local_endpoint().port() };
}

const std::pair<int, int>
Game_Server::playNum()
{
    int count{ 0 };
    for(auto& [ID, country]: _players)
    {
        if(country.busy()) ++count;
    }
    count -= _bot_num;
    return { (count > 0) ? count : 0, _play_num };
}

const std::pair<int, int>
Game_Server::botNum()
{
    return { _bot_num, _bot_num };
}

const std::pair<int, int>
Game_Server::roundsNum()
{
    return { _curr_round, _rounds_num };
}

const int
Game_Server::thinkingTime()
{
    return _thinking_t_num;
}

bool
Game_Server::OnClientConnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client)
{
    return (m_deqConnections.size() <= _play_num) ? true : false;
}

void
Game_Server::OnClientValidated(std::shared_ptr<olc::net::connection<MSG_FROM>> client)
{
    if(client)
    {
        if(m_deqConnections.size() <= _play_num)
        {
            for(auto& [ID, country]: _players)
            {
                if(!country.busy())
                {
                    country.busy(true);
                    auto node{ _players.extract(ID) };
                    node.key() = client->GetID();
                    _players.insert(std::move(node));

                    olc::net::message<MSG_FROM> msg;
                    msg.header.id = MSG_FROM::SERVER_HANDSHAKE;
                    country >> msg;

                    MessageClient(client, msg);

                    for(auto& [ID, country]: _players)
                    {
                        olc::net::message<MSG_FROM> msg;
                        msg.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
                        country >> msg;
                        MessageClient(client, msg);
                    }
                    _server_gui->redraw();
                    break;
                }
            }
        }
    }
    else
    {
        m_deqConnections.erase(
            std::remove(m_deqConnections.begin(), m_deqConnections.end(), client),
            m_deqConnections.end());
    }
}

void
Game_Server::OnClientDisconnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client)
{
    if(client) _players.at(client->GetID()).busy(false);
}

void
Game_Server::OnMessage(std::shared_ptr<olc::net::connection<MSG_FROM>> client,
                       olc::net::message<MSG_FROM>&                    msg)
{
    switch(msg.header.id)
    {
        case MSG_FROM::CLIENT_BUY_POINTS :
            {
                if(_players.at(client->GetID()).activityPoints().currentPoints() == 0)
                    return;
                POI::Points buy_points;
                buy_points << msg;

                bool is_bought{ false };
                if(!is_bought && buy_points.armyNum() > 0
                   && _players.at(client->GetID()).points().armyNum(buy_points.armyNum()))

                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought && buy_points.scienceNum() > 0
                   && _players.at(client->GetID())
                          .points()
                          .armyNum(buy_points.scienceNum()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought && buy_points.oilNum() > 0
                   && _players.at(client->GetID()).points().armyNum(buy_points.oilNum()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought && buy_points.mineralNum() > 0
                   && _players.at(client->GetID())
                          .points()
                          .armyNum(buy_points.mineralNum()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought &&

                   _players.at(client->GetID()).points().armyNum(buy_points.farmNum()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought &&

                   _players.at(client->GetID())
                       .points()
                       .armyNum(buy_points.industryNum()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                olc::net::message<MSG_FROM> msg_country{};
                msg_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
                _players.at(client->GetID()) >> msg_country;
                MessageAllClients(msg_country);
                break;
            }
        case MSG_FROM::CLIENT_BUY_LOCATIONS :
            {
                if(_players.at(client->GetID()).activityPoints().currentPoints() == 0)
                    return;

                Locations buy_locations{};
                buy_locations << msg;

                bool is_bought{ false };
                if(!is_bought && buy_locations.oilNum() > 0
                   && _players.at(client->GetID())
                          .locations()
                          .oilNum(buy_locations.coords()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought && buy_locations.mineralNum() > 0
                   && _players.at(client->GetID())
                          .locations()
                          .mineralNum(buy_locations.coords()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought && buy_locations.farmNum() > 0
                   && _players.at(client->GetID())
                          .locations()
                          .farmNum(buy_locations.coords()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                if(!is_bought && buy_locations.industryNum() > 0
                   && _players.at(client->GetID())
                          .locations()
                          .industryNum(buy_locations.coords()))
                {
                    _players.at(client->GetID()).activityPoints().currentPoints(-1);
                    is_bought = true;
                }

                olc::net::message<MSG_FROM> msg_country{};
                msg_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
                _players.at(client->GetID()) >> msg_country;
                MessageAllClients(msg_country);
                break;
            }
        case MSG_FROM::CLIENT_REQUEST_EXCHANGE_RES :
            {
                Country sender_request_exchange;
                Country receiver_request_exchange;

                sender_request_exchange << msg;
                receiver_request_exchange << msg;

                auto receiver_client{ std::find_if(
                    m_deqConnections.begin(),
                    m_deqConnections.end(),
                    [&sender_request_exchange, this](const auto& connection)
                    {
                        return _players.at(connection->GetID()).index()
                            == sender_request_exchange.index();
                    }) };

                if(receiver_client != m_deqConnections.end())
                {
                    olc::net::message<MSG_FROM> msg_request_exchange{};
                    msg_request_exchange.header.id =
                        MSG_FROM::SERVER_REQUEST_EXCHANGE_RES;

                    receiver_request_exchange >> msg_request_exchange;
                    sender_request_exchange >> msg_request_exchange;
                    MessageClient(*receiver_client, msg_request_exchange);
                }

                break;
            }

        case MSG_FROM::CLIENT_ACCEPT_EXCHANGE_RES :
            {
                Country sender_accept_exchange;
                Country receiver_accept_exchange;

                sender_accept_exchange << msg;
                receiver_accept_exchange << msg;

                auto receiver_accept_client{ std::find_if(
                    m_deqConnections.begin(),
                    m_deqConnections.end(),
                    [&receiver_accept_exchange, this](const auto& client) {
                        return _players.at(client->GetID()).index()
                            == receiver_accept_exchange.index();
                    }) };
                if(receiver_accept_client != m_deqConnections.end())
                {
                    if(_players.at(client->GetID()).activityPoints().currentPoints() != 0
                       || _players.at((*receiver_accept_client)->GetID())
                                  .activityPoints()
                                  .currentPoints()
                              != 0)
                    {
                        _players.at(client->GetID()).activityPoints().currentPoints(-1);
                        _players.at((*receiver_accept_client)->GetID())
                            .activityPoints()
                            .currentPoints(-1);

                        _players.at(client->GetID())
                            .resources() +=  // TODO! check this logic precisely
                                             // and consider the situation then
                                             // the order of this operations
                                             // affect the final number of
                                             // resources at both sides
                            receiver_accept_exchange.resources();
                        _players.at(client->GetID()).resources() -=
                            sender_accept_exchange.resources();

                        _players.at((*receiver_accept_client)->GetID()).resources() +=
                            sender_accept_exchange.resources();
                        _players.at((*receiver_accept_client)->GetID()).resources() -=
                            receiver_accept_exchange.resources();

                        olc::net::message<MSG_FROM> msg_sender_accept_country{};
                        msg_sender_accept_country.header.id =
                            MSG_FROM::SERVER_DATA_COUNTRY;
                        _players.at(client->GetID()) >> msg_sender_accept_country;
                        MessageAllClients(msg_sender_accept_country);

                        olc::net::message<MSG_FROM> msg_receiver_accept_country{};
                        msg_receiver_accept_country.header.id =
                            MSG_FROM::SERVER_DATA_COUNTRY;
                        _players.at((*receiver_accept_client)->GetID())
                            >> msg_receiver_accept_country;
                        MessageAllClients(msg_receiver_accept_country);
                    }
                }
                break;
            }
        case MSG_FROM::CLIENT_TEXT_MESSAGE :
            {
                Text_Message txt_mes{};
                txt_mes << msg;

                auto receiver_txt_mes{ std::find_if(
                    m_deqConnections.begin(),
                    m_deqConnections.end(),
                    [&txt_mes, this](const auto& client)
                    { return _players.at(client->GetID()).index() == txt_mes._index; }) };

                if(receiver_txt_mes != m_deqConnections.end())
                {
                    olc::net::message<MSG_FROM> msg_txt_mes{};
                    msg_txt_mes.header.id = MSG_FROM::SERVER_TEXT_MESSAGE;
                    txt_mes._index        = _players.at(client->GetID()).index();
                    txt_mes >> msg_txt_mes;
                    MessageClient(*receiver_txt_mes, msg_txt_mes);
                }
                break;
            }
    }
}
