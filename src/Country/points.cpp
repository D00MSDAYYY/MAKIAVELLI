#include "country.hpp"

using POI::Points;
using RES::Resources;

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

int Points::armyNum(int const points)
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
		   _army_points_cost * _army_coef_cost <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _army_points_cost * _army_coef_cost;
		++_army_points;
		isChanged = true;
		setArmyCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::scienceNum(int const points)
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
		   _science_points_cost * _science_coef_cost <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _science_points_cost * _science_coef_cost;
		++_science_points;
		isChanged = true;
		setScienceCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::oilNum(int const points)
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
		   _oil_points_cost * _oil_coef_cost <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _oil_points_cost * _oil_coef_cost;
		++_oil_points;
		isChanged = true;
		setOilCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::mineralNum(int const points)
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
		   _mineral_points_cost * _mineral_coef_cost <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _mineral_points_cost * _mineral_coef_cost;
		++_mineral_points;
		isChanged = true;
		setMineralCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::farmNum(int const points)
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
		   _farm_points_cost * _farm_coef_cost <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _farm_points_cost * _farm_coef_cost;
		++_farm_points;
		isChanged = true;
		setFarmCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

int Points::industryNum(int const points)
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
		   _industry_points_cost * _industry_coef_cost <= *_country.lock()->resources())
	{
		*_country.lock()->resources() -= _industry_points_cost * _industry_coef_cost;
		++_industry_points;
		isChanged = true;
		setIndustryCost();
	}
	if (isChanged)
		return 1;
	return 0;
}

float Points::armyCoefCost(float const coef)
{
	if (coef == 0)
	{
		return _army_coef_cost;
	}
	else
	{
		_army_coef_cost *= coef;
		return 1.0;
	}
}

float Points::scienceCoefCost(float const coef)
{
	if (coef == 0)
	{
		return _science_coef_cost;
	}
	else
	{
		_science_coef_cost *= coef;
		return 1.0;
	}
}

float Points::oilCoefCost(float const coef)
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

float Points::mineralCoefCost(float const coef)
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

float Points::farmCoefCost(float const coef)
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

float Points::industryCoefCost(float const coef)
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

float Points::allCoefCost(float const coef)
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
	armyNum(p._army_points);
	scienceNum(p._science_points);
	oilNum(p._oil_points);
	mineralNum(p._mineral_points);
	farmNum(p._farm_points);
	industryNum(p._industry_points);
	return *this;
}

const Points Points::operator-(const Points &p) const
{
	Points result(*this);
	return Points(result -= p);
}

const Points &Points::operator-=(const Points &p)
{
	armyNum(-p._army_points);
	scienceNum(-p._science_points);
	oilNum(-p._oil_points);
	mineralNum(-p._mineral_points);
	farmNum(-p._farm_points);
	industryNum(-p._industry_points);
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
	jv = {{"army", temp.armyNum()},
		  {"science", temp.scienceNum()},
		  {"oil", temp.oilNum()},
		  {"mineral", temp.mineralNum()},
		  {"farm", temp.farmNum()},
		  {"industry", temp.industryNum()}};
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
