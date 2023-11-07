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
    explicit Server_Waiting(Server_Creating *server_creating,
                            QWidget *parent = nullptr);
    ~Server_Waiting();

signals:
    void shutDownButtonClicked();

protected:
    void showEvent(QShowEvent *event) override;

private:
    std::unique_ptr<Game_Server> _game_server;
    
    Server_Creating *_server_creating;
    Ui::Server_Waiting *ui;
};

#endif // SERVER_WAITING_H
