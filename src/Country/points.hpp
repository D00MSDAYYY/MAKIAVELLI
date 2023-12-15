#pragma once
#include "game_network.hpp"

#include <boost/json.hpp>
#include <memory>

class Country;

namespace POI
{
class Points
{
private:
    static const int MAX_ARMY_POINTS{10};
    static const int MAX_SCIENCE_POINTS{10};
    static const int MAX_OIL_POINTS{10};
    static const int MAX_MINERAL_POINTS{10};
    static const int MAX_FARM_POINTS{10};
    static const int MAX_INDUSTRY_POINTS{10};

    Country*         _country;

    int              _army_points{0};
    int              _science_points{0};
    int              _oil_points{0};
    int              _mineral_points{0};
    int              _farm_points{0};
    int              _industry_points{0};

    float            _army_coef_cost{1.0};
    float            _science_coef_cost{1.0};
    float            _oil_coef_cost{1.0};
    float            _mineral_coef_cost{1.0};
    float            _farm_coef_cost{1.0};
    float            _industry_coef_cost{1.0};

    RES::Resources   _army_points_cost{0, 0, 0, 0};
    RES::Resources   _science_points_cost{0, 0, 0, 0};
    RES::Resources   _oil_points_cost{0, 0, 0, 0};
    RES::Resources   _mineral_points_cost{0, 0, 0, 0};
    RES::Resources   _farm_points_cost{0, 0, 0, 0};
    RES::Resources   _industry_points_cost{0, 0, 0, 0};

    void
    setArmyCost();
    void
    setScienceCost();
    void
    setOilCost();
    void
    setMineralCost();
    void
    setFarmCost();
    void
    setIndustryCost();
    void
    setAllCost();

public:
    Points() {}

    Points(int army, int science, int oil, int mineral, int farm, int industry)
        : _army_points(army),
          _science_points(science),
          _oil_points(oil),
          _mineral_points(mineral),
          _farm_points(farm),
          _industry_points(industry)
    {
        setAllCost();
    }

    ~Points();
    Points&
    setCountry(Country* country);

    int
    armyNum(std::optional<int> points = std::nullopt);
    int
    scienceNum(std::optional<int> points = std::nullopt);
    int
    oilNum(std::optional<int> points = std::nullopt);
    int
    mineralNum(std::optional<int> points = std::nullopt);
    int
    farmNum(std::optional<int> points = std::nullopt);
    int
    industryNum(std::optional<int> points = std::nullopt);

    float
    armyCoefCost(const float coef = 0);
    float
    scienceCoefCost(const float coef = 0);
    float
    oilCoefCost(const float coef = 0);
    float
    mineralCoefCost(const float coef = 0);
    float
    farmCoefCost(const float coef = 0);
    float
    industryCoefCost(const float coef = 0);
    float
    allCoefCost(const float coef = 0);

    bool
    operator<(const Points& p) const;
    bool
    operator<=(const Points& p) const;
    bool
    operator>(const Points& p) const;
    bool
    operator>=(const Points& p) const;
    bool
    operator==(const Points& p) const;

    const Points
    operator+(const Points& p) const;
    const Points&
    operator+=(const Points& p);
    const Points
    operator-(const Points& p) const;
    const Points&
    operator-=(const Points& p);
    const Points
    operator*(const float& coef) const;
    const Points&
    operator*=(const float& coef);

    void
    operator<<(olc::net::message<MSG_FROM>& msg);
    void
    operator>>(olc::net::message<MSG_FROM>& msg);
};

Points
tag_invoke(boost::json::value_to_tag<Points>, const boost::json::value& jv);
void
tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const Points& p);
}  // namespace POI
