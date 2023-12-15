#ifndef SERVER_H
#define SERVER_H

#include "game_server.hpp"

#include <QWidget>
#include <optional>

namespace Ui
{
class Server_GUI;
}

class Server_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Server_GUI(QWidget* parent);
    ~Server_GUI();

    std::shared_ptr<Game_Server>&
    gameServer(std::optional<std::shared_ptr<Game_Server>> game_server = std::nullopt);

    void
    redraw();

private:
    std::shared_ptr<Game_Server> _game_server{nullptr};
    Ui::Server_GUI*              ui;
};

#endif  // SERVER_H
