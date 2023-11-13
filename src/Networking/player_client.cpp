#include "player_client.hpp"
#include "game_server.hpp"
#include "card.hpp"
#include "card_bank.hpp"

// void Player_Client::OnMessage(olc::net::message<MSG_FROM> &msg)
// {
// 	switch (msg.header.id)
// 	{

// 	case MSG_FROM::SERVER_DATA_COUNTRY:
// 	{
// 		Country country;
// 		country << msg;
// 		_countries[country.index()] = std::move(country);
// 		break;
// 	}

// 	case MSG_FROM::SERVER_REQUEST_EXCHANGE_RES:
// 	{
// 		Country data_sender_request_exchange;
// 		Country data_receiver_request_exchange;
// 		auto msg_copy = msg;
// 		data_sender_request_exchange << msg;
// 		data_receiver_request_exchange << msg;
// 		// TODO! GUI here displaying the offer to the client and then accept/ignore it
// 		if (/*accept = true */ 0)
// 		{
// 			msg_copy.header.id = MSG_FROM::CLIENT_ACCEPT_EXCHANGE_RES;
// 			Send(msg_copy);
// 		}
// 		break;
// 	}
// 	case MSG_FROM::SERVER_HANDSHAKE:
// 	{
// 		Country this_country;
// 		this_country << msg;
// 		_this_country_index = this_country.index();
// 		_countries[this_country.index()] = std::move(this_country);
// 		break;
// 	}
// 	}
// }



void Player_Client::buyPoints(SCOPE scope, const int points)
{
}

void Player_Client::buyLocations(SCOPE scope, std::vector<std::pair<int, int>> coords)
{
}

// void Player_Client::run(const std::string &host, const uint16_t port)
// {
// 	Connect(host, port);

// 	std::mutex mtx_Redraw_Update;
// 	std::condition_variable cv_Redraw_Update;

// 	auto lambda_updating{[this, &cv_Redraw_Update, &mtx_Redraw_Update](std::stop_token stop_token)
// 						 {
// 							 while (!stop_token.stop_requested())
// 							 {
// 								 Update(-1, true); //! with true it can lead to deadlock coz wait shall never wake up
// 								 std::scoped_lock<std::mutex> sl(mtx_Redraw_Update);
// 								 cv_Redraw_Update.notify_one();
// 							 }
// 						 }};
// 	std::jthread thread_updating{lambda_updating};

// 	auto lambda_redrawing{[this, &cv_Redraw_Update, &mtx_Redraw_Update](std::stop_token stop_token)
// 						  {
// 							  while (!stop_token.stop_requested())
// 							  {
// 								  std::unique_lock<std::mutex> ul(mtx_Redraw_Update);
// 								  cv_Redraw_Update.wait(ul);
// 							  }
// 						  }};
// 	std::jthread thread_redrawing{lambda_redrawing};

// 	thread_redrawing.request_stop();
// 	thread_updating.request_stop();
// }
