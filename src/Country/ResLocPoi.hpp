#pragma once

#include <boost/json.hpp>
#include <memory>
#include "game_network.hpp"

namespace POI
{
	class Points;
}
namespace LOC
{
	class Locations;
}
class Country;

namespace RES
{
	using LOC::Locations;
	using POI::Points;
	class Resources
	{
	private:
		std::weak_ptr<Country> _country;

		int _oil_resources{};
		int _mineral_resources{};
		int _farm_resources{};
		int _industry_resources{};

		float _oil_coef{1.0}; //! changes coef of producing resources in countries
		float _mineral_coef{1.0};
		float _farm_coef{1.0};
		float _industry_coef{1.0};

		static const int OIL_BASE{};
		static const int MINERAL_BASE{};
		static const int FARM_BASE{};
		static const int INDUSTRY_BASE{};

	public:
		Resources(int oil,
				  int mineral,
				  int farm,
				  int industry)
			: _oil_resources{oil},
			  _mineral_resources{mineral},
			  _farm_resources{farm},
			  _industry_resources{industry}
		{
		}

		void setDependices(std::shared_ptr<Country> country);

		int oilNum(int const resources = 0);
		int mineralNum(int const resources = 0);
		int farmNum(int const resources = 0);
		int industryNum(int const resources = 0);

		float oilCoef(float const coef = 0);
		float mineralCoef(float const coef = 0);
		float farmCoef(float const coef = 0);
		float industryCoef(float const coef = 0);

		void update();

		bool operator<(const Resources &r) const;
		bool operator<=(const Resources &r) const;
		bool operator>(const Resources &r) const;
		bool operator>=(const Resources &r) const;
		bool operator==(const Resources &r) const;

		const Resources operator+(const Resources &r) const;
		const Resources &operator+=(const Resources &r);
		const Resources operator-(const Resources &r) const;
		const Resources &operator-=(const Resources &r);
		const Resources operator*(const float &coef) const;
		const Resources &operator*=(const float &coef);
		const Resources operator/(const float &coef) const;
		const Resources &operator/=(const float &coef);

		void operator<<(olc::net::message<MSG_FROM> msg);
		void operator>>(olc::net::message<MSG_FROM> msg);
	};
	Resources tag_invoke(boost::json::value_to_tag<Resources>, boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Resources const &res);
}

namespace POI
{
	using RES::Resources;
	class Points
	{
	private:
		static const int MAX_ARMY_POINTS{10};
		static const int MAX_SCIENCE_POINTS{10};
		static const int MAX_OIL_POINTS{10};
		static const int MAX_MINERAL_POINTS{10};
		static const int MAX_FARM_POINTS{10};
		static const int MAX_INDUSTRY_POINTS{10};

		std::weak_ptr<Country> _country;

		int _army_points{};
		int _science_points{};
		int _oil_points{};
		int _mineral_points{};
		int _farm_points{};
		int _industry_points{};

		float _army_coef_cost{1.0};
		float _science_coef_cost{1.0};
		float _oil_coef_cost{1.0};
		float _mineral_coef_cost{1.0};
		float _farm_coef_cost{1.0};
		float _industry_coef_cost{1.0};

		Resources _army_points_cost{0, 0, 0, 0};
		Resources _science_points_cost{0, 0, 0, 0};
		Resources _oil_points_cost{0, 0, 0, 0};
		Resources _mineral_points_cost{0, 0, 0, 0};
		Resources _farm_points_cost{0, 0, 0, 0};
		Resources _industry_points_cost{0, 0, 0, 0};

		void setArmyCost();
		void setScienceCost();
		void setOilCost();
		void setMineralCost();
		void setFarmCost();
		void setIndustryCost();
		void setAllCost();

	public:
		Points() {}
		Points(int army,
			   int science,
			   int oil,
			   int mineral,
			   int farm,
			   int industry)
			: _army_points(army),
			  _science_points(science),
			  _oil_points(oil),
			  _mineral_points(mineral),
			  _farm_points(farm),
			  _industry_points(industry)
		{
			setAllCost();
		}
		void setDependices(std::shared_ptr<Country> country);

		int armyNum(int const points = 0);
		int scienceNum(int const points = 0);
		int oilNum(int const points = 0);
		int mineralNum(int const points = 0);
		int farmNum(int const points = 0);
		int industryNum(int const points = 0);

		float armyCoefCost(float const coef = 0);
		float scienceCoefCost(float const coef = 0);
		float oilCoefCost(float const coef = 0);
		float mineralCoefCost(float const coef = 0);
		float farmCoefCost(float const coef = 0);
		float industryCoefCost(float const coef = 0);
		float allCoefCost(float const coef = 0);

		bool operator<(const Points &p) const;
		bool operator<=(const Points &p) const;
		bool operator>(const Points &p) const;
		bool operator>=(const Points &p) const;
		bool operator==(const Points &p) const;

		const Points operator+(const Points &p) const;
		const Points &operator+=(const Points &p);
		const Points operator-(const Points &p) const;
		const Points &operator-=(const Points &p);
		const Points operator*(const float &coef) const;
		const Points &operator*=(const float &coef);

		void operator<<(olc::net::message<MSG_FROM> msg);
		void operator>>(olc::net::message<MSG_FROM> msg);
	};
	Points tag_invoke(boost::json::value_to_tag<Points>, boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Points const &p);
}

class Map;
namespace LOC
{
	using RES::Resources;

	class Locations
	{
	private:
		std::weak_ptr<Country> _country;
		std::shared_ptr<Map> _map;

		std::vector<std::pair<int, int>> _country_map{};

		float _oil_coef_cost{1.0};
		float _mineral_coef_cost{1.0};
		float _farm_coef_cost{1.0};
		float _industry_coef_cost{1.0};

		Resources _oil_loc_cost{0, 0, 0, 0};
		Resources _mineral_loc_cost{0, 0, 0, 0};
		Resources _farm_loc_cost{0, 0, 0, 0};
		Resources _industry_loc_cost{0, 0, 0, 0};

	public:
		Locations() {}
		Locations(std::vector<std::pair<int, int>> country_map)
			: _country_map{country_map} {}

		void setDependices(std::shared_ptr<Country> country);
		void setDependices(std::shared_ptr<Map> map);

		const Locations operator+(const Locations &l) const;
		const Locations &operator+=(const Locations &l);
		const Locations operator-(const Locations &l) const;
		const Locations &operator-=(const Locations &l);

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
