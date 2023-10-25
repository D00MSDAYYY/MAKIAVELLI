#include "game_server.hpp"

#include "country.hpp"

#include <algorithm>
#include <utility>
#include <thread>
#include <stop_token>
#include <chrono>

Game_Server::Game_Server(int play_num, int bot_num,
						 int rounds, int thinking_time, uint16_t port)
	: olc::net::server_interface<MSG_FROM>(port),
	  _play_num{play_num},
	  _bot_num{bot_num},
	  _rounds{rounds},
	  _thinking_time{thinking_time}
{
	Game_Factory factory{_play_num + _bot_num};
	_players = factory.createPlayers();
}

Game_Server::~Game_Server()
{
}

void Game_Server::run()
{

	Start();
	while (m_deqConnections.size() < _players.size())
		std::this_thread::sleep_for(std::chrono::seconds(3));

	auto lambda_updating{[this](std::stop_token stop_token)
						 {
							 while (!stop_token.stop_requested())
							 {
								 Update(-1, true); //! with true it can lead to deadlock coz wait shall never wake up
							 }
						 }};
	std::jthread thread_updating{lambda_updating};

	for (int curr_round{0}; curr_round < _rounds; ++curr_round)
	{
		for (auto &[ID, country] : _players) //! this is very silly way to iterate over the players, because then we extract the node with country on disconnection of the client and after connect again and set the node  new (bigger) index we violate the order of players in queue
		{
			country.activityPoints()->currentPoints(country.activityPoints()->maxPoints());

			olc::net::message<MSG_FROM> msg_active_country{};
			msg_active_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
			country >> msg_active_country;
			MessageAllClients(msg_active_country);

			std::this_thread::sleep_for(std::chrono::seconds(_thinking_time));
			country.activityPoints()->currentPoints(-country.activityPoints()->maxPoints());

			olc::net::message<MSG_FROM> msg_inactive_country{};
			msg_inactive_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
			country >> msg_inactive_country;
			MessageAllClients(msg_inactive_country);
		}
	}
	thread_updating.request_stop();
}

bool Game_Server::OnClientConnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client)
{
	// OnClientValidated;
	return true;
}

void Game_Server::OnClientValidated(std::shared_ptr<olc::net::connection<MSG_FROM>> client)
{
	if (client) 
	{
		if (m_deqConnections.size() != _play_num)
		{
			for (auto &[ID, country] : _players)
			{
				if (!country.busy())
				{
					country.busy(true);
					auto node{_players.extract(ID)};
					node.key() = client->GetID();
					_players.insert(std::move(node));

					olc::net::message<MSG_FROM> msg;
					msg.header.id = MSG_FROM::SERVER_HANDSHAKE;
					country >> msg;
					MessageClient(client, msg);

					for (auto &[ID, country] : _players)
					{
						olc::net::message<MSG_FROM> msg;
						msg.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
						country >> msg;
						MessageClient(client, msg);
					}
					return;
				}
			}
		}
	}
	client.reset();
	m_deqConnections.erase(
		std::remove(m_deqConnections.begin(),
					m_deqConnections.end(),
					client),
		m_deqConnections.end());
}
void Game_Server::OnClientDisconnect(std::shared_ptr<olc::net::connection<MSG_FROM>> client)
{
	if (client)
	{
		_players.at(client->GetID()).busy(false);
	}
}

