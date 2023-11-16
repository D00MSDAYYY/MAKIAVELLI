#include "launch_window.h"
#include "ui_launch_window.h"

#include "server_launch.h"
#include "client_launch.h"

Launch_Window::Launch_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Launch_Window)
{
    ui->setupUi(this);
    int server_index{ui->tabWidget->addTab(new Server_Launch{this}, "Server")};
    int client_index{ui->tabWidget->addTab(new Client_Launch{this}, "Client")};
}

Launch_Window::~Launch_Window()
{
    delete ui;
}
