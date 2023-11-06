#ifndef PLAYER_WINDOW_H
#define PLAYER_WINDOW_H

#include <QWidget>

namespace Ui {
class Player_Window;
}

class Player_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Player_Window(QWidget *parent = nullptr);
    ~Player_Window();

private:
    Ui::Player_Window *ui;
};

#endif // PLAYER_WINDOW_H
