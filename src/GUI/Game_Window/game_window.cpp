#include "game_window.h"
#include "ui_game_window.h"

#include <QPushButton>

Game_Window::Game_Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game_Window)
{
    ui->setupUi(this);
}

Game_Window::~Game_Window()
{
    delete ui;
}
