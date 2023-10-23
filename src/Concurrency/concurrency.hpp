#include "gui.hpp"
#include "game_server.hpp"
#include "player_client.hpp"

void runGui(); //! is started from MAIN thread just after launch, calling runServer
			   //! and calling client

void runServer(GAME_MODE mode, int playnum, std::string address = ""); //! can throw an exeption, is called from runGUI thread

void runClient(std::string address);