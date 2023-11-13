#include "server_launch.h"
#include "ui_server_launch.h"

#include "server_creating.h"

#include <iostream>

Server_Launch::Server_Launch(QWidget *parent) : QWidget(parent),
                                                ui(new Ui::Server_Launch)
{
    ui->setupUi(this);

    auto server_creating{new Server_Creating{this}};
    server_creating_index = ui->stackedWidget->addWidget(server_creating);

    connect(ui->create_shutdown_button, &QPushButton::clicked,
            [&, this]()
            {
                if (ui->stackedWidget->currentIndex() == server_creating_index)
                {
                    ui->create_shutdown_button->setText("Shutdown");
                    std::cerr << "create button pressed " << std::endl;
                    server_index = ui->stackedWidget->addWidget(server_creating->createServer(this));
                }
                if (ui->stackedWidget->currentIndex() == server_index)
                {
                    ui->create_shutdown_button->setText("Create");
                }

            });
}

Server_Launch::~Server_Launch()
{
    delete ui;
}
