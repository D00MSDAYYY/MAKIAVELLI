#include "client_gui.h"
#include "ui_client_gui.h"

Client_GUI::Client_GUI(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::Client_GUI)
{
    ui->setupUi(this);
}

Client_GUI::~Client_GUI()
{
    delete ui;
}

std::shared_ptr<Player_Client> &Client_GUI::playerClient(std::optional<std::shared_ptr<Player_Client>> player_client)
{
    if (!player_client)
        return _player_client;
    else
    {
        _player_client = *player_client;
        return _player_client;
    }
}
