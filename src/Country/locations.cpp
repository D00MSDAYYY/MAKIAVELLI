#include "locations.hpp"

#include "country.hpp"

using LOC::Locations;

Locations&
Locations::setCountry(Country* country)
{
    _country = country;
    return *this;
}

LOC::Locations::~Locations() {}

const Locations
Locations::operator+(const std::vector<std::pair<int, int>> country_map) const
{
    Locations result(*this);
    return std::move(Locations{std::move(result += country_map)});  //! std::move
}

const Locations&
Locations::operator+=(const std::vector<std::pair<int, int>> country_map)
{
    for(auto& country_coord: _country_cells_coords)
    {
        if(std::find(
               _country_cells_coords.begin(), _country_cells_coords.end(), country_coord)
           == _country_cells_coords.end())
            _country_cells_coords.push_back(country_coord);
    }
    return *this;
}

const Locations
Locations::operator-(const std::vector<std::pair<int, int>> country_map) const
{
    Locations result(*this);
    return std::move(Locations{std::move(result -= country_map)});  //! std::move
}

const Locations&
Locations::operator-=(const std::vector<std::pair<int, int>> country_map)
{
    for(auto& country_coord: _country_cells_coords)
    {
        _country_cells_coords.erase(std::remove(_country_cells_coords.begin(),
                                                _country_cells_coords.end(),
                                                country_coord),
                                    _country_cells_coords.end());
    }
    return *this;
}

std::shared_ptr<Map>
LOC::Locations::map(std::optional<std::shared_ptr<Map>> map)
{
    if(map) _map = *map;
    return _map;
}

std::vector<std::pair<int, int>>
LOC::Locations::coords()
{
    return std::vector<std::pair<int, int>>();
}

int
Locations::oilNum(std::optional<std::vector<std::pair<int, int>>> cells)
{
    if(cells)
    {
        bool is_changed{false};
        for(auto& coord: *cells)
        {
            if(_oil_loc_cost * _oil_coef_cost <= _country->resources())
            {
                if(_map->cell(coord).mapCellOwner() == this
                   && _map->find(Cell_Type::COUNTRY_AREA, coord))
                {
                    _country->resources() -= _oil_loc_cost * _oil_coef_cost;
                    _map->cell(coord).mapCellOwner(this);
                    _map->cell(coord).mapCellType(Cell_Type::OIL);
                    is_changed = true;
                }
            }
            else
                break;
        }
        return is_changed;
    }
    else
    {
        int count{0};
        for(auto& country_coord: _country_cells_coords)
        {
            if(_map->find(Cell_Type::OIL, country_coord)) ++count;
        }
        return count;
    }
}

int
Locations::mineralNum(std::optional<std::vector<std::pair<int, int>>> cells)
{
    if(cells)
    {
        bool is_changed{false};
        for(auto& coord: *cells)
        {
            if(_mineral_loc_cost * _mineral_coef_cost <= _country->resources())
            {
                if(_map->cell(coord).mapCellOwner() == this
                   && _map->find(Cell_Type::COUNTRY_AREA, coord))
                {
                    _country->resources() -= _mineral_loc_cost * _mineral_coef_cost;
                    _map->cell(coord).mapCellOwner(this);
                    _map->cell(coord).mapCellType(Cell_Type::MINERAL);
                    is_changed = true;
                }
            }
            else
                break;
        }
        return is_changed;
    }
    else
    {
        int count{0};
        for(auto& country_coord: _country_cells_coords)
        {
            if(_map->find(Cell_Type::MINERAL, country_coord)) ++count;
        }
        return count;
    }
}

int
Locations::farmNum(std::optional<std::vector<std::pair<int, int>>> cells)
{
    if(cells)
    {
        bool is_changed{false};
        for(auto& coord: *cells)
        {
            if(_farm_loc_cost * _farm_coef_cost <= _country->resources())
            {
                if(_map->cell(coord).mapCellOwner() == this
                   && _map->find(Cell_Type::COUNTRY_AREA, coord))
                {
                    _country->resources() -= _farm_loc_cost * _farm_coef_cost;
                    _map->cell(coord).mapCellOwner(this);
                    _map->cell(coord).mapCellType(Cell_Type::FARM);
                    is_changed = true;
                }
            }
            else
                break;
        }
        return is_changed;
    }
    else
    {
        int count{0};
        for(auto& country_coord: _country_cells_coords)
        {
            if(_map->find(Cell_Type::FARM, country_coord)) ++count;
        }
        return count;
    }
}

int
Locations::industryNum(std::optional<std::vector<std::pair<int, int>>> cells)
{
    if(cells)
    {
        bool is_changed{false};
        for(auto& coord: *cells)
        {
            if(_industry_loc_cost * _industry_coef_cost <= _country->resources())
            {
                if(_map->cell(coord).mapCellOwner() == this
                   && _map->find(Cell_Type::COUNTRY_AREA, coord))
                {
                    _country->resources() -= _industry_loc_cost * _industry_coef_cost;
                    _map->cell(coord).mapCellOwner(this);
                    _map->cell(coord).mapCellType(Cell_Type::INDUSTRY);
                    is_changed = true;
                }
            }
            else { break; }
        }
        return is_changed;
    }
    else
    {
        int count{0};
        for(auto& country_coord: _country_cells_coords)
        {
            if(_map->find(Cell_Type::INDUSTRY, country_coord)) ++count;
        }
        return count;
    }
}

float
Locations::oilCoef(std::optional<float> coef)
{
    if(coef) _oil_coef_cost *= *coef;
    return _oil_coef_cost;
}

float
Locations::mineralCoef(std::optional<float> coef)
{
    if(coef) _mineral_coef_cost *= *coef;
    return _mineral_coef_cost;
}

float
Locations::farmCoef(std::optional<float> coef)
{
    if(coef) _farm_coef_cost *= *coef;
    return _farm_coef_cost;
}

float
Locations::industryCoef(std::optional<float> coef)
{
    if(coef) _industry_coef_cost *= *coef;
    return _industry_coef_cost;
}

float
Locations::allCoef(const float coef)
{
    oilCoef(coef);
    mineralCoef(coef);
    farmCoef(coef);
    industryCoef(coef);

    return 1.0f;
}

Locations
LOC::tag_invoke(boost::json::value_to_tag<Locations>, const boost::json::value& jv)
{
    const boost::json::object&       obj = jv.as_object();
    std::vector<std::pair<int, int>> country_map;
    country_map.resize(boost::json::value_to<int>(obj.at("country map")));
    return Locations{country_map};
}

void
LOC::tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const Locations& p)
{
    Locations temp = p;  //! dont change this coz loc must be const

    temp.oilNum();

    jv = {
        {"oil",      temp.oilNum()     },
        {"mineral",  temp.mineralNum() },
        {"farm",     temp.farmNum()    },
        {"industry", temp.industryNum()}
    };
}
