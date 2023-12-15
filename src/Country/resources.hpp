#pragma once
#include <boost/json.hpp>
#include <memory>

class Country;

namespace RES
{
class Resources
{
private:
    Country*         _country{nullptr};

    int              _oil_resources{};
    int              _mineral_resources{};
    int              _farm_resources{};
    int              _industry_resources{};

    float            _oil_coef{1.0};  // changes coef of producing resources in countries
    float            _mineral_coef{1.0};
    float            _farm_coef{1.0};
    float            _industry_coef{1.0};

    static const int OIL_BASE{};
    static const int MINERAL_BASE{};
    static const int FARM_BASE{};
    static const int INDUSTRY_BASE{};

public:
    Resources() {}

    Resources(int oil, int mineral, int farm, int industry)
        : _oil_resources{oil},
          _mineral_resources{mineral},
          _farm_resources{farm},
          _industry_resources{industry}
    {
    }

    ~Resources();

    Resources&
    setCountry(Country* country);

    int
    oilNum(const int resources = 0);
    int
    mineralNum(const int resources = 0);
    int
    farmNum(const int resources = 0);
    int
    industryNum(const int resources = 0);

    float
    oilCoef(const float coef = 0);
    float
    mineralCoef(const float coef = 0);
    float
    farmCoef(const float coef = 0);
    float
    industryCoef(const float coef = 0);

    void
    update();

    bool
    operator<(const Resources& r) const;
    bool
    operator<=(const Resources& r) const;
    bool
    operator>(const Resources& r) const;
    bool
    operator>=(const Resources& r) const;
    bool
    operator==(const Resources& r) const;

    const Resources
    operator+(const Resources& r) const;
    const Resources&
    operator+=(const Resources& r);
    const Resources
    operator-(const Resources& r) const;
    const Resources&
    operator-=(const Resources& r);
    const Resources
    operator*(const float& coef) const;
    const Resources&
    operator*=(const float& coef);
    const Resources
    operator/(const float& coef) const;
    const Resources&
    operator/=(const float& coef);

    void
    operator<<(olc::net::message<MSG_FROM>& msg);
    void
    operator>>(olc::net::message<MSG_FROM>& msg);
};

Resources
tag_invoke(boost::json::value_to_tag<Resources>, const boost::json::value& jv);
void
tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const Resources& res);
}  // namespace RES
