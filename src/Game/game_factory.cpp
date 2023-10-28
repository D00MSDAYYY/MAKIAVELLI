#include <random>
#include <chrono>
#include <cstdlib>

#include "game_factory.hpp"
#include "map.hpp"

std::shared_ptr<Resources> Game_Factory::createResources(int index)
{
	if (res_ar.size() == 0)
	{
		std::ifstream res_input{};
		std::string res_str_input{};

		res_input.open("resources.json");
		res_input.seekg(0, std::ios::end);
		res_str_input.resize(res_input.tellg());
		res_input.seekg(0, std::ios::beg);
		res_input.read(&res_str_input[0], res_str_input.size());
		res_input.close();
		res_ar = boost::json::parse(res_str_input).as_array();
	}
	return std::shared_ptr<Resources>(new Resources(boost::json::value_to<Resources>(res_ar.at(index))));
}

std::shared_ptr<Points> Game_Factory::createPoints(int index)
{
	if (points_ar.size() == 0)
	{
		std::ifstream points_input{};
		std::string points_str_input{};
		points_input.open("points.json");
		points_input.seekg(0, std::ios::end);
		points_str_input.resize(points_input.tellg());
		points_input.seekg(0, std::ios::beg);
		points_input.read(&points_str_input[0], points_str_input.size());
		points_input.close();
		points_ar = boost::json::parse(points_str_input).as_array();
	}

	return std::shared_ptr<Points>(new Points(boost::json::value_to<Points>(points_ar.at(index))));
}

std::shared_ptr<Locations> Game_Factory::createLocations(int index)
{
	if(loc_ar.size() == 0)
	{
		std::ifstream loc_input{};
		std::string loc_str_input{};
		loc_input.open("locations.json");
		loc_input.seekg(0, std::ios::end);
		loc_str_input.resize(loc_input.tellg());
		loc_input.seekg(0, std::ios::beg);
		loc_input.read(&loc_str_input[0], loc_str_input.size());
		loc_input.close();
		loc_ar = boost::json::parse(loc_str_input).as_array();
	}

	return std::shared_ptr<Locations>(new Locations(boost::json::value_to<Locations>(loc_ar.at(index))));
}

std::shared_ptr<Cards_Holder> Game_Factory::createCardsHolder(int index)
{
	return std::shared_ptr<Cards_Holder>(new Cards_Holder());
}

std::shared_ptr<Activity_Points> Game_Factory::createActivityPoints(int index)
{
	return std::shared_ptr<Activity_Points>(new Activity_Points{3});
}

void Game_Factory::createCardBank(std::unordered_map<uint32_t, Country> &pl)
{
	if (_card_bank.get() == nullptr)
		_card_bank = std::shared_ptr<Card_Bank>(new Card_Bank{});
	for (auto &[ID, country] : pl)
	{
		country.cardsHolder()->setDependices(_card_bank); // TODO! card_bank
	}
}

void Game_Factory::createMap(std::unordered_map<uint32_t, Country> &p)
{
	if (_map.get() == nullptr)
		_map = std::shared_ptr<Map>(new Map{_num_of_players});

	std::default_random_engine dre{uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};
	std::normal_distribution<float> di_x((_map->xSize()) / 2, 3.0);
	std::normal_distribution<float> di_y((_map->ySize()) / 2, 3.0);

	for (auto &[ID, country] : p)
	{
		int x{int(di_x(dre))};
		int y{int(di_y(dre))};

		for (; _map->find(Cell_Type::COUNTRY_AREA,
						  {x - 3, y - 3},
						  {x + 3, y + 3}) ||
			   _map->find(Cell_Type::CAPITAL,
						  {x - 3, y - 3},
						  {x + 3, y + 3});
			 x += 1,
			 y += 2)
		{
		}
		_map->cell({x, y}).mapCellOwner(country.locations().get());
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
			_map->cell({new_border_cell_coord.first, new_border_cell_coord.second}).mapCellOwner(country.locations().get());
			_map->cell({new_border_cell_coord.first, new_border_cell_coord.second}).mapCellType(Cell_Type::COUNTRY_AREA);

			*country.locations() += Locations{{new_border_cell_coord}};
			border_line.push_back(new_border_cell_coord);
		}
		country.locations()->setDependices(_map);
	}
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
								createResources(index),
								createPoints(index),
								createLocations(index),
								createCardsHolder(index),
								createActivityPoints(index)));
	}
	createMap(players);
	createCardBank(players); // TODO! change this logic and use this methods inside createLocations() and createCards()

	return std::move(players);
}
