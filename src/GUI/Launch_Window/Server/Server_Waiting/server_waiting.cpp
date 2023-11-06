#include "server_waiting.h"
#include "ui_server_waiting.h"

#include <QStackedWidget>


Server_Waiting::Server_Waiting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server_Waiting)
{
    ui->setupUi(this);
    connect(ui->shutdown_button, &QPushButton::clicked, this, &Server_Waiting::shutDownButtonClicked);


}

Server_Waiting::~Server_Waiting()
{
    delete ui;
}

