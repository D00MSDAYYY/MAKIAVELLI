#ifndef CLIENT_WAITING_H
#define CLIENT_WAITING_H

#include <QWidget>

namespace Ui {
class Client_Waiting;
}

class Client_Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Client_Waiting(QWidget *parent = nullptr);
    ~Client_Waiting();
signals:
    void shutDownButtonClicked();

private:
    Ui::Client_Waiting *ui;
};

#endif // CLIENT_WAITING_H
