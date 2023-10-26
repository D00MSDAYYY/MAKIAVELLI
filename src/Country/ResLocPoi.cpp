#include <boost/json/src.hpp>

#include "ResLocPoi.hpp"
#include "map.hpp"
#include "country.hpp"

#include <algorithm>

using RES::Resources;

void RES::Resources::setDependices(std::shared_ptr<Country> country)
{
	_country = country;
}

int Resources::oil(int const resources)
{
	if (resources == 0)
		return _oil_resources;
	_oil_resources += resources;
	if (_oil_resources < 0)
		_oil_resources = 0;
	return 1;
}
int Resources::mineral(int const resources)
{
	if (resources == 0)
		return _mineral_resources;
	_mineral_resources += resources;
	if (_mineral_resources < 0)
		_mineral_resources = 0;
	return 1;
}
int Resources::farm(int const resources)
{
	if (resources == 0)
		return _farm_resources;
	_farm_resources += resources;
	if (_farm_resources < 0)
		_farm_resources = 0;
	return 1;
}
int Resources::industry(int const resources)
{
	if (resources == 0)
		return _industry_resources;
	_industry_resources += resources;
	if (_industry_resources < 0)
		_industry_resources = 0;
	return 1;
}

float Resources::oilCoef(float const coef)
{
	if (coef == 0)
	{
		return _oil_coef;
	}
	else
	{
		_oil_coef *= coef;
		return 1.0f;
	}
}

float Resources::mineralCoef(float const coef)
{
	if (coef == 0)
	{
		return _mineral_coef;
	}
	else
	{
		_mineral_coef *= coef;
		return 1.0;
	}
}

float Resources::farmCoef(float const coef)
{
	if (coef == 0)
	{
		return _farm_coef;
	}
	else
	{
		_farm_coef *= coef;
		return 1.0;
	}
}

float Resources::industryCoef(float const coef)
{
	if (coef == 0)
	{
		return _industry_coef;
	}
	else
	{
		_industry_coef *= coef;
		return 1.0;
	}
}

bool Resources::operator<(const Resources &r) const
{
	if (_oil_resources < r._oil_resources ||
		_mineral_resources < r._mineral_resources ||
		_farm_resources < r._farm_resources ||
		_industry_resources < r._industry_resources)
		return true;
	else
		return false;
}

bool RES::Resources::operator>(const Resources &r) const
{
	if (!(*this < r))
		return true;
	else
		return false;
}

bool RES::Resources::operator>=(const Resources &r) const
{
	if (*this > r || *this == r)
		return true;
	else
		return false;
}

bool RES::Resources::operator==(const Resources &r) const
{
	if (!(*this < r) && !(*this > r))
		return true;
	else
		return false;
}

bool Resources::operator<=(const Resources &r) const
{
	if (*this < r || *this == r)
		return true;
	else
		return false;
}

const Resources Resources::operator+(const Resources &r) const
{
	Resources result(*this);
	return std::move(Resources(std::move(result += r)));
}

const Resources &Resources::operator+=(const Resources &r)
{
	oil(r._oil_resources);
	mineral(r._mineral_resources);
	farm(r._farm_resources);
	industry(r._industry_resources);
	return *this;
}

const Resources Resources::operator-(const Resources &r) const
{
	Resources result(*this);
	return std::move(Resources(std::move(result -= r)));
}

const Resources &Resources::operator-=(const Resources &r)
{
	oil(-r._oil_resources);
	mineral(-r._mineral_resources);
	farm(-r._farm_resources);
	industry(-r._industry_resources);
	return *this;
}

const Resources Resources::operator*(const float &coef) const
{
	Resources result(*this);
	return std::move(Resources(std::move(result *= coef)));
}

const Resources &Resources::operator*=(const float &coef)
{
	_oil_resources *= coef;
	_mineral_resources *= coef;
	_farm_resources *= coef;
	_industry_resources *= coef;
	return *this;
}

const Resources Resources::operator/(const float &coef) const
{
	Resources result(*this);
	return std::move(Resources(std::move(result /= coef)));
}

const Resources &Resources::operator/=(const float &coef)
{
	_oil_resources /= coef;
	_mineral_resources /= coef;
	_farm_resources /= coef;
	_industry_resources /= coef;
	return *this;
}

