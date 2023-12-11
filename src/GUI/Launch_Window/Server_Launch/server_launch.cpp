#include "server_launch.h"
#include "ui_server_launch.h"

#include "server_creating.h"
#include "server_gui.h"

Server_Launch::Server_Launch(QWidget *parent) : QWidget(parent),
                                                ui(new Ui::Server_Launch)
{
    ui->setupUi(this);

    auto server_gui{new Server_GUI{this}};
    auto server_creating{new Server_Creating{this}};

    server_creating_index = ui->stackedWidget->addWidget(server_creating);
    server_gui_index = ui->stackedWidget->addWidget(server_gui);

    connect(ui->create_shutdown_button, &QPushButton::clicked,
            [this, server_creating, server_gui]()
            {
                if (ui->stackedWidget->currentIndex() == server_creating_index)
                {
                    ui->create_shutdown_button->setText("Shutdown");
                    server_gui->gameServer(server_creating->createServer(server_gui));
                    ui->stackedWidget->setCurrentIndex(server_gui_index);
                }
                else if (ui->stackedWidget->currentIndex() == server_gui_index)
                {
                    ui->create_shutdown_button->setText("Create");
                    ui->stackedWidget->setCurrentIndex(server_creating_index);
                    thread_server_deleting = std::jthread{
                        [this,server_gui]()
                        {
                            std::shared_ptr<Game_Server> deleted_server{
                                std::move(server_gui->gameServer())};
                        }};
                    thread_server_deleting.detach();
                }
            });
}

Server_Launch::~Server_Launch()
{
    delete ui;
}
