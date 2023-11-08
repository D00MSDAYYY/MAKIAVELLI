#include "server.h"
#include "ui_server.h"

#include "server_creating.h"
#include "server_waiting.h"

#include <iostream>

Server::Server(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Server)
{
        ui->setupUi(this);
        auto creating{new Server_Creating(_game_server, this)};
        auto waiting{new Server_Waiting(_game_server, this)};

        int create_index{ui->stackedWidget->addWidget(creating)};
        int waiting_index{ui->stackedWidget->addWidget(waiting)};
        connect(ui->create_shutdown_button, &QPushButton::clicked,
                [&]()
                {
                        if (_game_server)
                        {
                                creating->createGameServer();
                        }
                        else
                        {
                                _game_server = std::nullopt;
                        }
                });
}

Server::~Server()
{
        delete ui;
}
