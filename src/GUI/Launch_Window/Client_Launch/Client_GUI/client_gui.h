#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include <QWidget>

namespace Ui {
class Client_GUI;
}

class Client_GUI : public QWidget
{
    Q_OBJECT

public:
    explicit Client_GUI(QWidget *parent = nullptr);
    ~Client_GUI();

private:
    Ui::Client_GUI *ui;
};

#endif // CLIENT_GUI_H
