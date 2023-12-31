#pragma once

#include "game_network.hpp"

#include <atomic>
#include <cstdint>

namespace AC_POI
{
class Activity_Points
{
private:
    std::atomic<int> _current_points{0};
    std::atomic<int> _max_points{0};

public:
    Activity_Points(int max_p = 0)
        : _current_points{max_p},
          _max_points{max_p}
    {
    }

    Activity_Points(const Activity_Points& acpoi);
    const Activity_Points&
    operator=(const Activity_Points& acpoi);
    ~Activity_Points(){};

    int
    currentPoints(std::optional<int> points = std::nullopt);
    int
    maxPoints(std::optional<int> points = std::nullopt);

    void
    operator<<(olc::net::message<MSG_FROM>& msg);
    void
    operator>>(olc::net::message<MSG_FROM>& msg);
};
}  // namespace AC_POI
