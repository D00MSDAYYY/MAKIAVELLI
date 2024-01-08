#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include "game_client.hpp"

#include <QWidget>

namespace Ui
{
class Client_GUI;
}

class Client_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Client_GUI(QWidget* parent = nullptr);
    ~Client_GUI();

    std::shared_ptr<Player_Client>&
    playerClient(
        std::optional<std::shared_ptr<Player_Client>> game_client = std::nullopt);

    void
    redraw();

private:
    void
    resizeEvent(QResizeEvent* event);

private:
    std::shared_ptr<Player_Client>                 _game_client{nullptr};
    std::unordered_map<int, QGraphicsProxyWidget*> _players_dashboards{};
    Ui::Client_GUI*                                ui;
};

#endif  // CLIENT_GUI_H
