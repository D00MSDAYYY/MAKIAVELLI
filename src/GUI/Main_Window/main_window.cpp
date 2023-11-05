#include "main_window.h"
#include "ui_main_window.h"

#include <QWindow>


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

}
