#pragma once
#include <boost/json.hpp>
#include <memory>

#include "map.hpp"

class Country;

namespace LOC
{
	class Locations
	{
	private:
		
		Country* _country{nullptr};
		std::shared_ptr<Map> _map;

		std::vector<std::pair<int, int>> _country_map{};

		float _oil_coef_cost{1.0};
		float _mineral_coef_cost{1.0};
		float _farm_coef_cost{1.0};
		float _industry_coef_cost{1.0};

		RES::Resources _oil_loc_cost{0, 0, 0, 0};
		RES::Resources _mineral_loc_cost{0, 0, 0, 0};
		RES::Resources _farm_loc_cost{0, 0, 0, 0};
		RES::Resources _industry_loc_cost{0, 0, 0, 0};

	public:
		Locations() {}
		Locations(std::vector<std::pair<int, int>> country_map)
			: _country_map{country_map}{}
		~Locations();

		void setDependices(Country* country);
		void setDependices(std::shared_ptr<Map> map);

		const Locations operator+(const std::vector<std::pair<int, int>> country_map ) const;
		const Locations &operator+=(const std::vector<std::pair<int, int>> country_map );
		const Locations operator-(const std::vector<std::pair<int, int>> country_map ) const;
		const Locations &operator-=(const std::vector<std::pair<int, int>> country_map );

		std::shared_ptr<Map> map();

		std::vector<std::pair<int, int>> country_map();
		int oilNum(std::vector<std::pair<int, int>> loc_coord = {});
		int mineralNum(std::vector<std::pair<int, int>> loc_coord = {});
		int farmNum(std::vector<std::pair<int, int>> loc_coord = {});
		int industryNum(std::vector<std::pair<int, int>> loc_coord = {});

		float oilCoef(float const coef = 0);
		float mineralCoef(float const coef = 0);
		float farmCoef(float const coef = 0);
		float industryCoef(float const coef = 0);
		float allCoef(float const coef);

		void operator<<(olc::net::message<MSG_FROM> msg);
		void operator>>(olc::net::message<MSG_FROM> msg);
	};
	Locations tag_invoke(boost::json::value_to_tag<Locations>, boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Locations const &p);
}
