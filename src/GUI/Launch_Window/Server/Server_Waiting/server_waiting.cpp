#include "server_waiting.h"
#include "ui_server_waiting.h"

#include <QStackedWidget>

#include <utility>

Server_Waiting::Server_Waiting(Server_Creating *server_creating, QWidget *parent)
    : QWidget(parent),
      _server_creating{server_creating},
      ui(new Ui::Server_Waiting)
{
    ui->setupUi(this);
    connect(ui->shutdown_button, &QPushButton::clicked, this, &Server_Waiting::shutDownButtonClicked);
}

Server_Waiting::~Server_Waiting()
{
    delete ui;
}

void Server_Waiting::showEvent(QShowEvent *event)
{
    if (_server_creating)
    {
        _game_server = std::move(_server_creating->createGameServer());
    }
}
