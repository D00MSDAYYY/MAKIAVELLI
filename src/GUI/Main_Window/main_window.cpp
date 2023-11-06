#include "main_window.h"
#include "ui_main_window.h"

#include  "launch_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_button_clicked()
{
    Launch_Window *launch_window = new Launch_Window{this};
    launch_window->setModal(true);
    launch_window->show();
}
