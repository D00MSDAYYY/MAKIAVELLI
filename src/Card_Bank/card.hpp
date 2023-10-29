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
	NUMBER,
	COEFFICIENT
};

class Country;

namespace CARD
{
	class Card_Core
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

	public:
		Card_Core(SCOPE scope, TARGET target,
				  EFFECT effect, int index,
				  int duration, int probability,
				  int num_or_coef, std::string description);

		const SCOPE scope() { return _scope; }
		const TARGET target() { return _target; }
		const EFFECT effect() { return _effect; }
		const int index() { return _index; }
		const int duration() { return _duration; }
		const std::string &descriprion() { return _description; }

		~Card_Core(){};
	};
	std::shared_ptr<Card_Core> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Card_Core>>,
										  boost::json::value const &jv);

	class Card_Wrapper : public Card_Core
	{
	private:
		std::weak_ptr<Country> _country{};
		void execute();
		void unexecute();

	public:
		Card_Wrapper(Card_Core cd, std::weak_ptr<Country> country)
			: Card_Core{cd}, _country{country} { execute(); }
		~Card_Wrapper() { unexecute(); };
	};
}
