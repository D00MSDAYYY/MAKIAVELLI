#include <random>
#include <chrono>

#include <cstdlib>

#include "game_factory.hpp"
#include "map.hpp"

std::shared_ptr<Resources> Game_Factory::createResources(int ndx)
{

	res_input.open("resources.json");
	res_input.seekg(0, std::ios::end);
	res_str_input.resize(res_input.tellg());
	res_input.seekg(0, std::ios::beg);
	res_input.read(&res_str_input[0], res_str_input.size());
	res_input.close();
	res_ar = boost::json::parse(res_str_input).as_array();

	return std::shared_ptr<Resources>(new Resources(boost::json::value_to<Resources>(res_ar.at(ndx))));
}

std::shared_ptr<Points> Game_Factory::createPoints(int ndx)
{
	points_input.open("points.json");
	points_input.seekg(0, std::ios::end);
	points_str_input.resize(points_input.tellg());
	points_input.seekg(0, std::ios::beg);
	points_input.read(&points_str_input[0], points_str_input.size());
	points_input.close();
	points_ar = boost::json::parse(points_str_input).as_array();

	return std::shared_ptr<Points>(new Points(boost::json::value_to<Points>(points_ar.at(ndx))));
}

std::shared_ptr<Locations> Game_Factory::createLocations(int ndx)
{
	loc_input.open("locations.json");
	loc_input.seekg(0, std::ios::end);
	loc_str_input.resize(loc_input.tellg());
	loc_input.seekg(0, std::ios::beg);
	loc_input.read(&loc_str_input[0], loc_str_input.size());
	loc_input.close();
	loc_ar = boost::json::parse(loc_str_input).as_array();

	return std::shared_ptr<Locations>(new Locations(boost::json::value_to<Locations>(loc_ar.at(ndx))));
}

std::shared_ptr<Cards> Game_Factory::createCards(int ndx)
{
	return std::shared_ptr<Cards>(new Cards());
}

std::shared_ptr<Card_Bank> Game_Factory::createCardBank()
{
	return std::shared_ptr<Card_Bank>(new Card_Bank());
}

void Game_Factory::createMap(std::unordered_map<uint32_t, Country> &p)
{
	std::shared_ptr<Map> map(new Map{_num_of_players});
	int color{1};

	std::default_random_engine dre{uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};
	std::normal_distribution<float> di_x((map->xSize()) / 2, 3.0);
	std::normal_distribution<float> di_y((map->ySize()) / 2, 3.0);
	// std::uniform_int_distribution<int> di_x(0, map->xSize());
	// std::uniform_int_distribution<int> di_y(0, map->ySize());

	for (auto &[ID, country] : p)
	{
		int x{int(di_x(dre))};
		int y{int(di_y(dre))};

		for (; map->find(Cell_Type::COUNTRY_AREA,
						 {x - 3, y - 3},
						 {x + 3, y + 3}) ||
			   map->find(Cell_Type::CAPITAL,
						 {x - 3, y - 3},
						 {x + 3, y + 3});
			 x += 1,
			 y += 2)
		{
		}
		map->cell({x, y}).mapCellOwner(country.locations().get());
		map->cell({x, y}).mapCellType(Cell_Type::CAPITAL);

		const int MIN_COUNTRY_SIZE{50};
		const int MAX_COUNTRY_SIZE{250};
		std::uniform_int_distribution<int> di_country_size(MIN_COUNTRY_SIZE, MAX_COUNTRY_SIZE);
		int country_size{di_country_size(dre)};

		std::vector<std::pair<int, int>> border_line;
		border_line.reserve(MAX_COUNTRY_SIZE);
		border_line.push_back({x, y});

		std::uniform_int_distribution<int> di_step(-1, 1);

		for (int i{1};
			 i < country_size;
			 ++i)
		{
			if (border_line.empty())
				break;

			std::uniform_int_distribution<int> di_index(0, border_line.size() - 1);
			auto border_cell{border_line[di_index(dre)]};

			if (map->isSurroundedBy(Cell_Type::COUNTRY_AREA,
									{border_cell.first, border_cell.second}))
			{
				border_line.erase(std::remove(border_line.begin(),
											  border_line.end(),
											  border_cell),
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

			for (; map->cell({border_cell.first + x_step, border_cell.second + y_step}).mapCellType() == Cell_Type::COUNTRY_AREA ||
				   map->cell({border_cell.first + x_step, border_cell.second + y_step}).mapCellType() == Cell_Type::CAPITAL;)
			{
				int tmp_x{x_step};
				x_step = std::round((x_step - y_step) * std::sqrt(2) / 2);
				y_step = std::round((tmp_x + y_step) * std::sqrt(2) / 2);
			}

			std::pair<int, int> new_border_cell{border_cell.first + x_step, border_cell.second + y_step};
			map->cell({new_border_cell.first, new_border_cell.second}).mapCellOwner(country.locations().get());
			map->cell({new_border_cell.first, new_border_cell.second}).mapCellType(Cell_Type::COUNTRY_AREA);

			*country.locations() += Locations{{new_border_cell}};
			border_line.push_back(new_border_cell);

			map->cell({new_border_cell.first, new_border_cell.second}).color = color;
		}
		country.locations()->setDependices(map);
		color++;
	}
	for (int i{0}; i < map->xSize(); ++i)
	{
		std::cerr << "│";
		for (int j{0}; j < map->ySize(); ++j)
		{
			if (map->cell({i, j}).mapCellType() == Cell_Type::CAPITAL)
				std::cerr << "╬╬";
			if (map->cell({i, j}).mapCellType() == Cell_Type::COUNTRY_AREA)
			{
				int color = 100 + map->cell({i, j}).color;
				if (color == 104)
				{
					std::cout
						<< "\033[100m"
						<< " "
						<< "\u001b[0m";
					std::cout
						<< "\033[100m"
						<< " "
						<< "\u001b[0m";
				}

				else
				{
					std::cout
						<< "\033["
						<< color
						<< "m"
						<< " "
						<< "\u001b[0m";
					std::cout
						<< "\033["
						<< color
						<< "m"
						<< " "
						<< "\u001b[0m";
				}
			}
			if (map->cell({i, j}).mapCellType() == Cell_Type::OCEAN)
			{
				std::cout << "\033[104m"
						  << " "
						  << "\u001b[0m";
				std::cout << "\033[104m"
						  << " "
						  << "\u001b[0m";
			}
		}

		std::cerr << "│" << std::endl;
	}
}

Game_Factory::Game_Factory(int numplay) : _num_of_players{numplay}
{
}

std::unordered_map<uint32_t, Country> Game_Factory::createPlayers()
{
	std::default_random_engine dre{
		uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};

	std::unordered_map<uint32_t, Country> players;
	players.reserve(_num_of_players);

	
	auto card_bank{createCardBank()};

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

		auto res{createResources(index)};
		auto loc{createLocations(index)}; // TODO! change index logic with sepate index for each func
		auto points{createPoints(index)};
		auto cards{createCards(index)};
		auto activity_points{std::shared_ptr<Activity_Points>(new Activity_Points{3})};

		loc->setDependices(res);
		res->setDependices(points, loc);
		points->setDependices(res);
		cards->setDependices(card_bank, loc, res, points);

		players.emplace(DEFAULT_ID + i,
						Country(index,
								res,
								points,
								loc,
								cards,
								activity_points));
	}
	createMap(players);

	return players;
}