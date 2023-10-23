#include "server_constructor.h"
#include "ui_server_constructor.h"

#include <QStackedWidget>

Server_Constructor::Server_Constructor(QWidget *parent) : QWidget(parent),
                                                          ui(new Ui::Server_Constructor)
{
    ui->setupUi(this);
    ui->players_num_label->setText(QString::number(ui->players_slider->value()));
    ui->bots_num_label->setText(QString::number(ui->bots_slider->value()));
    ui->rounds_num_label->setText(QString::number(ui->rounds_slider->value()));
    ui->thinking_t_num_label->setText(QString::number(ui->thinking_t_slider->value()) + 's');
    
    connect(ui->create_server_button, &QPushButton::clicked, this, &Server_Constructor::createButtonClicked);
}

Server_Constructor::~Server_Constructor()
{
    delete ui;
}

void Server_Constructor::on_players_slider_valueChanged(int value)
{
    ui->players_num_label->setText(QString::number(value));
}

void Server_Constructor::on_bots_slider_valueChanged(int value)
{
    ui->bots_num_label->setText(QString::number(value));
}

void Server_Constructor::on_rounds_slider_valueChanged(int value)
{
    ui->rounds_num_label->setText(QString::number(value));
}

void Server_Constructor::on_thinking_t_slider_valueChanged(int value)
{
    ui->thinking_t_num_label->setText(QString::number(value) + "s");
}




