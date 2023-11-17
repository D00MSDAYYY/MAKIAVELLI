#include "client_launch.h"
#include "ui_client_launch.h"

#include "player_client.hpp"

Client_Launch::Client_Launch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client_Launch)
{
    ui->setupUi(this);

    auto client_gui{new Player_Client{ui->address_edit->text().toUtf8().constData(),
                                      uint16_t(ui->id_edit->text().toUInt())}};
    // connect(ui->create_shutdown_button, &QPushButton::clicked,
    //         [this, server_creating, server_gui]()
    //         {
    //             if (ui->stackedWidget->currentIndex() == server_creating_index)
    //             {
    //                 ui->create_shutdown_button->setText("Shutdown");
    //                 server_gui->gameServer(server_creating->createServer(server_gui));
    //                 ui->stackedWidget->setCurrentIndex(server_gui_index);
    //             }
    //             else if (ui->stackedWidget->currentIndex() == server_gui_index)
    //             {
    //                 ui->create_shutdown_button->setText("Create");
    //                 ui->stackedWidget->setCurrentIndex(server_creating_index);
    //                 thread_server_deleting = std::jthread{
    //                     [this, server_gui]()
    //                     {
    //                         std::shared_ptr<Game_Server> deleted_server{
    //                             std::move(server_gui->gameServer())};
    //                     }};
    //                 thread_server_deleting.detach();
    //             }
    //         });
}

Client_Launch::~Client_Launch()
{
    delete ui;
}
