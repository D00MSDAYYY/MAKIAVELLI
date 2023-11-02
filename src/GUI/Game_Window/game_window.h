#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QWidget>

namespace Ui {
class player_window;
}

class Game_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Game_Window(QWidget *parent = nullptr);
    ~Game_Window();

private:
    Ui::player_window *ui;
};

#endif // GAME_WINDOW_H