void Resources::operator<<(olc::net::message<MSG_FROM> msg)
{
	uint32_t ores{};
	uint32_t mres{};
	uint32_t fres{};
	uint32_t ires{};
	msg >> ires >> fres >> mres >> ores;
	_oil_resources = ores;
	_mineral_resources = mres;
	_farm_resources = fres;
	_industry_resources = ires;
}

void Resources::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_oil_resources)
		<< uint32_t(_mineral_resources)
		<< uint32_t(_farm_resources)
		<< uint32_t(_industry_resources);
}

void Resources::update()
{
	_oil_resources += OIL_BASE * _oil_coef * _country.lock()->locations()->oil();
	_mineral_resources += MINERAL_BASE * _mineral_coef * _country.lock()->locations()->mineral();
	_farm_resources += FARM_BASE * _farm_coef * _country.lock()->locations()->farm();
	_industry_resources += INDUSTRY_BASE * _industry_coef * _country.lock()->locations()->industry();
}

Resources RES::tag_invoke(boost::json::value_to_tag<Resources>, boost::json::value const &jv)
{
	boost::json::object const &obj = jv.as_object();
	return Resources{boost::json::value_to<int>(obj.at("oil")),
					 boost::json::value_to<int>(obj.at("mineral")),
					 boost::json::value_to<int>(obj.at("farm")),
					 boost::json::value_to<int>(obj.at("industry"))};
}
void RES::tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Resources const &res)
{
	Resources temp = res; //! dont change this coz res must be const
	jv = {{"oil", temp.oil()},
		  {"mineral", temp.mineral()},
		  {"farm", temp.farm()},
		  {"industry", temp.industry()}};
}

using LOC::Locations;

void Locations::setDependices(std::shared_ptr<Country> country)
{
	_country = country;
}

void Locations::setDependices(std::shared_ptr<Map> map)
{
	_map = map;
}

const Locations LOC::Locations::operator+(const Locations &l) const
{
	Locations result(*this);
	return std::move(Locations{std::move(result += l)}); //! std::move
}

const Locations &LOC::Locations::operator+=(const Locations &l)
{
	for (auto &country_coord : l._country_map)
	{
		if (std::find(_country_map.begin(), _country_map.end(), country_coord) == _country_map.end())
			_country_map.push_back(country_coord);
	}
	return *this;
}

const Locations LOC::Locations::operator-(const Locations &l) const
{
	Locations result(*this);
	return std::move(Locations{std::move(result -= l)}); //! std::move
}

const Locations &LOC::Locations::operator-=(const Locations &l)
{
	for (auto &country_coord : l._country_map)
	{
		_country_map.erase(std::remove(_country_map.begin(),
									   _country_map.end(),
									   country_coord),
						   _country_map.end());
	}
	return *this;
}

std::shared_ptr<Map> LOC::Locations::map()
{
	return _map;
}

std::vector<std::pair<int, int>> LOC::Locations::country_map()
{
	return std::vector<std::pair<int, int>>();
}

