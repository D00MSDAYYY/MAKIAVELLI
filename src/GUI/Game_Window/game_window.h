#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QWidget>

namespace Ui {
class Game_Window;
}

class Game_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Game_Window(QWidget *parent = nullptr);
    ~Game_Window();

private:
    Ui::Game_Window *ui;
};

#endif // GAME_WINDOW_H
