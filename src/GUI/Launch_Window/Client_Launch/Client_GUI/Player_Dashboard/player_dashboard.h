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
    explicit Player_Dashboard(const QString &file,
                              QWidget *parent = nullptr);
    ~Player_Dashboard();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::Player_Dashboard *ui;
};

#endif // PLAYER_DASHBOARD_H
