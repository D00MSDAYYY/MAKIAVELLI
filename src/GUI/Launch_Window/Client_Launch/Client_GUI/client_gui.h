#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <memory>
#include <QWidget>

#include "player_client.hpp"

namespace Ui {
class Client_GUI;
}

class Client_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Client_GUI(QWidget *parent = nullptr);
    ~Client_GUI();

private:
    std::shared_ptr<Player_Client> _player_client{nullptr};
    Ui::Client_GUI *ui;
};

#endif // CLIENT_GUI_H
