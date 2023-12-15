#include "points.hpp"

#include "country.hpp"

using POI::Points;
using RES::Resources;

void
Points::setArmyCost()
{
    switch(_army_points)
    {
        case 10 :
        case 9 : _army_points_cost = Resources{0, 100, 100, 100}; break;
        case 8 :
        case 7 : _army_points_cost = Resources{0, 100, 100, 100}; break;
        case 6 :
        case 5 : _army_points_cost = Resources{0, 100, 100, 100}; break;
        case 4 :
        case 3 : _army_points_cost = Resources{0, 100, 100, 100}; break;
        case 2 :
        case 1 :
        case 0 : _army_points_cost = Resources{0, 100, 100, 100}; break;
        default : break;
    }
}

void
Points::setScienceCost()
{
    switch(_science_points)
    {
        case 10 :
        case 9 : _science_points_cost = Resources{0, 100, 100, 100}; break;
        case 8 :
        case 7 : _science_points_cost = Resources{0, 100, 100, 100}; break;
        case 6 :
        case 5 : _science_points_cost = Resources{0, 100, 100, 100}; break;
        case 4 :
        case 3 : _science_points_cost = Resources{0, 100, 100, 100}; break;
        case 2 :
        case 1 :
        case 0 : _science_points_cost = Resources{0, 100, 100, 100}; break;
        default : break;
    }
}

void
Points::setOilCost()
{
    switch(_oil_points)
    {
        case 10 :
        case 9 : _oil_points_cost = Resources{0, 100, 100, 100}; break;
        case 8 :
        case 7 : _oil_points_cost = Resources{0, 100, 100, 100}; break;
        case 6 :
        case 5 : _oil_points_cost = Resources{0, 100, 100, 100}; break;
        case 4 :
        case 3 : _oil_points_cost = Resources{0, 100, 100, 100}; break;
        case 2 :
        case 1 :
        case 0 : _oil_points_cost = Resources{0, 100, 100, 100}; break;
        default : break;
    }
}

void
Points::setMineralCost()
{
    switch(_mineral_points)
    {
        case 10 :
        case 9 : _mineral_points_cost = Resources{0, 100, 100, 100}; break;
        case 8 :
        case 7 : _mineral_points_cost = Resources{0, 100, 100, 100}; break;
        case 6 :
        case 5 : _mineral_points_cost = Resources{0, 100, 100, 100}; break;
        case 4 :
        case 3 : _mineral_points_cost = Resources{0, 100, 100, 100}; break;
        case 2 :
        case 1 :
        case 0 : _mineral_points_cost = Resources{0, 100, 100, 100}; break;
        default : break;
    }
}

void
Points::setFarmCost()
{
    switch(_farm_points)
    {
        case 10 :
        case 9 : _farm_points_cost = Resources{0, 100, 100, 100}; break;
        case 8 :
        case 7 : _farm_points_cost = Resources{0, 100, 100, 100}; break;
        case 6 :
        case 5 : _farm_points_cost = Resources{0, 100, 100, 100}; break;
        case 4 :
        case 3 : _farm_points_cost = Resources{0, 100, 100, 100}; break;
        case 2 :
        case 1 :
        case 0 : _farm_points_cost = Resources{0, 100, 100, 100}; break;
        default : break;
    }
}

void
Points::setIndustryCost()
{
    switch(_industry_points)
    {
        case 10 :
        case 9 : _industry_points_cost = Resources{0, 100, 100, 100}; break;
        case 8 :
        case 7 : _industry_points_cost = Resources{0, 100, 100, 100}; break;
        case 6 :
        case 5 : _industry_points_cost = Resources{0, 100, 100, 100}; break;
        case 4 :
        case 3 : _industry_points_cost = Resources{0, 100, 100, 100}; break;
        case 2 :
        case 1 :
        case 0 : _industry_points_cost = Resources{0, 100, 100, 100}; break;
        default : break;
    }
}

void
Points::setAllCost()
{
    setArmyCost();
    setScienceCost();
    setOilCost();
    setMineralCost();
    setFarmCost();
    setIndustryCost();
}

Points&
Points::setCountry(Country* country)
{
    _country = country;
    return *this;
}

Points::~Points() {}

int
Points::armyNum(std::optional<int> points)
{
    if(points)
    {
        if(*points < 0)
        {
            _army_points += *points;
            if(_army_points < 0) _army_points = 0;
            setArmyCost();
            return true;
        }
        else  //! this statement holds point >= 0   and return false if points == 0
        {
            bool is_changed{false};
            for(int i{0}; i < points && _army_points < MAX_ARMY_POINTS
                          && _army_points_cost * _army_coef_cost <= _country->resources();
                ++i)
            {
                _country->resources() -= _army_points_cost * _army_coef_cost;
                ++_army_points;
                is_changed = true;
                setArmyCost();
            }
            return is_changed;
        }
    }
    else
        return _army_points;
}

