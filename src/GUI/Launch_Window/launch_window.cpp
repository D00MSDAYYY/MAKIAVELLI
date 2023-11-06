#include "launch_window.h"
#include "ui_launch_window.h"

#include "client_connector.h"

#include "server.h"
#include "client.h"

#include <QTabBar>

Launch_Window::Launch_Window(QWidget *parent) : QDialog(parent),
                                                ui(new Ui::Launch_Window)
{
    ui->setupUi(this);
    auto server = new Server(this);
    auto client = new Client(this);
    ui->tabWidget->addTab(server, "create");
    ui->tabWidget->addTab(client, "connect");

    connect(server, &Server::createButtonClicked, this, &Launch_Window::createButtonClicked);
    connect(server, &Server::shutdownButtonClicked, this, &Launch_Window::shutdownButtonClicked);
}

void Launch_Window::closeEvent(QCloseEvent *e)
{
    parentWidget()->show();
}

Launch_Window::~Launch_Window()
{
    delete ui;
}

void Launch_Window::createButtonClicked()
{
    // ui->tabWidget->tabBar()->setEnabled(false);
    ui->tabWidget->tabBar()->hide();
}
void Launch_Window::shutdownButtonClicked()
{
    // ui->tabWidget->tabBar()->setEnabled(true);
    ui->tabWidget->tabBar()->show();
}