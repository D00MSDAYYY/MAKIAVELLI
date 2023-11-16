#include "client_gui.h"
#include "ui_client_gui.h"

Client_GUI::Client_GUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client_GUI)
{
    ui->setupUi(this);
}

Client_GUI::~Client_GUI()
{
    delete ui;
}
