#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <thread>

#include "game_server.hpp"

namespace Ui
{
    class Server_GUI;
}

class Server_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Server_GUI(QWidget *parent ,
                    int play_num, int bot_num,
                    int rounds, int thinking_time,
                    uint16_t port = 0);
    ~Server_GUI();

private:
    std::shared_ptr<Game_Server> _game_server{};
    Ui::Server_GUI *ui;
};

#endif // SERVER_H
