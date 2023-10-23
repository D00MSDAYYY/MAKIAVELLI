#include "player_client.hpp"
#include "country.hpp"
#include "ResLocPoi.hpp"

#include "game_server.hpp"
#include "card.hpp"
#include "card_bank.hpp"

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
