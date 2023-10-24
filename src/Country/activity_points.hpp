#include <cstdint>
#include <atomic>
#include "game_network.hpp"

namespace AC_POI
{
	class Activity_Points
	{
	private:
		std::atomic<int> _current_points{};
		int _max_points{};

	public:
		Activity_Points( int max_p = 0);

		Data_Activity_Points convertToData();
		// TODO! dont forget to add FROM_SERVER_NEW_CARD
		int currentPoints(int points = 0);
		int maxPoints(int points = 0);

		void operator<<(olc::net::message<MSG_FROM> msg);
		void operator>>(olc::net::message<MSG_FROM> msg);
	};
}