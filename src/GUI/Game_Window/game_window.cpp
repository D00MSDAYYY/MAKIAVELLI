#include "game_window.h"
#include "ui_game_window.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsItem>

#include <QPushButton>

#include <iostream>

Game_Window::Game_Window(QWidget *parent) : QWidget(parent, Qt::Window),
                                            ui(new Ui::Game_Window)
{
    ui->setupUi(this);
    
}

Game_Window::~Game_Window()
{
    delete ui;
}
