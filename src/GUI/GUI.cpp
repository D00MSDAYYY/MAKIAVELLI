#include "GUI.hpp"

#include "main_window.h"

#include <QApplication>

int
runGUI(int argc, char** argv)
{
    QApplication qapp{argc, argv};

    MainWindow   main_window{};
    main_window.show();

    return qapp.exec();
}
