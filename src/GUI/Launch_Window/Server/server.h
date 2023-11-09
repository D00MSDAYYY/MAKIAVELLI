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
    std::shared_ptr<Game_Server> _game_server{nullptr};
    Ui::Server *ui;
};

#endif // SERVER_H
