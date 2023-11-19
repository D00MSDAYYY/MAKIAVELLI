#include "player_dashboard.h"
#include "ui_player_dashboard.h"

Player_Dashboard::Player_Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player_Dashboard)
{
    ui->setupUi(this);
}

Player_Dashboard::~Player_Dashboard()
{
    delete ui;
}
