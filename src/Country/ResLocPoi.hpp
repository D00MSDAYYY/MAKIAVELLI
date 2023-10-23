#pragma once

#include <boost/json.hpp>
#include <memory>


struct Data_Resources
{
	uint32_t _oil_resources{};
	uint32_t _mineral_resources{};
	uint32_t _farm_resources{};
	uint32_t _industry_resources{};
};

namespace POI
{
	class Points;
}
namespace LOC
{
	class Locations;
}


namespace RES
{
	using LOC::Locations;
	using POI::Points;
	class Resources
	{
	private:
		std::weak_ptr<Points> _points;
		std::weak_ptr<Locations> _locations;

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

		Resources(Data_Resources &dr);
		void setDependices(std::shared_ptr<Points> points, std::shared_ptr<Locations> locations);
		Data_Resources convertToData() const;

		int oil(int const resources = 0);
		int mineral(int const resources = 0);
		int farm(int const resources = 0);
		int industry(int const resources = 0);

		float oilCoef(float const coef = 0);
		float mineralCoef(float const coef = 0);
		float farmCoef(float const coef = 0);
		float industryCoef(float const coef = 0);

		void updateRes();

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
	};
	Resources tag_invoke(boost::json::value_to_tag<Resources>, boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Resources const &res);
}


struct Data_Points
{
	uint32_t _army_points{};
	uint32_t _science_points{};
	uint32_t _oil_points{};
	uint32_t _mineral_points{};
	uint32_t _farm_points{};
	uint32_t _industry_points{};
};

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

		std::weak_ptr<Resources> _resources;

		int _army_points{};
		int _science_points{};
		int _oil_points{};
		int _mineral_points{};
		int _farm_points{};
		int _industry_points{};

		float _army_coef{1.0};
		float _science_coef{1.0};
		float _oil_coef{1.0};
		float _mineral_coef{1.0};
		float _farm_coef{1.0};
		float _industry_coef{1.0};

		
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
		void setDependices(std::shared_ptr<Resources> resources);
		Data_Points convertToData();

		int army(int const points = 0);
		int science(int const points = 0);
		int oil(int const points = 0);
		int mineral(int const points = 0);
		int farm(int const points = 0);
		int industry(int const points = 0);

		float armyCoef(float const coef = 0);
		float scienceCoef(float const coef = 0);
		float oilCoef(float const coef = 0);
		float mineralCoef(float const coef = 0);
		float farmCoef(float const coef = 0);
		float industryCoef(float const coef = 0);
		float allCoef(float const coef = 0);

		bool operator<(const Points &p) const;
		bool operator<=(const Points &p) const;
		bool operator>(const Points &p) const;
		bool operator>=(const Points &p) const;
		bool operator==(const Points &p) const;

		Points operator+(const Points &p) const;
		Points &operator+=(const Points &p);
		Points operator-(const Points &p) const;
		Points &operator-=(const Points &p);
		Points operator*(const float &coef) const;
		Points &operator*=(const float &coef);
	};
	Points tag_invoke(boost::json::value_to_tag<Points>, boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Points const &p);
}

enum class LOC_TYPE : uint8_t
{
	COUNTRY,

	OIL,
	MINERAL,
	FARM,
	INDUSTRY
};
struct Data_Locations
{
	LOC_TYPE _loc_type{LOC_TYPE::COUNTRY};
	std::vector<std::pair<uint32_t, uint32_t>> _loc_coord{};
};

class Map;
namespace LOC
{
	using RES::Resources;
	class Locations
	{
	private:
		std::weak_ptr<Resources> _resources;
		std::shared_ptr<Map> _map;

		std::vector<std::pair<unsigned int, unsigned int>> _country_map{};

		float _oil_coef{1.0};
		float _mineral_coef{1.0};
		float _farm_coef{1.0};
		float _industry_coef{1.0};

		Resources _oil_loc_cost{0, 0, 0, 0};
		Resources _mineral_loc_cost{0, 0, 0, 0};
		Resources _farm_loc_cost{0, 0, 0, 0};
		Resources _industry_loc_cost{0, 0, 0, 0};

	public:
		Locations(std::vector<std::pair<unsigned int, unsigned int>> country_map)
			: _country_map{country_map} {}

		void setDependices(std::shared_ptr<Resources> resources);
		void setDependices(std::shared_ptr<Map> map);

		Data_Locations convertToData();

		Locations operator+(const Locations &l) const;
		Locations &operator+=(const Locations &l);
		Locations operator-(const Locations &l) const;
		Locations &operator-=(const Locations &l);
		
		//! change to operator + -

		std::shared_ptr<Map> map();

		int oil(std::vector<std::pair<unsigned int, unsigned int>> loc_coord = {});
		int mineral(std::vector<std::pair<unsigned int, unsigned int>> loc_coord = {});
		int farm(std::vector<std::pair<unsigned int, unsigned int>> loc_coord = {});
		int industry(std::vector<std::pair<unsigned int, unsigned int>> loc_coord = {});

		//! bool changeCapital(std::pair<uint8_t, uint8_t> capital_coord);

		float oilCoef(float const coef = 0);
		float mineralCoef(float const coef = 0);
		float farmCoef(float const coef = 0);
		float industryCoef(float const coef = 0);
		float allCoef(float const coef = 0);

		bool operator<(const Locations &cl) const;
		bool operator<=(const Locations &cl) const;
	};
	Locations tag_invoke(boost::json::value_to_tag<Locations>, boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Locations const &p);
}
