#pragma once
#include <boost/json.hpp>
#include <memory>

#include "game_network.hpp"

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

		RES::Resources _army_points_cost{0, 0, 0, 0};
		RES::Resources _science_points_cost{0, 0, 0, 0};
		RES::Resources _oil_points_cost{0, 0, 0, 0};
		RES::Resources _mineral_points_cost{0, 0, 0, 0};
		RES::Resources _farm_points_cost{0, 0, 0, 0};
		RES::Resources _industry_points_cost{0, 0, 0, 0};

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