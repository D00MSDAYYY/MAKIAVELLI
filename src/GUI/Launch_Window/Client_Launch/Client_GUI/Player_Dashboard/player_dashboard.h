#ifndef PLAYER_DASHBOARD_H
#define PLAYER_DASHBOARD_H

#include <QWidget>

namespace Ui {
class Player_Dashboard;
}

class Player_Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Player_Dashboard(QWidget *parent = nullptr);
    ~Player_Dashboard();

private:
    Ui::Player_Dashboard *ui;
};

#endif // PLAYER_DASHBOARD_H
