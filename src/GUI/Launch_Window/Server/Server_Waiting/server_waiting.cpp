#include "server_waiting.h"
#include "ui_server_waiting.h"

#include <QStackedWidget>

#include <utility>

Server_Waiting::Server_Waiting(std::optional<Game_Server> &game_server,
                               QWidget *parent)
    : QWidget(parent),
      _game_server{game_server},
      ui(new Ui::Server_Waiting)
{
    ui->setupUi(this);
   
}

Server_Waiting::~Server_Waiting()
{
    delete ui;
}
