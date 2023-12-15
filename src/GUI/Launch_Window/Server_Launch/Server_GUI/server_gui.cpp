#include "server_gui.h"

#include "ui_server_GUI.h"

Server_GUI::Server_GUI(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::Server_GUI)
{
    ui->setupUi(this);
}

std::shared_ptr<Game_Server>&
Server_GUI::gameServer(std::optional<std::shared_ptr<Game_Server>> game_server)
{
    if(game_server) _game_server = *game_server;
    return _game_server;
}

void
Server_GUI::redraw()
{
    ui->server_addr_text_label->setText(
        QString(_game_server->address().first.data()) + "/"
        + QString::number(_game_server->address().second));
    ui->players_num_label->setText(QString::number(_game_server->playNum().first) + "/"
                                   + QString::number(_game_server->playNum().second));
    ui->bots_num_label->setText(QString::number(_game_server->botNum().first) + "/"
                                + QString::number(_game_server->botNum().second));
    ui->rounds_num_label->setText(QString::number(_game_server->roundsNum().first) + "/"
                                  + QString::number(_game_server->roundsNum().second));
    ui->thinking_t_num_label->setText(QString::number(_game_server->thinkingTime())
                                      + "s");
}

Server_GUI::~Server_GUI() { delete ui; }
