#include "client.h"
#include "ui_client.h"

#include "client_connector.h"
#include "client_waiting.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    auto connector{new Client_Connector(ui->stackedWidget)};
    auto waiting{new Client_Waiting(ui->stackedWidget)};

    int connect_index{ui->stackedWidget->addWidget(connector)};
    int wait_index{ui->stackedWidget->addWidget(waiting)};

    connect(connector, &Client_Connector::connectButtonClicked,
            ui->stackedWidget, [=]()
            { ui->stackedWidget->setCurrentIndex(wait_index); });
    connect(connector, &Client_Connector::connectButtonClicked,
            parent, [=]()
            { parent->parentWidget()->hide(); });
    connect(waiting, &Client_Waiting::shutDownButtonClicked,
            ui->stackedWidget, [=]()
            { ui->stackedWidget->setCurrentIndex(connect_index); });
    connect(waiting, &Client_Waiting::shutDownButtonClicked,
            this, [=]()
            { parent->parentWidget()->show(); });
}

Client::~Client()
{
    delete ui;
}
