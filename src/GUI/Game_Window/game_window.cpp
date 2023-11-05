#include "game_window.h"
#include "ui_game_window.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsItem>

#include <QPushButton>

#include <iostream>

Game_Window::Game_Window(QWidget *parent) : QWidget(parent, Qt::Window),
    ui(new Ui::player_window)
{
    ui->setupUi(this);
    QGraphicsScene *scene{new QGraphicsScene(this)};
    scene->setBackgroundBrush(QBrush{QColor({230, 230, 180}), Qt::Dense5Pattern});
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

Game_Window::~Game_Window()
{
    delete ui;
}