void Game_Server::OnMessage(std::shared_ptr<olc::net::connection<MSG_FROM>> client, olc::net::message<MSG_FROM> &msg)
{
	switch (msg.header.id)
	{
	case MSG_FROM::CLIENT_BUY_POINTS:
	{
		if (_players.at(client->GetID()).activityPoints()->currentPoints() == 0)
			return;
		Points buy_points;
		buy_points << msg;

		bool is_bought{false};
		if (!is_bought &&
			buy_points.army() > 0 &&
			_players.at(client->GetID()).points()->army(buy_points.army()))

		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			buy_points.science() > 0 &&
			_players.at(client->GetID()).points()->army(buy_points.science()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			buy_points.oil() > 0 &&
			_players.at(client->GetID()).points()->army(buy_points.oil()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			buy_points.mineral() > 0 &&
			_players.at(client->GetID()).points()->army(buy_points.mineral()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&

			_players.at(client->GetID()).points()->army(buy_points.farm()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&

			_players.at(client->GetID()).points()->army(buy_points.industry()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		olc::net::message<MSG_FROM> msg_country{};
		msg_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
		_players.at(client->GetID()) >> msg_country;
		MessageAllClients(msg_country);
		break;
	}
	case MSG_FROM::CLIENT_BUY_LOCATIONS:
	{
		if (_players.at(client->GetID()).activityPoints()->currentPoints() == 0)
			return;

		Locations buy_locations{};
		buy_locations << msg;

		bool is_bought{false};
		if (!is_bought &&
			buy_locations.oil() > 0 &&
			_players.at(client->GetID()).locations()->oil(buy_locations.country_map()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			buy_locations.mineral() > 0 &&
			_players.at(client->GetID()).locations()->mineral(buy_locations.country_map()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			buy_locations.farm() > 0 &&
			_players.at(client->GetID()).locations()->farm(buy_locations.country_map()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			buy_locations.industry() > 0 &&
			_players.at(client->GetID()).locations()->industry(buy_locations.country_map()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		olc::net::message<MSG_FROM> msg_country{};
		msg_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
		_players.at(client->GetID()) >> msg_country;
		MessageAllClients(msg_country);
		break;
	}
	case MSG_FROM::CLIENT_REQUEST_EXCHANGE_RES:
	{
		Country sender_request_exchange;
		Country receiver_request_exchange;

		sender_request_exchange << msg;
		receiver_request_exchange << msg;

		auto receiver_client{
			std::find_if(
				m_deqConnections.begin(),
				m_deqConnections.end(),
				[&sender_request_exchange, this](const auto &connection)
				{
					return _players.at(connection->GetID()).index() == sender_request_exchange.index();
				})};

		if (receiver_client != m_deqConnections.end())
		{
			olc::net::message<MSG_FROM> msg_request_exchange{};
			msg_request_exchange.header.id = MSG_FROM::SERVER_REQUEST_EXCHANGE_RES;

			receiver_request_exchange >> msg_request_exchange;
			sender_request_exchange >> msg_request_exchange;
			MessageClient(*receiver_client, msg_request_exchange);
		}

		break;
	}

	case MSG_FROM::CLIENT_ACCEPT_EXCHANGE_RES: 
	{
		Country sender_accept_exchange;
		Country receiver_accept_exchange;

		sender_accept_exchange << msg;
		receiver_accept_exchange << msg;

		auto receiver_accept_client{
			std::find_if(
				m_deqConnections.begin(),
				m_deqConnections.end(),
				[&receiver_accept_exchange, this](const auto &client)
				{
					return _players.at(client->GetID()).index() == receiver_accept_exchange.index();
				})};
		if (receiver_accept_client != m_deqConnections.end())
		{
			if (_players.at(client->GetID()).activityPoints()->currentPoints() != 0 ||
				_players.at((*receiver_accept_client)->GetID()).activityPoints()->currentPoints() != 0)
			{
				_players.at(client->GetID()).activityPoints()->currentPoints(-1);
				_players.at((*receiver_accept_client)->GetID()).activityPoints()->currentPoints(-1);

				*_players.at(client->GetID()).resources() += // TODO! check this logic precisely and consider the situation then the order of this operations affect the final number of resources at both sides
					*receiver_accept_exchange.resources();
				*_players.at(client->GetID()).resources() -=
					*sender_accept_exchange.resources();

				*_players.at((*receiver_accept_client)->GetID()).resources() +=
					*sender_accept_exchange.resources();
				*_players.at((*receiver_accept_client)->GetID()).resources() -=
					*receiver_accept_exchange.resources();

				olc::net::message<MSG_FROM> msg_sender_accept_country{};
				msg_sender_accept_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
				_players.at(client->GetID()) >> msg_sender_accept_country;
				MessageAllClients(msg_sender_accept_country);

				olc::net::message<MSG_FROM> msg_receiver_accept_country{};
				msg_receiver_accept_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
				_players.at((*receiver_accept_client)->GetID()) >> msg_receiver_accept_country;
				MessageAllClients(msg_receiver_accept_country);
			}
		}
		break;
	}
	case MSG_FROM::CLIENT_TEXT_MESSAGE:
	{
		
		break;
	}
	}
}
