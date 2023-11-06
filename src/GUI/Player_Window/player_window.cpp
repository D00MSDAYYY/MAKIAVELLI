#include "player_window.h"
#include "ui_player_window.h"

Player_Window::Player_Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player_Window)
{
    ui->setupUi(this);
}

Player_Window::~Player_Window()
{
    delete ui;
}
