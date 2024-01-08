#ifndef PLAYER_DASHBOARD_H
#define PLAYER_DASHBOARD_H

#include <QSvgWidget>

namespace Ui
{
class Player_Dashboard;
}

class Player_Dashboard : public QSvgWidget
{
    Q_OBJECT

public:
    explicit Player_Dashboard(QWidget* parent = nullptr);
    ~Player_Dashboard();

private:
    //! group of points
    int                   _index{0};

    Ui::Player_Dashboard* ui;
};

#endif  // PLAYER_DASHBOARD_H
