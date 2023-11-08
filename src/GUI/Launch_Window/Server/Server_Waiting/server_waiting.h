#ifndef SERVER_WAITING_H
#define SERVER_WAITING_H

#include <QWidget>

#include "server_creating.h"

namespace Ui
{
    class Server_Waiting;
}

class Server_Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Waiting(std::optional<Game_Server>& game_server,
                            QWidget *parent = nullptr);

    ~Server_Waiting();

private:
    std::optional<Game_Server> &_game_server;
    Ui::Server_Waiting *ui;
};

#endif // SERVER_WAITING_H
