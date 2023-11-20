#include "client_gui.h"
#include "ui_client_gui.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QRect>
#include <QBrush>

#include "player_dashboard.h"

inline void init()
{
    Q_INIT_RESOURCE(images);
}

inline void cleanUp()
{
    Q_CLEANUP_RESOURCE(images);
}

Client_GUI::Client_GUI(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::Client_GUI)
{
    init();
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene{this});
    QPixmap image{":/images/background.svg"};
    image.scaled(2000, 2000);
    QBrush brush{image};
    ui->graphicsView->scene()->setBackgroundBrush(image);

    // auto tmp = ui->graphicsView->scene()->addWidget(new Player_Dashboard{"", this});
}

Client_GUI::~Client_GUI()
{
    delete ui;
}

std::shared_ptr<Player_Client> &Client_GUI::playerClient(std::optional<std::shared_ptr<Player_Client>> player_client)
{
    if (!player_client)
        return _player_client;
    else
    {
        _player_client = *player_client;
        return _player_client;
    }
}

void Client_GUI::redraw()
{
    std::cerr << " size " << _player_client->countries().size() << std::endl;

}
