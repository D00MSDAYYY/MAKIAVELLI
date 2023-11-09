#include "server_waiting.h"
#include "ui_server_waiting.h"

#include <QStackedWidget>

Server_Waiting::Server_Waiting(
    QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Server_Waiting)
{
    ui->setupUi(this);
}

void Server_Waiting::startUpdatingInfo(const std::shared_ptr<Game_Server> &game_server)
{

}

void Server_Waiting::finishUpdatingInfo()
{
    is_active = false;
}

Server_Waiting::~Server_Waiting()
{
    delete ui;
}
