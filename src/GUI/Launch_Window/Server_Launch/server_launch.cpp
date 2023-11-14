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
            [this, server_creating]()
            {
                std::cerr << "cur ind = " << ui->stackedWidget->currentIndex() << " ser creat ind" << server_creating_index;
                if (ui->stackedWidget->currentIndex() == server_creating_index)
                {
                    ui->create_shutdown_button->setText("Shutdown");
                    server_index = ui->stackedWidget->addWidget(server_creating->createServer(this));
                    ui->stackedWidget->setCurrentIndex(server_index);
                }
                else if (ui->stackedWidget->currentIndex() == server_index)
                {
                    ui->create_shutdown_button->setText("Create");
                    ui->stackedWidget->widget(1)->setAttribute(Qt::WA_DeleteOnClose);
                    ui->stackedWidget->widget(1)->close();
                }
            });
}

Server_Launch::~Server_Launch()
{
    delete ui;
}
