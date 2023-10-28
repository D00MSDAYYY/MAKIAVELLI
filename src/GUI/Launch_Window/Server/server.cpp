#include "server.h"
#include "ui_server.h"

#include "server_constructor.h"
#include "server_waiting.h"



Server::Server(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Server)
{
    ui->setupUi(this);

    auto constructor{new Server_Constructor(ui->stackedWidget)};
    auto waiting{new Server_Waiting(ui->stackedWidget)};

    int constr_index{ui->stackedWidget->addWidget(constructor)};
    int wait_index{ui->stackedWidget->addWidget(waiting)};

    connect(constructor, &Server_Constructor::createButtonClicked,
            ui->stackedWidget, [&, this]()
            { ui->stackedWidget->setCurrentIndex(wait_index); });
    connect(constructor, &Server_Constructor::createButtonClicked,
            parent, [=]()
            { parent->parentWidget()->hide(); });
    connect(waiting, &Server_Waiting::shutDownButtonClicked,
            ui->stackedWidget, [&, this]()
            { ui->stackedWidget->setCurrentIndex(constr_index); });
    connect(waiting, &Server_Waiting::shutDownButtonClicked,
            this, [=]()
            { parent->parentWidget()->show(); });

        
}

Server::~Server()
{
    delete ui;
}


