#include "server_creating.h"
#include "ui_server_creating.h"

#include <utility>

Server_Creating::Server_Creating(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::Server_Creating)
{
    ui->setupUi(this);
    ui->players_num_label->setText(QString::number(ui->players_slider->value()));
    ui->bots_num_label->setText(QString::number(ui->bots_slider->value()));
    ui->rounds_num_label->setText(QString::number(ui->rounds_slider->value()));
    ui->thinking_t_num_label->setText(QString::number(ui->thinking_t_slider->value()) + 's');
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

std::shared_ptr<Game_Server> Server_Creating::createServer(Server_GUI* server_gui)
{
    return std::shared_ptr<Game_Server>{new Game_Server{
        ui->players_slider->value(),
        ui->bots_slider->value(),
        ui->rounds_slider->value(),
        ui->thinking_t_slider->value(),
        server_gui}};
}
