#include "server.h"
#include "ui_server.h"

#include "server_creating.h"
#include "server_waiting.h"

#include <iostream>
Server::Server(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Server)
{
        ui->setupUi(this);
        auto creating{new Server_Creating(ui->stackedWidget)};
        auto waiting{new Server_Waiting(ui->stackedWidget)};

        int create_index{ui->stackedWidget->addWidget(creating)};
        int wait_index{ui->stackedWidget->addWidget(waiting)};

        connect(creating, &Server_Creating::createButtonClicked,
                [this, wait_index]()
                { ui->stackedWidget->setCurrentIndex(wait_index); });
        connect(creating, &Server_Creating::createButtonClicked,
                [=]() //! if & segfault
                { parent->parentWidget()->hide(); });
        connect(waiting, &Server_Waiting::shutDownButtonClicked,
                [this, create_index]()
                { ui->stackedWidget->setCurrentIndex(create_index); });
        connect(waiting, &Server_Waiting::shutDownButtonClicked,
                [=]()
                { parent->parentWidget()->show(); });
}

Server::~Server()
{
        delete ui;
}
