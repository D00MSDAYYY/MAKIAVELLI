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
        auto waiting{new Server_Waiting(creating, ui->stackedWidget)};

        int create_index{ui->stackedWidget->addWidget(creating)};
        int wait_index{ui->stackedWidget->addWidget(waiting)};

        connect(creating, &Server_Creating::createButtonClicked,
                [=, this]() //! if & segfault
                {
                        ui->stackedWidget->setCurrentIndex(wait_index);

                        parent->parentWidget()->hide();
                        createButtonClicked();
                });

        connect(waiting, &Server_Waiting::shutDownButtonClicked,
                [=, this]()
                {
                        ui->stackedWidget->setCurrentIndex(create_index);
                        parent->parentWidget()->show();
                        shutdownButtonClicked();
                });
}

Server::~Server()
{
        delete ui;
}
