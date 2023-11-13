#include "launch_window.h"
#include "ui_launch_window.h"

#include "server_launch.h"

Launch_Window::Launch_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Launch_Window)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new Server_Launch{this}, "Server");
    // ui->tabWidget->addTab(new Server_Launch{this}, "Client");
}

Launch_Window::~Launch_Window()
{
    delete ui;
}
