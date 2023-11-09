#include "server.h"
#include "ui_server.h"

#include "server_creating.h"
#include "server_waiting.h"

#include <iostream>

Server::Server(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Server)
{
        ui->setupUi(this);
        auto creating{new Server_Creating(this)};
        auto waiting{new Server_Waiting(this)};

        int create_index{ui->stackedWidget->addWidget(creating)};
        int waiting_index{ui->stackedWidget->addWidget(waiting)};
        connect(ui->create_shutdown_button, &QPushButton::clicked,
                [&]()
                {
                        if (!_game_server)
                        {
                                creating->createGameServer(_game_server);
                                std::cerr << "create button pushed" << (_game_server.get() == nullptr) << std::endl;
                        }
                        else
                        {
                                _game_server.reset();
                                std::cerr << _game_server.use_count();
                                std::cerr << "shutdown button pushed" << (_game_server.get() == nullptr) << std::endl;
                        }
                });
}

Server::~Server()
{
        delete ui;
}
