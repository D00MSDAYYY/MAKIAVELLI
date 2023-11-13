#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

#include "game_server.hpp"

namespace Ui
{
    class Server;
}

class Server : public QWidget, public Game_Server
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent ,
                    int play_num, int bot_num,
                    int rounds, int thinking_time,
                    uint16_t port = 0);
    ~Server();

private:
    Ui::Server *ui;
};

#endif // SERVER_H
