#include "client_gui.h"
#include "ui_client_gui.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QRect>
#include <QBrush>

#include "player_dashboard.h"

inline void init()
{
    Q_INIT_RESOURCE(cg_images);
}

inline void cleanUp()
{
    Q_CLEANUP_RESOURCE(cg_images);
}

Client_GUI::Client_GUI(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::Client_GUI)
{
    init();
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    auto scene = new QGraphicsScene{this};
    scene->setSceneRect(0, 0, 1920, 1080);
    QPixmap pixmap{":/cg_images/background.svg"};
    scene->setBackgroundBrush(pixmap);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    scene->addRect(0, 0, 1920, 1080);
}

Client_GUI::~Client_GUI()
{
    delete ui;
}

std::shared_ptr<Player_Client> &Client_GUI::playerClient(std::optional<std::shared_ptr<Player_Client>> game_client)
{
    if (game_client)
        _game_client = *game_client;
    return _game_client;
}

void Client_GUI::redraw()
{
    if (_game_client && (_players_dashboards.size() != _game_client->countries().size()))
    {
        for (auto &[index, country] : _game_client->countries())
        {
            if (!_players_dashboards.contains(index))
            {
                auto tmp = new Player_Dashboard{};
                tmp->index(index);
                _players_dashboards[index] =
                    ui->graphicsView->scene()->addWidget(tmp);
            }
        }
    }
    {
        // switch ()
        // {
        // case 1:
        // {
        //     // auto tmp = ui->graphicsView->scene()->addWidget(new Player_Dashboard{""});

        //     break;
        // }
        // case 2:
        // {
        //     for (auto &[ID, country] : _game_client->countries())
        //         ;
        //     break;
        // }
        // case 3:
        // {
        //     break;
        // }
        // case 4:
        // {
        //     break;
        // }
        // case 5:
        // {
        //     break;
        // }
        // default:
        // {
        // }
        // }
    }
}

void Client_GUI::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
}
