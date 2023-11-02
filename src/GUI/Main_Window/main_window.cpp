#include "main_window.h"
#include "ui_main_window.h"

#include "game_window.h"
#include <QWindow>

#include <iostream>

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
    // TODO! Launch_Window *launcher{new Launch_Window(this)};
    // launcher->setModal(true);
    // launcher->show();
    Game_Window *gm = new Game_Window{this};
    gm->show();
}