int
Points::scienceNum(std::optional<int> points)
{
    if(points)
    {
        if(*points < 0)
        {
            _science_points += *points;
            if(_science_points < 0) _science_points = 0;
            setArmyCost();
            return true;
        }
        else
        {
            bool is_changed{false};
            for(int i{0};
                i < points && _science_points < MAX_SCIENCE_POINTS
                && _science_points_cost * _science_coef_cost <= _country->resources();
                ++i)
            {
                _country->resources() -= _science_points_cost * _science_coef_cost;
                ++_science_points;
                is_changed = true;
                setArmyCost();
            }
            return is_changed;
        }
    }
    else
        return _science_points;
}

int
Points::oilNum(std::optional<int> points)
{
    if(points)
    {
        if(*points < 0)
        {
            _oil_points += *points;
            if(_oil_points < 0) _oil_points = 0;
            setArmyCost();
            return true;
        }
        else
        {
            bool is_changed{false};
            for(int i{0}; i < points && _oil_points < MAX_OIL_POINTS
                          && _oil_points_cost * _oil_coef_cost <= _country->resources();
                ++i)
            {
                _country->resources() -= _oil_points_cost * _oil_coef_cost;
                ++_oil_points;
                is_changed = true;
                setArmyCost();
            }
            return is_changed;
        }
    }
    else
        return _oil_points;
}

int
Points::mineralNum(std::optional<int> points)
{
    if(points)
    {
        if(*points < 0)
        {
            _mineral_points += *points;
            if(_mineral_points < 0) _mineral_points = 0;
            setArmyCost();
            return true;
        }
        else
        {
            bool is_changed{false};
            for(int i{0};
                i < points && _mineral_points < MAX_MINERAL_POINTS
                && _mineral_points_cost * _mineral_coef_cost <= _country->resources();
                ++i)
            {
                _country->resources() -= _mineral_points_cost * _mineral_coef_cost;
                ++_mineral_points;
                is_changed = true;
                setArmyCost();
            }
            return is_changed;
        }
    }
    else
        return _mineral_points;
}

int
Points::farmNum(std::optional<int> points)
{
    if(points)
    {
        if(*points < 0)
        {
            _farm_points += *points;
            if(_farm_points < 0) _farm_points = 0;
            setArmyCost();
            return true;
        }
        else
        {
            bool is_changed{false};
            for(int i{0}; i < points && _farm_points < MAX_FARM_POINTS
                          && _farm_points_cost * _farm_coef_cost <= _country->resources();
                ++i)
            {
                _country->resources() -= _farm_points_cost * _farm_coef_cost;
                ++_farm_points;
                is_changed = true;
                setArmyCost();
            }
            return is_changed;
        }
    }
    else
        return _farm_points;
}

int
Points::industryNum(std::optional<int> points)
{
    if(points)
    {
        if(*points < 0)
        {
            _industry_points += *points;
            if(_industry_points < 0) _industry_points = 0;
            setArmyCost();
            return true;
        }
        else
        {
            bool is_changed{false};
            for(int i{0};
                i < points && _industry_points < MAX_INDUSTRY_POINTS
                && _industry_points_cost * _industry_coef_cost <= _country->resources();
                ++i)
            {
                _country->resources() -= _industry_points_cost * _industry_coef_cost;
                ++_industry_points;
                is_changed = true;
                setArmyCost();
            }
            return is_changed;
        }
    }
    else
        return _industry_points;
}

float
Points::armyCoefCost(const float coef)
{
    if(coef == 0) { return _army_coef_cost; }
    else
    {
        _army_coef_cost *= coef;
        return 1.0;
    }
}

float
Points::scienceCoefCost(const float coef)
{
    if(coef == 0) { return _science_coef_cost; }
    else
    {
        _science_coef_cost *= coef;
        return 1.0;
    }
}

float
Points::oilCoefCost(const float coef)
{
    if(coef == 0) { return _oil_coef_cost; }
    else
    {
        _oil_coef_cost *= coef;
        return 1.0;
    }
}

float
Points::mineralCoefCost(const float coef)
{
    if(coef == 0) { return _mineral_coef_cost; }
    else
    {
        _mineral_coef_cost *= coef;
        return 1.0;
    }
}

float
Points::farmCoefCost(const float coef)
{
    if(coef == 0) { return _farm_coef_cost; }
    else
    {
        _farm_coef_cost *= coef;
        return 1.0;
    }
}

float
Points::industryCoefCost(const float coef)
{
    if(coef == 0) { return _industry_coef_cost; }
    else
    {
        _industry_coef_cost *= coef;
        return 1.0;
    }
}

