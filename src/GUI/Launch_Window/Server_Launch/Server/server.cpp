#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent,
               int play_num, int bot_num,
               int rounds, int thinking_time,
               uint16_t port)
    : QWidget(parent),
      ui(new Ui::Server),
      Game_Server{play_num, bot_num,
                  rounds, thinking_time, port}
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}
