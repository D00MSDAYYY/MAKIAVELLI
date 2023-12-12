#include <QApplication>

#include "GUI.hpp"
#include "main_window.h"

int runGUI(int argc, char **argv)
{
	QApplication qapp{argc, argv};
	
	MainWindow main_window{};
	main_window.show();

	return qapp.exec();
}
