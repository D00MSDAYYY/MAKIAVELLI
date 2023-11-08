#ifndef SERVER_CONSTRUCTOR_H
#define SERVER_CONSTRUCTOR_H

#include <QWidget>
#include <memory>

#include "game_server.hpp"

namespace Ui
{
    class Server_Creating;
}

class Server_Creating : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Creating(std::optional<Game_Server> &game_server,
                             QWidget *parent = nullptr);

    void createGameServer();

    ~Server_Creating();

private slots:
    void on_players_slider_valueChanged(int value);
    void on_bots_slider_valueChanged(int value);
    void on_rounds_slider_valueChanged(int value);
    void on_thinking_t_slider_valueChanged(int value);

private:
    std::optional<Game_Server> &_game_server;
    Ui::Server_Creating *ui;
};

#endif // SERVER_CONSTRUCTOR_H
