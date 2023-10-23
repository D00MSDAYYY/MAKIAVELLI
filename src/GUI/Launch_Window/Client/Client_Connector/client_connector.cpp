#include "client_connector.h"
#include "ui_client_connector.h"

Client_Connector::Client_Connector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client_Connector)
{
    ui->setupUi(this);
    connect(ui->connect_client_button, &QPushButton::clicked, this, &Client_Connector::connectButtonClicked);
}

Client_Connector::~Client_Connector()
{
    delete ui;
}