float
Points::allCoefCost(const float coef)
{
    if(coef == 0) { return _industry_coef_cost; }
    else
    {
        _industry_coef_cost *= coef;
        return 1.0;
    }
}

bool
Points::operator<(const Points& p) const
{
    if(_army_points < p._army_points || _science_points < p._science_points
       || _oil_points < p._oil_points || _mineral_points < p._mineral_points
       || _farm_points < p._farm_points || _industry_points < p._industry_points)
        return true;
    else
        return false;
}

bool
Points::operator<=(const Points& p) const
{
    if(*this < p || (!(*this < p) && !(p < *this)))
        return true;
    else
        return false;
}

bool
POI::Points::operator>(const Points& p) const
{
    if(!(*this < p))
        return true;
    else
        return false;
}

bool
POI::Points::operator>=(const Points& p) const
{
    if(*this > p || *this == p)
        return true;
    else
        return false;
}

bool
POI::Points::operator==(const Points& p) const
{
    if(!(*this < p) && !(*this > p))
        return true;
    else
        return false;
}

const Points
Points::operator+(const Points& p) const
{
    Points result(*this);
    return std::move(Points{std::move(result += p)});
}

const Points&
Points::operator+=(const Points& p)
{
    armyNum(p._army_points);
    scienceNum(p._science_points);
    oilNum(p._oil_points);
    mineralNum(p._mineral_points);
    farmNum(p._farm_points);
    industryNum(p._industry_points);
    return *this;
}

const Points
Points::operator-(const Points& p) const
{
    Points result(*this);
    return Points(result -= p);
}

const Points&
Points::operator-=(const Points& p)
{
    armyNum(-p._army_points);
    scienceNum(-p._science_points);
    oilNum(-p._oil_points);
    mineralNum(-p._mineral_points);
    farmNum(-p._farm_points);
    industryNum(-p._industry_points);
    return *this;
}

const Points
Points::operator*(const float& coef) const
{
    Points result(*this);
    return Points(result *= coef);
}

const Points&
Points::operator*=(const float& coef)
{
    _army_points     *= coef;
    _science_points  *= coef;
    _oil_points      *= coef;
    _mineral_points  *= coef;
    _farm_points     *= coef;
    _industry_points *= coef;
    return *this;
}

void
Points::operator<<(olc::net::message<MSG_FROM>& msg)
{
    uint32_t ipoi{0};
    uint32_t fpoi{0};
    uint32_t mpoi{0};
    uint32_t opoi{0};
    uint32_t spoi{0};
    uint32_t apoi{0};
    msg >> ipoi;
    msg >> fpoi;
    msg >> mpoi;
    msg >> opoi;
    msg >> spoi;
    msg >> apoi;
    _army_points     = apoi;
    _science_points  = spoi;
    _oil_points      = opoi;
    _mineral_points  = mpoi;
    _farm_points     = fpoi;
    _industry_points = ipoi;
}

void
Points::operator>>(olc::net::message<MSG_FROM>& msg)
{
    msg << uint32_t(_army_points) << uint32_t(_science_points) << uint32_t(_oil_points)
        << uint32_t(_mineral_points) << uint32_t(_farm_points)
        << uint32_t(_industry_points);
}

Points
POI::tag_invoke(boost::json::value_to_tag<Points>, const boost::json::value& jv)
{
    const boost::json::object& obj = jv.as_object();
    return Points{boost::json::value_to<int>(obj.at("army")),
                  boost::json::value_to<int>(obj.at("science")),
                  boost::json::value_to<int>(obj.at("oil")),
                  boost::json::value_to<int>(obj.at("mineral")),
                  boost::json::value_to<int>(obj.at("farm")),
                  boost::json::value_to<int>(obj.at("industry"))};
}

void
POI::tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const Points& p)
{
    Points temp = p;  //! dont change this coz res must be const
    jv          = {
        {"army",     temp.armyNum()    },
        {"science",  temp.scienceNum() },
        {"oil",      temp.oilNum()     },
        {"mineral",  temp.mineralNum() },
        {"farm",     temp.farmNum()    },
        {"industry", temp.industryNum()}
    };
}

void
Locations::operator<<(olc::net::message<MSG_FROM>& msg)
{
    uint32_t size{0};
    msg >> size;
    uint32_t x{0};
    uint32_t y{0};
    for(int i{0}; i < size; ++i)
    {
        msg >> x;
        msg >> y;
        _country_cells_coords.push_back({x, y});
    }
}

void
Locations::operator>>(olc::net::message<MSG_FROM>& msg)
{
    for(auto& [x, y]: _country_cells_coords)
    {
        msg << uint32_t(y);
        msg << uint32_t(x);
    }
    msg << uint32_t(_country_cells_coords.size());
}
