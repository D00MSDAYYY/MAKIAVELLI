#include "server_gui.h"
#include "ui_server_GUI.h"

Server_GUI::Server_GUI(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Server_GUI)
{
    ui->setupUi(this);
}

std::shared_ptr<Game_Server> &Server_GUI::gameServer(std::optional<std::shared_ptr<Game_Server>> game_server)
{
    if (!game_server)
        return _game_server;
    else
    {
        _game_server = *game_server; 
        return _game_server;
    }
}


Server_GUI::~Server_GUI()
{
    delete ui;
}
