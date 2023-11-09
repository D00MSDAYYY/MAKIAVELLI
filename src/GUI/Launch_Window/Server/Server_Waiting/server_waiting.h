#ifndef SERVER_WAITING_H
#define SERVER_WAITING_H

#include <QWidget>

#include <atomic>

#include "server_creating.h"

namespace Ui
{
    class Server_Waiting;
}

class Server_Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Waiting(QWidget *parent = nullptr);

    void startUpdatingInfo(const std::shared_ptr<Game_Server> &game_server);
    void finishUpdatingInfo();
    ~Server_Waiting();

private:
    std::atomic<bool> is_active{false};
    Ui::Server_Waiting *ui;
};

#endif // SERVER_WAITING_H
