#include <QApplication>


#include "GUI.hpp"

int runGUI(int argc, char **argv)
{
	QApplication qapp{argc, argv};



	return qapp.exec();
}
