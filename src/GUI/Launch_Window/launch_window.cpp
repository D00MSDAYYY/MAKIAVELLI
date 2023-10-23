#include "launch_window.h"
#include "ui_launch_window.h"

#include "client_connector.h"

#include "server.h"
#include "client.h"

#include <iostream>

void printMe()
{
    std::cerr << "printMe activated";
}
Launch_Window::Launch_Window(QWidget *parent) : QDialog(parent),
                                                ui(new Ui::Launch_Window)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new Server(this), "create");
    ui->tabWidget->addTab(new Client(this), "connect");

}

Launch_Window::~Launch_Window()
{
    delete ui;
}
