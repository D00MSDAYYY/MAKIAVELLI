#include "country.hpp"
#include "locations.hpp"

using LOC::Locations;

void Locations::setDependices(Country *country)
{

	_country = country;
	std::cerr << "set loc dep " << _country->index() << " " << _country << std::endl;
}
LOC::Locations::~Locations()
{
	std::cerr << "locations destr " << _country->index() << " " << _country << std::endl;
}
void Locations::setDependices(std::shared_ptr<Map> map)
{
	_map = map;
}

const Locations Locations::operator+(const std::vector<std::pair<int, int>> country_map) const
{
	Locations result(*this);
	return std::move(Locations{std::move(result += country_map)}); //! std::move
}

const Locations &Locations::operator+=(const std::vector<std::pair<int, int>> country_map)
{
	for (auto &country_coord : _country_map)
	{
		if (std::find(_country_map.begin(), _country_map.end(), country_coord) == _country_map.end())
			_country_map.push_back(country_coord);
	}
	return *this;
}

const Locations Locations::operator-(const std::vector<std::pair<int, int>> country_map) const
{
	Locations result(*this);
	return std::move(Locations{std::move(result -= country_map)}); //! std::move
}

const Locations &Locations::operator-=(const std::vector<std::pair<int, int>> country_map)
{
	for (auto &country_coord : _country_map)
	{
		_country_map.erase(std::remove(_country_map.begin(),
									   _country_map.end(),
									   country_coord),
						   _country_map.end());
	}
	return *this;
}

std::shared_ptr<Map> Locations::map()
{
	return _map;
}

std::vector<std::pair<int, int>> Locations::country_map()
{
	return std::vector<std::pair<int, int>>();
}

int Locations::oilNum(std::vector<std::pair<int, int>> coords)
{
	if (coords.size() == 0)
	{
		int count{};
		for (auto &country_coord : _country_map)
		{
			if (_map->find(Cell_Type::OIL, country_coord))
				++count;
		}
		return count;
	}
	else
	{
		bool isChanged{false};
		for (auto &coord : coords)
		{
			if (_oil_loc_cost * _oil_coef_cost <= *_country->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country->resources() -= _oil_loc_cost * _oil_coef_cost;
					_map->cell(coord).mapCellOwner(this);
					_map->cell(coord).mapCellType(Cell_Type::OIL);
					isChanged = true;
				}
			}
			else
			{
				break;
			}
		}
		return isChanged;
	}
}

int Locations::mineralNum(std::vector<std::pair<int, int>> coords)
{
	if (coords.size() == 0)
	{
		int count{};
		for (auto &country_coord : _country_map)
		{
			if (_map->find(Cell_Type::MINERAL, country_coord))
				++count;
		}
		return count;
	}
	else
	{
		bool isChanged{false};
		for (auto &coord : coords)
		{
			if (_mineral_loc_cost * _mineral_coef_cost <= *_country->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country->resources() -= _mineral_loc_cost * _mineral_coef_cost;
					_map->cell(coord).mapCellOwner(this);
					_map->cell(coord).mapCellType(Cell_Type::MINERAL);
					isChanged = true;
				}
			}
			else
			{
				break;
			}
		}
		return isChanged;
	}
}

int Locations::farmNum(std::vector<std::pair<int, int>> coords)
{
	if (coords.size() == 0)
	{
		int count{};
		for (auto &country_coord : _country_map)
		{
			if (_map->find(Cell_Type::FARM, country_coord))
				++count;
		}
		return count;
	}
	else
	{
		bool isChanged{false};
		for (auto &coord : coords)
		{
			if (_farm_loc_cost * _farm_coef_cost <= *_country->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country->resources() -= _farm_loc_cost * _farm_coef_cost;
					_map->cell(coord).mapCellOwner(this);
					_map->cell(coord).mapCellType(Cell_Type::FARM);
					isChanged = true;
				}
			}
			else
			{
				break;
			}
		}
		return isChanged;
	}
}

int Locations::industryNum(std::vector<std::pair<int, int>> coords)
{

	if (coords.size() == 0)
	{
		int count{};
		for (auto &country_coord : _country_map)
		{
			if (_map->find(Cell_Type::INDUSTRY, country_coord))
				++count;
		}
		return count;
	}
	else
	{
		bool isChanged{false};
		for (auto &coord : coords)
		{
			if (_industry_loc_cost * _industry_coef_cost <= *_country->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country->resources() -= _industry_loc_cost * _industry_coef_cost;
					_map->cell(coord).mapCellOwner(this);
					_map->cell(coord).mapCellType(Cell_Type::INDUSTRY);
					isChanged = true;
				}
			}
			else
			{
				break;
			}
		}
		return isChanged;
	}
}

float Locations::oilCoef(float const coef)
{
	if (coef == 0)
	{
		return _oil_coef_cost;
	}
	else
	{
		_oil_coef_cost *= coef;
		return 1.0;
	}
}

float Locations::mineralCoef(float const coef)
{
	if (coef == 0)
	{
		return _mineral_coef_cost;
	}
	else
	{
		_mineral_coef_cost *= coef;
		return 1.0;
	}
}

float Locations::farmCoef(float const coef)
{
	if (coef == 0)
	{
		return _farm_coef_cost;
	}
	else
	{
		_farm_coef_cost *= coef;
		return 1.0;
	}
}

float Locations::industryCoef(float const coef)
{
	if (coef == 0)
	{
		return _industry_coef_cost;
	}
	else
	{
		_industry_coef_cost *= coef;
		return 1.0;
	}
}

float Locations::allCoef(float const coef)
{
	oilCoef(coef);
	mineralCoef(coef);
	farmCoef(coef);
	industryCoef(coef);

	return 1.0f;
}

Locations LOC::tag_invoke(boost::json::value_to_tag<Locations>, boost::json::value const &jv)
{
	boost::json::object const &obj = jv.as_object();

	std::vector<std::pair<int, int>> country_map;
	country_map.resize(boost::json::value_to<int>(obj.at("country map")));
	return Locations{country_map};
}
void LOC::tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Locations const &p)
{
	Locations temp = p; //! dont change this coz loc must be const
	jv = {{"oil", temp.oilNum()},
		  {"mineral", temp.mineralNum()},
		  {"farm", temp.farmNum()},
		  {"industry", temp.industryNum()}};
}