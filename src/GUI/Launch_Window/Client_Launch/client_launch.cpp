#include "client_launch.h"
#include "ui_client_launch.h"

Client_Launch::Client_Launch(QWidget *parent) : QWidget(parent),
                                                ui(new Ui::Client_Launch)
{
    ui->setupUi(this);
   
    connect(ui->connect_button, &QPushButton::clicked,
            [this]()
            {
                
            });
}

Client_Launch::~Client_Launch()
{
    delete ui;
}
