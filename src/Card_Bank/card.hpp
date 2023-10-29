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

		void execute();
		void unexecute();

	public:
		Card(SCOPE scope,
			 TARGET target,
			 EFFECT effect,
			 int index,
			 int duration,
			 int probability,
			 int num_or_coef,
			 std::string description) : _index{index},
										_duration{duration},
										_probability{probability},
										_scope{scope},
										_target{target},
										_effect{effect},
										_num_or_coef{num_or_coef},
										_description{std::move(description)} {}

		const SCOPE scope() { return _scope; }
		const TARGET target() { return _target; }
		const EFFECT effect() { return _effect; }
		const int index() { return _index; }
		const int duration() { return _duration; }
		const std::string &descriprion() { return _description; }

		bool attach(std::weak_ptr<Country> country);
		void detach();
		
		~Card(){};
	};
	std::shared_ptr<Card> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Card>>,
									 boost::json::value const &jv);

}
