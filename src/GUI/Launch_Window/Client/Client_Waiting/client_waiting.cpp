#include "client_waiting.h"
#include "ui_client_waiting.h"

Client_Waiting::Client_Waiting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client_Waiting)
{
    ui->setupUi(this);
    connect(ui->shutdown_button, &QPushButton::clicked, this, &Client_Waiting::shutDownButtonClicked);
}

Client_Waiting::~Client_Waiting()
{
    delete ui;
}
