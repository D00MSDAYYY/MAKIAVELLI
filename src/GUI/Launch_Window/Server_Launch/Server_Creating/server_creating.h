#ifndef SERVER_CREATING_H
#define SERVER_CREATING_H

#include <QWidget>

#include "server_GUI.h"

namespace Ui {
class Server_Creating;
}

class Server_Creating : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Creating(QWidget *parent = nullptr);

    Server_GUI *createServer(QWidget *parent = nullptr);

    ~Server_Creating();

private slots:

    void on_players_slider_valueChanged(int value);
    void on_bots_slider_valueChanged(int value);
    void on_rounds_slider_valueChanged(int value);
    void on_thinking_t_slider_valueChanged(int value);

private:

    Ui::Server_Creating *ui;
};

#endif // SERVER_CREATING_H
