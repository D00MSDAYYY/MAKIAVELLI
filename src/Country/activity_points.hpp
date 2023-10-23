#include <cstdint>
#include <atomic>

struct Data_Activity_Points
{
	uint8_t _current_points;
	uint8_t _max_points;
};
namespace ACPOI
{
	class Activity_Points
	{
	private:
		std::atomic<int> _current_points{};
		int _max_points{};

	public:
		Activity_Points( int max_p = 0);

		Data_Activity_Points convertToData();
		int currentPoints(int points = 0);
		int maxPoints(int points = 0);
	};
}