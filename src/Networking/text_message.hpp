#include <string>
#include "game_network.hpp"

class Text_Message
{
public:
	std::string _data{};
	int _index{};
	void operator<<(olc::net::message<MSG_FROM>& msg);
	void operator>>(olc::net::message<MSG_FROM>& msg);
};