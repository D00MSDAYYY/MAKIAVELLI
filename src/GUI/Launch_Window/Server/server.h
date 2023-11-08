#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <optional>

#include "game_server.hpp"

namespace Ui
{
    class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private:
    std::optional<Game_Server> _game_server;
    Ui::Server *ui;
};

#endif // SERVER_H
