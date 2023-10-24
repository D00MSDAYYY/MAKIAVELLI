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
	Game_Factory factory(_play_num + _bot_num);
	_players = std::move(factory.createPlayers());
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
	std::jthread thread_updating{lambda_updating}; // TODO! maybe relocate threads in class body

	for (int curr_round{0}; curr_round < _rounds; ++curr_round)
	{
		for (auto &[ID, country] : _players) //! this is very silly way to iterate over the players, because then we extract the node with country on disconnection of the client and after connect again and set the node  new (bigger) index we violate the order of players in queue
		{
			country.activityPoints()->currentPoints(country.activityPoints()->maxPoints());

			Country data_active_country{country.convertToData()};
			olc::net::message<MSG_FROM> msg_data_active_country{};
			msg_data_active_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
			msg_data_active_country << data_active_country;
			MessageAllClients(msg_data_active_country);

			std::this_thread::sleep_for(std::chrono::seconds(_thinking_time));
			country.activityPoints()->currentPoints(-country.activityPoints()->maxPoints());

			Country data_inactive_country{country.convertToData()};
			olc::net::message<MSG_FROM> msg_data_inactive_country{};
			msg_data_inactive_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
			msg_data_inactive_country << data_inactive_country;
			MessageAllClients(msg_data_inactive_country);
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
	if (client) // TODO! for optimization might be needed bool is_full_of_connections_to_server{};
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
				msg << country.convertToData()._data_index;
				MessageClient(client, msg);

				for (auto &[ID, country] : _players)
				{
					olc::net::message<MSG_FROM> msg;
					msg.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
					msg << country.convertToData();
					MessageClient(client, msg);
				}
				return;
			}
		}
		client.reset();
		m_deqConnections.erase(
			std::remove(m_deqConnections.begin(),
						m_deqConnections.end(),
						client),
			m_deqConnections.end());
	}
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
		Points data_buy_points;
		msg >> data_buy_points;

		bool is_bought{false};
		if (!is_bought &&
			data_buy_points.army() > 0 &&
			_players.at(client->GetID()).points()->army(data_buy_points.army()))

		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_buy_points.science() > 0 &&
			_players.at(client->GetID()).points()->army(data_buy_points.science()))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_buy_points._oil_points > 0 &&
			_players.at(client->GetID()).points()->army(data_buy_points._oil_points))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_buy_points._mineral_points > 0 &&
			_players.at(client->GetID()).points()->army(data_buy_points._mineral_points))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_buy_points._farm_points > 0 &&
			_players.at(client->GetID()).points()->army(data_buy_points._farm_points))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_buy_points._industry_points > 0 &&
			_players.at(client->GetID()).points()->army(data_buy_points._industry_points))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		olc::net::message<MSG_FROM> msg_data_country{};
		msg_data_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
		msg_data_country << _players.at(client->GetID()).convertToData();
		MessageAllClients(msg_data_country);
		//! send the whole country data coz everything is changed
		break;
	}
	case MSG_FROM::CLIENT_BUY_LOCATIONS:
	{
		if (_players.at(client->GetID()).activityPoints()->currentPoints() == 0)
			return;
		Data_Locations data_locations;
		int size_of_coord_array{0};
		msg >> size_of_coord_array;
		for (int i{0}; i < size_of_coord_array; ++i)
		{
			msg >> data_locations._loc_coord[i];
		}
		bool is_bought{false};
		if (!is_bought &&
			data_locations._loc_type == LOC_TYPE::OIL &&
			data_locations._loc_coord.size() > 0 &&
			_players.at(client->GetID()).locations()->oil(data_locations._loc_coord))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_locations._loc_type == LOC_TYPE::MINERAL &&
			data_locations._loc_coord.size() > 0 &&
			_players.at(client->GetID()).locations()->mineral(data_locations._loc_coord))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_locations._loc_type == LOC_TYPE::FARM &&
			data_locations._loc_coord.size() > 0 &&
			_players.at(client->GetID()).locations()->farm(data_locations._loc_coord))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		if (!is_bought &&
			data_locations._loc_type == LOC_TYPE::INDUSTRY &&
			data_locations._loc_coord.size() > 0 &&
			_players.at(client->GetID()).locations()->industry(data_locations._loc_coord))
		{
			_players.at(client->GetID()).activityPoints()->currentPoints(-1);
			is_bought = true;
		}

		olc::net::message<MSG_FROM> msg_data_country{};
		msg_data_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
		msg_data_country << _players.at(client->GetID()).convertToData();
		MessageAllClients(msg_data_country);
		break;
	}
	case MSG_FROM::CLIENT_REQUEST_EXCHANGE_RES:
	{
		Data_Country data_sender_request_exchange;
		Data_Country data_receiver_request_exchange;
		msg >> data_sender_request_exchange >> data_receiver_request_exchange;

		auto receiver_client{
			std::find_if(
				m_deqConnections.begin(),
				m_deqConnections.end(),
				[&data_sender_request_exchange, this](const auto &connection)
				{
					return _players.at(connection->GetID()).index() == data_sender_request_exchange._data_index;
				})};

		if (receiver_client != m_deqConnections.end())
		{
			olc::net::message<MSG_FROM> msg_request_exchange{};
			msg_request_exchange.header.id = MSG_FROM::SERVER_REQUEST_EXCHANGE_RES;
			data_sender_request_exchange._data_index = _players.at(client->GetID()).index();
			msg_request_exchange << data_receiver_request_exchange << data_sender_request_exchange;
			MessageClient(*receiver_client, msg_request_exchange);
		}

		break;
	}

	case MSG_FROM::CLIENT_ACCEPT_EXCHANGE_RES: //! maybe remove it to simplicity ERROR LOGIC
	{
		Data_Country data_sender_accept_exchange;
		Data_Country data_receiver_accept_exchange;
		msg >> data_sender_accept_exchange >> data_receiver_accept_exchange;
		auto sender_client{
			std::find_if(
				m_deqConnections.begin(),
				m_deqConnections.end(),
				[&data_sender_accept_exchange, this](const auto &connection)
				{
					return _players.at(connection->GetID()).index() == data_sender_accept_exchange._data_index;
				})};
		if (sender_client != m_deqConnections.end())
		{
			if (_players.at(client->GetID()).activityPoints()->currentPoints() != 0 ||
				_players.at((*sender_client)->GetID()).activityPoints()->currentPoints() != 0)
			{
				_players.at(client->GetID()).activityPoints()->currentPoints(-1);
				_players.at((*sender_client)->GetID()).activityPoints()->currentPoints(-1);

				*_players.at(client->GetID()).resources() +=
					Resources(data_receiver_accept_exchange._data_resources);

				*_players.at((*sender_client)->GetID()).resources() -=
					Resources(data_sender_accept_exchange._data_resources);

				olc::net::message<MSG_FROM> msg_sender_data_country{};
				msg_sender_data_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
				msg_sender_data_country << _players.at(client->GetID()).convertToData();
				MessageAllClients(msg_sender_data_country);

				olc::net::message<MSG_FROM> msg_receiver_data_country{};
				msg_receiver_data_country.header.id = MSG_FROM::SERVER_DATA_COUNTRY;
				msg_receiver_data_country << _players.at((*sender_client)->GetID()).convertToData();
				MessageAllClients(msg_receiver_data_country);
			}
		}
		break;
	}
	}
}
