#include "server_creating.h"
#include "ui_server_creating.h"

#include <QStackedWidget>

Server_Creating::Server_Creating(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Server_Creating)
{
    ui->setupUi(this);
    ui->players_num_label->setText(QString::number(ui->players_slider->value()));
    ui->bots_num_label->setText(QString::number(ui->bots_slider->value()));
    ui->rounds_num_label->setText(QString::number(ui->rounds_slider->value()));
    ui->thinking_t_num_label->setText(QString::number(ui->thinking_t_slider->value()) + 's');
}

void Server_Creating::createGameServer(std::shared_ptr<Game_Server> &game_server )
{
    game_server = std::shared_ptr<Game_Server>{new Game_Server(1, 1, 1, 1)};
    std::cerr << "created game server" << game_server.use_count() << std::endl;
}

Server_Creating::~Server_Creating()
{
    delete ui;
}

void Server_Creating::on_players_slider_valueChanged(int value)
{
    ui->players_num_label->setText(QString::number(value));
}

void Server_Creating::on_bots_slider_valueChanged(int value)
{
    ui->bots_num_label->setText(QString::number(value));
}

void Server_Creating::on_rounds_slider_valueChanged(int value)
{
    ui->rounds_num_label->setText(QString::number(value));
}

void Server_Creating::on_thinking_t_slider_valueChanged(int value)
{
    ui->thinking_t_num_label->setText(QString::number(value) + "s");
}
