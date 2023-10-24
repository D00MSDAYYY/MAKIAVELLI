#include "main_window.h"
#include "ui_main_window.h"


#include "game_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Launch_Window *launcher{new Launch_Window(this)};
    launcher->setModal(true);
    launcher->show();
}