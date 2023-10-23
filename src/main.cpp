#include <iostream>
#include "game_server.hpp"

int main(int argc, char *argv[])
{
	Game_Server gs{2, 0, 100, 15, 0};
	gs.run();
}
