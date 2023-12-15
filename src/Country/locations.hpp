#pragma once
#include "map.hpp"

#include <boost/json.hpp>
#include <memory>
#include <optional>

class Country;

namespace LOC
{
class Locations
{
private:
    Country*                         _country{nullptr};
    std::shared_ptr<Map>             _map;

    std::vector<std::pair<int, int>> _country_cells_coords{};

    float                            _oil_coef_cost{1.0};
    float                            _mineral_coef_cost{1.0};
    float                            _farm_coef_cost{1.0};
    float                            _industry_coef_cost{1.0};


    RES::Resources                   _oil_loc_cost{0, 0, 0, 0};
    // TODO!  change to optional for avoiding object constructor
    RES::Resources                   _mineral_loc_cost{0, 0, 0, 0};
    RES::Resources                   _farm_loc_cost{0, 0, 0, 0};
    RES::Resources                   _industry_loc_cost{0, 0, 0, 0};

public:
    Locations(){};

    Locations(std::vector<std::pair<int, int>> country_map)
        : _country_cells_coords{country_map}
    {
    }

    ~Locations();

    Locations&
    setCountry(Country* country);

    const Locations
    operator+(const std::vector<std::pair<int, int>> country_map) const;
    const Locations&
    operator+=(const std::vector<std::pair<int, int>> country_map);
    const Locations
    operator-(const std::vector<std::pair<int, int>> country_map) const;
    const Locations&
    operator-=(const std::vector<std::pair<int, int>> country_map);

    std::shared_ptr<Map>
    map(std::optional<std::shared_ptr<Map>> map);

    std::vector<std::pair<int, int>>
    coords();

    int
    oilNum(std::optional<std::vector<std::pair<int, int>>> loc_coord = std::nullopt);
    int
    mineralNum(std::optional<std::vector<std::pair<int, int>>> loc_coord = std::nullopt);
    int
    farmNum(std::optional<std::vector<std::pair<int, int>>> loc_coord = std::nullopt);
    int
    industryNum(std::optional<std::vector<std::pair<int, int>>> loc_coord = std::nullopt);

    float
    oilCoef(std::optional<float> coef = std::nullopt);
    float
    mineralCoef(std::optional<float> coef = std::nullopt);
    float
    farmCoef(std::optional<float> coef = std::nullopt);
    float
    industryCoef(std::optional<float> coef = std::nullopt);
    float
    allCoef(const float coef);

    void
    operator<<(olc::net::message<MSG_FROM>& msg);
    void
    operator>>(olc::net::message<MSG_FROM>& msg);
};

Locations
tag_invoke(boost::json::value_to_tag<Locations>, const boost::json::value& jv);
void
tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const Locations& p);
}  // namespace LOC
