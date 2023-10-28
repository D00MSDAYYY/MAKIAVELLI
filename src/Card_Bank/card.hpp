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
		int _index{0};
		int _duration{0};
		std::string _description{};
		std::weak_ptr<Country> _country{};
		std::unique_ptr<Card> _next{nullptr};

		virtual void unexecute() = 0;
		virtual void execute() = 0;

	public:
		Card(int index,
			 int duration,
			 std::string description,
			 std::weak_ptr<Country> country,
			 std::shared_ptr<Card> card = nullptr) : _index{index},
													 _duration{duration},
													 _description{description},
													 _country{country},
													 _next{std::move(card.get())} {}

		Card(std::shared_ptr<Card> card) : Card(card->_index,
												card->_duration,
												card->_description,
												card->_country,
												card) {}

		int index() { return _index; }
		int duration() { return _duration; }
		std::string descriprion() { return _description; }
		virtual boost::json::value convertToJSONValue() = 0;

		virtual ~Card();
	};
	std::shared_ptr<Card> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Card>>,
									 boost::json::value const &jv);
	void tag_invoke(boost::json::value_from_tag,
					boost::json::value &jv,
					std::shared_ptr<Card> const &c);
}