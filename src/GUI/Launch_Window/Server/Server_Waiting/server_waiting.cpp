#include "server_waiting.h"
#include "ui_server_waiting.h"

#include <QStackedWidget>

#include <utility>

Server_Waiting::Server_Waiting(
                               QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Server_Waiting)
{
    ui->setupUi(this);
   
}

Server_Waiting::~Server_Waiting()
{
    delete ui;
}
