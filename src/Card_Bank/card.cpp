#include "card.hpp"
#include "country.hpp"

using CARD::Card_Core;

CARD::Card_Core::Card_Core(SCOPE scope,
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




