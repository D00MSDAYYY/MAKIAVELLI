#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <memory>
#include <optional>
#include <QWidget>

#include <QGraphicsItemGroup>

#include "player_client.hpp"

namespace Ui
{
    class Client_GUI;
}

class Client_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Client_GUI(QWidget *parent = nullptr);
    ~Client_GUI();

    std::shared_ptr<Player_Client> &playerClient(std::optional<std::shared_ptr<Player_Client>> player_client = std::nullopt);

    void redraw();

private:
    std::shared_ptr<Player_Client> _player_client{nullptr};

    Ui::Client_GUI *ui;
};

#endif // CLIENT_GUI_H
