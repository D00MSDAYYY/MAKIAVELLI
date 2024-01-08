#include "client_gui.h"

#include "player_dashboard.h"
#include "ui_client_gui.h"

#include <QBrush>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QRect>

inline void
init()
{
    Q_INIT_RESOURCE(cg_images);
}

inline void
cleanUp()
{
    Q_CLEANUP_RESOURCE(cg_images);
}

Client_GUI::Client_GUI(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::Client_GUI)
{
    init();
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    auto scene = new QGraphicsScene{this};
    scene->setSceneRect(0, 0, 1'920, 1'080);
    QPixmap pixmap{":/cg_images/background.svg"};
    scene->setBackgroundBrush(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    scene->addRect(0, 0, 1'920, 1'080);
}

Client_GUI::~Client_GUI() { delete ui; }

std::shared_ptr<Player_Client>&
Client_GUI::playerClient(std::optional<std::shared_ptr<Player_Client>> game_client)
{
    if(game_client) _game_client = *game_client;
    return _game_client;
}

void
Client_GUI::redraw()
{
    if(_game_client->countries().size() != _players_dashboards.size())
    {
        if(_game_client->countries().size() > _players_dashboards.size())
        {
            for(const auto& [ID, country]: _game_client->countries())
            {
                // if(!_players_dashboards.contains(ID))
                // _players_dashboards.insert({ID, new })
            }
        } }
}

void
Client_GUI::resizeEvent(QResizeEvent* event)
{
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
}
