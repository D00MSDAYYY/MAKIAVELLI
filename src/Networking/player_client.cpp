#include "player_client.hpp"
#include "country.hpp"
#include "ResLocPoi.hpp"

#include "game_server.hpp"
#include "card.hpp"
#include "card_bank.hpp"

void Player_Client::OnMessage(olc::net::message<MSG_FROM> &msg)
{
	switch(msg.header.id)
	{
		
		case MSG_FROM::SERVER_DATA_COUNTRY:
		{
			Data_Country data_country;
			msg >> data_country;
			_countries[data_country._data_index] = data_country;
			break;
		}
		case MSG_FROM::SERVER_NEXT_TURN:
		{
			Data_Country data_country;
			msg >> data_country;
			_countries[data_country._data_index] = data_country;
			break;
		}
		case MSG_FROM::SERVER_HANDSHAKE:
		{
			Data_Country data_this_country;
			msg >> data_this_country;
			_this_country_index = data_this_country._data_index;
			_countries[data_this_country._data_index] = data_this_country;
			break;
		}
		case MSG_FROM::SERVER_REQUEST_EXCHANGE_RES:
		{
			Data_Country data_sender_request_exchange;
			Data_Country data_receiver_request_exchange;
			msg >> data_sender_request_exchange >> data_receiver_request_exchange;
			// TODO! here displaying the offer to the client and then accept/ignore it
			if(/*accept = true */42)
			{
				olc::net::message<MSG_FROM> msg_accept_exchange{msg};
				msg_accept_exchange.header.id = MSG_FROM::CLIENT_ACCEPT_EXCHANGE_RES;
				Send(msg_accept_exchange);
			}
			break;
		}
	}
}

Player_Client::Player_Client(std::string address)
{
	// Connect(boost::tcp::ip::address::from_string("127.0.0.1"), )
}

void Player_Client::buyPoints(SCOPE scope, const int points)
{
	if (points > 0)
	{
		switch (scope)
		{
		case SCOPE::ARMY:
		{
			break;
		}
		case SCOPE::SCIENCE:

		{
			break;
		}
		case SCOPE::OIL:

		{
			break;
		}
		case SCOPE::MINERAL:

		{
			break;
		}
		case SCOPE::FARM:

		{
			break;
		}
		case SCOPE::INDUSTRY:

		{
			break;
		}
		case SCOPE::ALL:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void Player_Client::run(const std::string &host, const uint16_t port)
{
	Connect(host, port);

	std::mutex mtx_Redraw_Update;
	std::condition_variable cv_Redraw_Update;

	auto lambda_updating{[this, &cv_Redraw_Update, &mtx_Redraw_Update](std::stop_token stop_token)
						 {
							 while (!stop_token.stop_requested())
							 {
								 Update(-1, true); //! with true it can lead to deadlock coz wait shall never wake up
								 std::scoped_lock<std::mutex> sl(mtx_Redraw_Update);
								 cv_Redraw_Update.notify_one();
							 }
						 }};
	std::jthread thread_updating{lambda_updating};

	auto lambda_redrawing{[this, &cv_Redraw_Update, &mtx_Redraw_Update](std::stop_token stop_token)
						 {
							 while (!stop_token.stop_requested())
							 {
								 redrawInterface(); //TODO! maybe change the order in this block
								 std::unique_lock<std::mutex> ul(mtx_Redraw_Update);
								 cv_Redraw_Update.wait(ul);
							 }
						 }};
	std::jthread thread_redrawing{lambda_redrawing};

	thread_redrawing.request_stop();
	thread_updating.request_stop();
}
