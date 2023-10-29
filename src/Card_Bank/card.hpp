#pragma once
#include <memory>
#include <string>
#include <boost/json.hpp>

enum class SCOPE
{
	ARMY,
	SCIENCE,
	OIL,
	MINERAL,
	FARM,
	INDUSTRY,
	ALL
};

enum class TARGET
{
	LOCATIONS,
	POINTS,
	RESOURCES
};

enum class EFFECT
{
	EFFECT,
	COEFFICIENT
};

class Country;

namespace CARD
{
	class Card
	{
	private:
		int _index{0};
		TARGET _target{};
		SCOPE _scope{};
		EFFECT _effect{};
		std::string _description{};
		int _probability{0};
		int _duration{0};
		int _num_or_coef{0};

		std::weak_ptr<Country> _country{};

	public:
		Card(int index,
			 SCOPE scope,
			 TARGET target,
			 EFFECT effect,
			 std::string description,
			 int probability,
			 int duration,
			 int num_or_coef);
		Card(const Card &c, std::weak_ptr<Country> country);

		const SCOPE scope() { return _scope; }
		const TARGET target() { return _target; }
		const EFFECT effect() { return _effect; }
		const int index() { return _index; }
		const int duration() { return _duration; }
		const std::string &descriprion() { return _description; }

		void execute();
		void unexecute();

		~Card();
	};
	Card tag_invoke(boost::json::value_to_tag<Card>, boost::json::value const &jv);
	SCOPE toSCOPE(std::string str);
	TARGET toTARGET(std::string str);
	EFFECT toEFFECT(std::string str);
}
