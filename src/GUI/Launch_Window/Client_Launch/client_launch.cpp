#include "client_launch.h"

#include "ui_client_launch.h"

Client_Launch::Client_Launch(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::Client_Launch)
{
    ui->setupUi(this);

    connect(ui->connect_button,
            &QPushButton::clicked,
            [this]()
            {
                auto tmp = new Client_GUI{nullptr};
                tmp->playerClient(std::shared_ptr<Player_Client>{
                    new Player_Client{
                                      "localhost", uint16_t(ui->id_edit->text().toUInt()), tmp}
                });
                tmp->show();
            });
}

Client_Launch::~Client_Launch() { delete ui; }
