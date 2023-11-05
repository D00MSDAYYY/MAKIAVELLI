#include <QApplication>

#include "player_GUI.hpp"
#include "server_GUI.hpp"
#include "GUI.hpp"

int runGUI(int argc, char **argv)
{
	QApplication qapp{argc, argv};



	return qapp.exec();
}
