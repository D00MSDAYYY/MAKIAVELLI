#include "resources.hpp"

#include "country.hpp"

using RES::Resources;

Resources&
Resources::setCountry(Country* country)
{
    _country = country;
    return *this;
}

RES::Resources::~Resources() {}

int
Resources::oilNum(const int resources)
{
    if(resources == 0) return _oil_resources;
    _oil_resources += resources;
    if(_oil_resources < 0) _oil_resources = 0;
    return 1;
}

int
Resources::mineralNum(const int resources)
{
    if(resources == 0) return _mineral_resources;
    _mineral_resources += resources;
    if(_mineral_resources < 0) _mineral_resources = 0;
    return 1;
}

int
Resources::farmNum(const int resources)
{
    if(resources == 0) return _farm_resources;
    _farm_resources += resources;
    if(_farm_resources < 0) _farm_resources = 0;
    return 1;
}

int
Resources::industryNum(const int resources)
{
    if(resources == 0) return _industry_resources;
    _industry_resources += resources;
    if(_industry_resources < 0) _industry_resources = 0;
    return 1;
}

float
Resources::oilCoef(const float coef)
{
    if(coef == 0) { return _oil_coef; }
    else
    {
        _oil_coef *= coef;
        return 1.0f;
    }
}

float
Resources::mineralCoef(const float coef)
{
    if(coef == 0) { return _mineral_coef; }
    else
    {
        _mineral_coef *= coef;
        return 1.0;
    }
}

float
Resources::farmCoef(const float coef)
{
    if(coef == 0) { return _farm_coef; }
    else
    {
        _farm_coef *= coef;
        return 1.0;
    }
}

float
Resources::industryCoef(const float coef)
{
    if(coef == 0) { return _industry_coef; }
    else
    {
        _industry_coef *= coef;
        return 1.0;
    }
}

bool
Resources::operator<(const Resources& r) const
{
    if(_oil_resources < r._oil_resources || _mineral_resources < r._mineral_resources
       || _farm_resources < r._farm_resources
       || _industry_resources < r._industry_resources)
        return true;
    else
        return false;
}

bool
Resources::operator>(const Resources& r) const
{
    if(!(*this < r))
        return true;
    else
        return false;
}

bool
Resources::operator>=(const Resources& r) const
{
    if(*this > r || *this == r)
        return true;
    else
        return false;
}

bool
Resources::operator==(const Resources& r) const
{
    if(!(*this < r) && !(*this > r))
        return true;
    else
        return false;
}

bool
Resources::operator<=(const Resources& r) const
{
    if(*this < r || *this == r)
        return true;
    else
        return false;
}

const Resources
Resources::operator+(const Resources& r) const
{
    Resources result(*this);
    return std::move(Resources(std::move(result += r)));
}

const Resources&
Resources::operator+=(const Resources& r)
{
    oilNum(r._oil_resources);
    mineralNum(r._mineral_resources);
    farmNum(r._farm_resources);
    industryNum(r._industry_resources);
    return *this;
}

const Resources
Resources::operator-(const Resources& r) const
{
    Resources result(*this);
    return std::move(Resources(std::move(result -= r)));
}

const Resources&
Resources::operator-=(const Resources& r)
{
    oilNum(-r._oil_resources);
    mineralNum(-r._mineral_resources);
    farmNum(-r._farm_resources);
    industryNum(-r._industry_resources);
    return *this;
}

const Resources
Resources::operator*(const float& coef) const
{
    Resources result(*this);
    return std::move(Resources(std::move(result *= coef)));
}

const Resources&
Resources::operator*=(const float& coef)
{
    _oil_resources      *= coef;
    _mineral_resources  *= coef;
    _farm_resources     *= coef;
    _industry_resources *= coef;
    return *this;
}

const Resources
Resources::operator/(const float& coef) const
{
    Resources result(*this);
    return std::move(Resources(std::move(result /= coef)));
}

const Resources&
Resources::operator/=(const float& coef)
{
    _oil_resources      /= coef;
    _mineral_resources  /= coef;
    _farm_resources     /= coef;
    _industry_resources /= coef;
    return *this;
}

void
Resources::operator<<(olc::net::message<MSG_FROM>& msg)
{
    uint32_t ores{};
    uint32_t mres{};
    uint32_t fres{};
    uint32_t ires{};
    msg >> ires;
    msg >> fres;
    msg >> mres;
    msg >> ores;
    _oil_resources      = ores;
    _mineral_resources  = mres;
    _farm_resources     = fres;
    _industry_resources = ires;
}

void
Resources::operator>>(olc::net::message<MSG_FROM>& msg)
{
    msg << uint32_t(_oil_resources);
    msg << uint32_t(_mineral_resources);
    msg << uint32_t(_farm_resources);
    msg << uint32_t(_industry_resources);
}

void
Resources::update()
{
    // _country->CHECK();
    // _oil_resources += OIL_BASE * _oil_coef * _country->locations()->oilNum();
    // _mineral_resources += MINERAL_BASE * _mineral_coef *
    // _country->locations()->mineralNum(); _farm_resources += FARM_BASE *
    // _farm_coef * _country->locations()->farmNum(); _industry_resources +=
    // INDUSTRY_BASE * _industry_coef * _country->locations()->industryNum();
}

Resources
RES::tag_invoke(boost::json::value_to_tag<Resources>, const boost::json::value& jv)
{
    const boost::json::object& obj = jv.as_object();
    return std::move(Resources{boost::json::value_to<int>(obj.at("oil")),
                               boost::json::value_to<int>(obj.at("mineral")),
                               boost::json::value_to<int>(obj.at("farm")),
                               boost::json::value_to<int>(obj.at("industry"))});
}

void
RES::tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const Resources& res)
{
    Resources temp{res};  //! dont change this coz res must be const
    jv = {
        {"oil",      temp.oilNum()     },
        {"mineral",  temp.mineralNum() },
        {"farm",     temp.farmNum()    },
        {"industry", temp.industryNum()}
    };
}
