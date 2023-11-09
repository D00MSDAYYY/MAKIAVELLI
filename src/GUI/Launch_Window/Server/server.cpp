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

        int creating_index{ui->stackedWidget->addWidget(creating)};
        int waiting_index{ui->stackedWidget->addWidget(waiting)};
        connect(ui->create_shutdown_button, &QPushButton::clicked,
                [=,this]()
                {
                        if (!_game_server)
                        {
                                _game_server = creating->createGameServer();
                                waiting->startUpdatingInfo(_game_server);
                                ui->stackedWidget->setCurrentIndex(waiting_index);
                                std::cerr << "======================>" << (_game_server.get() == nullptr) << std::endl;
                        }
                        else
                        {
                                waiting->finishUpdatingInfo();
                                _game_server.reset();
                                ui->stackedWidget->setCurrentIndex(creating_index);
                                std::cerr << "=======================" << (_game_server.get() == nullptr) << std::endl;
                        }
                });
}

Server::~Server()
{
        delete ui;
}
