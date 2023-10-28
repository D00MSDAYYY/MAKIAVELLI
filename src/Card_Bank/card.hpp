#pragma once
#include <memory>
#include <string>
#include <boost/json.hpp>

class Country;

namespace CARD
{
	class Card
	{
	private:
		int _card_index{0};
		int _duration{0};
		std::string _description{};
		std::weak_ptr<Country> _country{};
		std::unique_ptr<Card> _next{nullptr};

		virtual void unexecute() = 0;
		virtual void execute() = 0;

	public:
		Card(int card_index,
			 int duration,
			 std::string dercription,
			 std::weak_ptr<Country> country);
		void addNext(std::shared_ptr<Card> next_card);

		int duration() { return _duration; }
		virtual boost::json::value convertToJSONValue() = 0;

		virtual ~Card();
	};
	std::shared_ptr<Card> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Card>>,
									 boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag,
					boost::json::value &jv,
					std::shared_ptr<Card> const &c);
}