int LOC::Locations::oil(std::vector<std::pair<int, int>> coords)
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
			if (_oil_loc_cost * _oil_coef <= *_country.lock()->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country.lock()->resources() -= _oil_loc_cost * _oil_coef;
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

int Locations::mineral(std::vector<std::pair<int, int>> coords)
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
			if (_mineral_loc_cost * _mineral_coef <= *_country.lock()->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country.lock()->resources() -= _mineral_loc_cost * _mineral_coef;
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

int LOC::Locations::farm(std::vector<std::pair<int, int>> coords)
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
			if (_farm_loc_cost * _farm_coef <= *_country.lock()->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country.lock()->resources() -= _farm_loc_cost * _farm_coef;
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

int LOC::Locations::industry(std::vector<std::pair<int, int>> coords)
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
			if (_industry_loc_cost * _industry_coef <= *_country.lock()->resources())
			{
				if (_map->cell(coord).mapCellOwner() == this &&
					_map->find(Cell_Type::COUNTRY_AREA, coord))
				{
					*_country.lock()->resources() -= _industry_loc_cost * _industry_coef;
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

float LOC::Locations::oilCoef(float const coef)
{
	if (coef == 0)
	{
		return _oil_coef;
	}
	else
	{
		_oil_coef *= coef;
		return 1.0;
	}
}

float LOC::Locations::mineralCoef(float const coef)
{
	if (coef == 0)
	{
		return _mineral_coef;
	}
	else
	{
		_mineral_coef *= coef;
		return 1.0;
	}
}

float LOC::Locations::farmCoef(float const coef)
{
	if (coef == 0)
	{
		return _farm_coef;
	}
	else
	{
		_farm_coef *= coef;
		return 1.0;
	}
}

float Locations::industryCoef(float const coef)
{
	if (coef == 0)
	{
		return _industry_coef;
	}
	else
	{
		_industry_coef *= coef;
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
	jv = {{"oil", temp.oil()},
		  {"mineral", temp.mineral()},
		  {"farm", temp.farm()},
		  {"industry", temp.industry()}};
}

using POI::Points;

void Points::setArmyCost()
{
	switch (_army_points)
	{
	case 10:
	case 9:
		_army_points_cost = Resources{0, 100, 100, 100};
		break;
	case 8:
	case 7:
		_army_points_cost = Resources{0, 100, 100, 100};
		break;
	case 6:
	case 5:
		_army_points_cost = Resources{0, 100, 100, 100};
		break;
	case 4:
	case 3:
		_army_points_cost = Resources{0, 100, 100, 100};
		break;
	case 2:
	case 1:
	case 0:
		_army_points_cost = Resources{0, 100, 100, 100};
		break;
	default:
		break;
	}
}

void Points::setScienceCost()
{
	switch (_science_points)
	{
	case 10:
	case 9:
		_science_points_cost = Resources{0, 100, 100, 100};
		break;
	case 8:
	case 7:
		_science_points_cost = Resources{0, 100, 100, 100};
		break;
	case 6:
	case 5:
		_science_points_cost = Resources{0, 100, 100, 100};
		break;
	case 4:
	case 3:
		_science_points_cost = Resources{0, 100, 100, 100};
		break;
	case 2:
	case 1:
	case 0:
		_science_points_cost = Resources{0, 100, 100, 100};
		break;
	default:
		break;
	}
}

void Points::setOilCost()
{
	switch (_oil_points)
	{
	case 10:
	case 9:
		_oil_points_cost = Resources{0, 100, 100, 100};
		break;
	case 8:
	case 7:
		_oil_points_cost = Resources{0, 100, 100, 100};
		break;
	case 6:
	case 5:
		_oil_points_cost = Resources{0, 100, 100, 100};
		break;
	case 4:
	case 3:
		_oil_points_cost = Resources{0, 100, 100, 100};
		break;
	case 2:
	case 1:
	case 0:
		_oil_points_cost = Resources{0, 100, 100, 100};
		break;
	default:
		break;
	}
}

void Points::setMineralCost()
{
	switch (_mineral_points)
	{
	case 10:
	case 9:
		_mineral_points_cost = Resources{0, 100, 100, 100};
		break;
	case 8:
	case 7:
		_mineral_points_cost = Resources{0, 100, 100, 100};
		break;
	case 6:
	case 5:
		_mineral_points_cost = Resources{0, 100, 100, 100};
		break;
	case 4:
	case 3:
		_mineral_points_cost = Resources{0, 100, 100, 100};
		break;
	case 2:
	case 1:
	case 0:
		_mineral_points_cost = Resources{0, 100, 100, 100};
		break;
	default:
		break;
	}
}

void Points::setFarmCost()
{
	switch (_farm_points)
	{
	case 10:
	case 9:
		_farm_points_cost = Resources{0, 100, 100, 100};
		break;
	case 8:
	case 7:
		_farm_points_cost = Resources{0, 100, 100, 100};
		break;
	case 6:
	case 5:
		_farm_points_cost = Resources{0, 100, 100, 100};
		break;
	case 4:
	case 3:
		_farm_points_cost = Resources{0, 100, 100, 100};
		break;
	case 2:
	case 1:
	case 0:
		_farm_points_cost = Resources{0, 100, 100, 100};
		break;
	default:
		break;
	}
}

void Points::setIndustryCost()
{
	switch (_industry_points)
	{
	case 10:
	case 9:
		_industry_points_cost = Resources{0, 100, 100, 100};
		break;
	case 8:
	case 7:
		_industry_points_cost = Resources{0, 100, 100, 100};
		break;
	case 6:
	case 5:
		_industry_points_cost = Resources{0, 100, 100, 100};
		break;
	case 4:
	case 3:
		_industry_points_cost = Resources{0, 100, 100, 100};
		break;
	case 2:
	case 1:
	case 0:
		_industry_points_cost = Resources{0, 100, 100, 100};
		break;
	default:
		break;
	}
}

void Points::setAllCost()
{
	setArmyCost();
	setScienceCost();
	setOilCost();
	setMineralCost();
	setFarmCost();
	setIndustryCost();
}

void POI::Points::setDependices(std::shared_ptr<Country> country)
{
	_country = country;
}

int Points::army(int const points)
{
	if (points == 0)
		return _army_points;
	if (points < 0)
	{
		_army_points += points;
		if (_army_points < 0)
			_army_points = 0;
		setArmyCost();
		return 0;
	}
	bool isChanged = false;
	while (_army_points < MAX_ARMY_POINTS &&
		   _army_points_cost * _army_coef <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _army_points_cost * _army_coef;
		++_army_points;
		isChanged = true;
		setArmyCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::science(int const points)
{
	if (points == 0)
		return _science_points;
	if (points < 0)
	{
		_science_points += points;
		if (_science_points < 0)
			_science_points = 0;
		setScienceCost();
		return 0;
	}
	bool isChanged = false;
	while (_science_points < MAX_SCIENCE_POINTS &&
		   _science_points_cost * _science_coef <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _science_points_cost * _science_coef;
		++_science_points;
		isChanged = true;
		setScienceCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::oil(int const points)
{
	if (points == 0)
		return _oil_points;
	if (points < 0)
	{
		_oil_points += points;
		if (_oil_points < 0)
			_oil_points = 0;
		setOilCost();
		return 0;
	}
	bool isChanged = false;
	while (_oil_points < MAX_OIL_POINTS &&
		   _oil_points_cost * _oil_coef <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _oil_points_cost * _oil_coef;
		++_oil_points;
		isChanged = true;
		setOilCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::mineral(int const points)
{
	if (points == 0)
		return _mineral_points;
	if (points < 0)
	{
		_mineral_points += points;
		if (_mineral_points < 0)
			_mineral_points = 0;
		setMineralCost();
		return 0;
	}
	bool isChanged = false;
	while (_mineral_points < MAX_MINERAL_POINTS &&
		   _mineral_points_cost * _mineral_coef <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _mineral_points_cost * _mineral_coef;
		++_mineral_points;
		isChanged = true;
		setMineralCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::farm(int const points)
{
	if (points == 0)
		return _farm_points;
	if (points < 0)
	{
		_farm_points += points;
		if (_farm_points < 0)
			_farm_points = 0;
		setFarmCost();
		return 0;
	}
	bool isChanged = false;
	while (_farm_points < MAX_FARM_POINTS &&
		   _farm_points_cost * _farm_coef <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _farm_points_cost * _farm_coef;
		++_farm_points;
		isChanged = true;
		setFarmCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::industry(int const points)
{
	if (points == 0)
		return _industry_points;
	if (points < 0)
	{
		_industry_points += points;
		if (_industry_points < 0)
			_industry_points = 0;
		setIndustryCost();
		return 0;
	}
	bool isChanged = false;
	while (_industry_points < MAX_INDUSTRY_POINTS &&
		   _industry_points_cost * _industry_coef <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _industry_points_cost * _industry_coef;
		++_industry_points;
		isChanged = true;
		setIndustryCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

float Points::armyCoef(float const coef)
{
	if (coef == 0)
	{
		return _army_coef;
	}
	else
	{
		_army_coef *= coef;
		return 1.0;
	}
}

float Points::scienceCoef(float const coef)
{
	if (coef == 0)
	{
		return _science_coef;
	}
	else
	{
		_science_coef *= coef;
		return 1.0;
	}
}

float Points::oilCoef(float const coef)
{
	if (coef == 0)
	{
		return _oil_coef;
	}
	else
	{
		_oil_coef *= coef;
		return 1.0;
	}
}

float Points::mineralCoef(float const coef)
{
	if (coef == 0)
	{
		return _mineral_coef;
	}
	else
	{
		_mineral_coef *= coef;
		return 1.0;
	}
}

float Points::farmCoef(float const coef)
{
	if (coef == 0)
	{
		return _farm_coef;
	}
	else
	{
		_farm_coef *= coef;
		return 1.0;
	}
}

float Points::industryCoef(float const coef)
{
	if (coef == 0)
	{
		return _industry_coef;
	}
	else
	{
		_industry_coef *= coef;
		return 1.0;
	}
}

float Points::allCoef(float const coef)
{
	if (coef == 0)
	{
		return _industry_coef;
	}
	else
	{
		_industry_coef *= coef;
		return 1.0;
	}
}

bool Points::operator<(const Points &p) const
{
	if (_army_points < p._army_points ||
		_science_points < p._science_points ||
		_oil_points < p._oil_points ||
		_mineral_points < p._mineral_points ||
		_farm_points < p._farm_points ||
		_industry_points < p._industry_points)
		return true;
	else
		return false;
}

bool Points::operator<=(const Points &p) const
{
	if (*this < p || (!(*this < p) && !(p < *this)))
		return true;
	else
		return false;
}

bool POI::Points::operator>(const Points &p) const
{
	if (!(*this < p))
		return true;
	else
		return false;
}

bool POI::Points::operator>=(const Points &p) const
{
	if (*this > p || *this == p)
		return true;
	else
		return false;
}

bool POI::Points::operator==(const Points &p) const
{
	if (!(*this < p) && !(*this > p))
		return true;
	else
		return false;
}

const Points Points::operator+(const Points &p) const
{
	Points result(*this);
	return std::move(Points{std::move(result += p)});
}

const Points &Points::operator+=(const Points &p)
{
	army(p._army_points);
	science(p._science_points);
	oil(p._oil_points);
	mineral(p._mineral_points);
	farm(p._farm_points);
	industry(p._industry_points);
	return *this;
}

const Points Points::operator-(const Points &p) const
{
	Points result(*this);
	return Points(result -= p);
}

const Points &Points::operator-=(const Points &p)
{
	army(-p._army_points);
	science(-p._science_points);
	oil(-p._oil_points);
	mineral(-p._mineral_points);
	farm(-p._farm_points);
	industry(-p._industry_points);
	return *this;
}

const Points Points::operator*(const float &coef) const
{
	Points result(*this);
	return Points(result *= coef);
}

const Points &Points::operator*=(const float &coef)
{
	_army_points *= coef;
	_science_points *= coef;
	_oil_points *= coef;
	_mineral_points *= coef;
	_farm_points *= coef;
	_industry_points *= coef;
	return *this;
}

void Points::operator<<(olc::net::message<MSG_FROM> msg)
{
	uint32_t ipoi{};
	uint32_t fpoi{};
	uint32_t mpoi{};
	uint32_t opoi{};
	uint32_t spoi{};
	uint32_t apoi{};
	msg >> ipoi >> fpoi >> mpoi >> opoi >> spoi >> apoi;
	_army_points = apoi;
	_science_points = spoi;
	_oil_points = opoi;
	_mineral_points = mpoi;
	_farm_points = fpoi;
	_industry_points = ipoi;
}

void Points::operator>>(olc::net::message<MSG_FROM> msg)
{
	msg << uint32_t(_army_points)
		<< uint32_t(_science_points)
		<< uint32_t(_oil_points)
		<< uint32_t(_mineral_points)
		<< uint32_t(_farm_points)
		<< uint32_t(_industry_points);
}

Points POI::tag_invoke(boost::json::value_to_tag<Points>, boost::json::value const &jv)
{
	boost::json::object const &obj = jv.as_object();
	return Points{boost::json::value_to<int>(obj.at("army")),
				  boost::json::value_to<int>(obj.at("science")),
				  boost::json::value_to<int>(obj.at("oil")),
				  boost::json::value_to<int>(obj.at("mineral")),
				  boost::json::value_to<int>(obj.at("farm")),
				  boost::json::value_to<int>(obj.at("industry"))};
}
void POI::tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Points const &p)
{
	Points temp = p; //! dont change this coz res must be const
	jv = {{"army", temp.army()},
		  {"science", temp.science()},
		  {"oil", temp.oil()},
		  {"mineral", temp.mineral()},
		  {"farm", temp.farm()},
		  {"industry", temp.industry()}};
}

void Locations::operator<<(olc::net::message<MSG_FROM> msg)
{
	uint32_t size{};
	msg >> size;
	uint32_t x;
	uint32_t y;
	for (int i{0}; i < size; ++i)
	{
		msg >> x >> y;
		_country_map.push_back({x, y});
	}
}

void Locations::operator>>(olc::net::message<MSG_FROM> msg)
{
	for (auto &[x, y] : _country_map)
	{
		msg << uint32_t(y) << uint32_t(x);
	}
	msg << uint32_t(_country_map.size());
}
