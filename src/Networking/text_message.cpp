#include "text_message.hpp"

void Text_Message::operator<<(olc::net::message<MSG_FROM> msg)
{
	uint32_t size{};
	msg >> size;
	uint32_t ch{};
	for (int i{0}; i < size; ++i)
	{
		msg >> ch;
		_data.push_back(ch); //TODO! is it in reverse order?
	}
	msg >> _index;
}

void Text_Message::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_index);
	for (auto &ch : _data)
	{
		msg << uint32_t(ch);
	}
	msg << uint32_t(_data.size());
}
