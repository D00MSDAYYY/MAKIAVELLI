#include <random>
#include <chrono>
#include <vector>

#include <QResource>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>

#include "game_factory.hpp"
#include "map.hpp"

using AC_POI::Activity_Points;
using CARD::Card;
using CARD::Card_Bank;
using CARD::Cards_Holder;
using LOC::Locations;
using POI::Points;
using RES::Resources;

inline void init()
{
	Q_INIT_RESOURCE(json_files);
}

inline void cleanUp()
{
	Q_CLEANUP_RESOURCE(json_files);
}

Resources Game_Factory::createResources(int index)
{
	if (res_ar.size() == 0)
	{
		QFile res_file(":/json_files/resources.json");
		res_file.open(QIODevice::ReadOnly);
		//! if using GCC 13.2.0 QString::toStdString() cause compile error, with clang 16.0.6 OK
		std::string res_str_input{res_file.readAll().data()};
		res_ar = boost::json::parse(res_str_input).as_array();
		res_file.close();
	}
	return Resources{boost::json::value_to<Resources>(res_ar.at(index))};
}

Points Game_Factory::createPoints(int index)
{
	if (points_ar.size() == 0)
	{
		QFile points_file(":/json_files/points.json");
		points_file.open(QIODevice::ReadOnly);
		std::string points_str_input{points_file.readAll().data()};
		points_ar = boost::json::parse(points_str_input).as_array();
		points_file.close();
	}
	return Points(boost::json::value_to<Points>(points_ar.at(index)));
}

Locations Game_Factory::createLocations(int index)
{
	if (loc_ar.size() == 0)
	{
		QFile loc_file(":/json_files/locations.json");
		loc_file.open(QIODevice::ReadOnly);
		std::string loc_str_input{loc_file.readAll().data()};
		loc_ar = boost::json::parse(loc_str_input).as_array();
		loc_file.close();
	}
	return Locations(boost::json::value_to<Locations>(loc_ar.at(index)));
}

Cards_Holder Game_Factory::createCardsHolder(int index)
{
	return Cards_Holder();
}

Activity_Points Game_Factory::createActivityPoints(int index)
{
	return Activity_Points{3};
}

void Game_Factory::createCardBank(std::unordered_map<uint32_t, Country> &pl)
{
	if (cards_ar.size() == 0)
	{
		QFile cards_file(":/json_files/cards.json");
		cards_file.open(QIODevice::ReadOnly);
		std::string cards_str_input{cards_file.readAll().data()};
		cards_ar = boost::json::parse(cards_str_input).as_array();
		cards_file.close();
	}
	std::vector<Card> cards{};
	for (auto &card : cards_ar)
	{
		cards.push_back(Card{boost::json::value_to<Card>(card)});
	}
	if (!_card_bank)
		_card_bank = std::shared_ptr<Card_Bank>(new Card_Bank{std::move(cards)});

	for (auto &[ID, country] : pl)
	{
		country.cardsHolder().setDependices(_card_bank);
	}
}

void Game_Factory::createMap(std::unordered_map<uint32_t, Country> &p)
{
	if (_map.get() == nullptr)
	{
		_map = std::shared_ptr<Map>(new Map{_num_of_players});
	}

	std::default_random_engine dre{uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};
	std::uniform_int_distribution di_x(0, (_map->xSize()) / 2);
	std::uniform_int_distribution di_y(0, (_map->ySize()) / 2);
	for (auto &[ID, country] : p)
	{
		int x{di_x(dre)};
		int y{di_y(dre)};

		for (int in_x_row_count{0};
			 _map->find(Cell_Type::COUNTRY_AREA,
						{x - 3, y - 3},
						{x + 3, y + 3}) ||
			 _map->find(Cell_Type::CAPITAL,
						{x - 3, y - 3},
						{x + 3, y + 3});
			 ++in_x_row_count)
		{
			++x;
			if (in_x_row_count == _map->xSize())
			{
				++y;
				in_x_row_count = 0;
			}
		}
		_map->cell({x, y}).mapCellOwner(&(country.locations()));
		_map->cell({x, y}).mapCellType(Cell_Type::CAPITAL);

		const int MIN_COUNTRY_SIZE{50};
		const int MAX_COUNTRY_SIZE{250};
		std::uniform_int_distribution<int> di_country_size(MIN_COUNTRY_SIZE, MAX_COUNTRY_SIZE);
		int country_size{di_country_size(dre)};
		std::vector<std::pair<int, int>> border_line;
		border_line.reserve(MAX_COUNTRY_SIZE);
		border_line.push_back({x, y});

		std::uniform_int_distribution<int> di_step(-1, 1);

		for (int i{1};
			 i < country_size && !border_line.empty();
			 ++i)
		{
			std::uniform_int_distribution<int> di_index(0, border_line.size() - 1);
			auto border_cell_coord{border_line[di_index(dre)]};

			if (_map->isSurroundedBy(Cell_Type::COUNTRY_AREA,
									 {border_cell_coord.first, border_cell_coord.second}))
			{
				border_line.erase(std::remove(border_line.begin(),
											  border_line.end(),
											  border_cell_coord),
								  border_line.end());
				--i;
				continue;
			}
			int x_step{di_step(dre)};
			int y_step{di_step(dre)};
			for (; !x_step && !y_step;
				 x_step = di_step(dre),
				 y_step = di_step(dre))
			{
			}
			for (; _map->cell({border_cell_coord.first + x_step, border_cell_coord.second + y_step}).mapCellType() == Cell_Type::COUNTRY_AREA ||
				   _map->cell({border_cell_coord.first + x_step, border_cell_coord.second + y_step}).mapCellType() == Cell_Type::CAPITAL;)
			{
				int tmp_x{x_step};
				x_step = std::round((x_step - y_step) * std::sqrt(2) / 2);
				y_step = std::round((tmp_x + y_step) * std::sqrt(2) / 2);
			}
			std::pair<int, int> new_border_cell_coord{border_cell_coord.first + x_step, border_cell_coord.second + y_step};
			_map->cell({new_border_cell_coord.first, new_border_cell_coord.second}).mapCellOwner(&(country.locations()));
			_map->cell({new_border_cell_coord.first, new_border_cell_coord.second}).mapCellType(Cell_Type::COUNTRY_AREA);
			country.locations() += {new_border_cell_coord};
			border_line.push_back(new_border_cell_coord);
		}
		country.locations().map(_map);
	}
}

Game_Factory::Game_Factory(int numplay) : _num_of_players{numplay}
{
	// init();
}

Game_Factory::~Game_Factory()
{
	// cleanUp();
}

std::unordered_map<uint32_t, Country> Game_Factory::createPlayers()
{
	std::default_random_engine dre{
		uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};

	std::unordered_map<uint32_t, Country> players;
	players.reserve(_num_of_players);

	int index;
	std::unordered_map<int, bool> used_indexes;
	std::uniform_int_distribution<int> di_index(0, MAX_JSON_INDEX);

	for (int i = 0; i < _num_of_players; ++i)
	{
		for (index = di_index(dre); used_indexes[index] == true; ++index % MAX_JSON_INDEX)
		{
			; // TODO! maybe bad probability
		}
		used_indexes[index] = true;

		players.emplace(DEFAULT_ID + i,
						Country(index,
								std::move(createResources(index)),
								std::move(createPoints(index)),
								std::move(createLocations(index)),
								std::move(createCardsHolder(index)),
								std::move(createActivityPoints(index))));
	}
	createMap(players);
	createCardBank(players); // TODO! change this logic and use this methods inside createLocations() and createCards()
	return std::move(players);
}
