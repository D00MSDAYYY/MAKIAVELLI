#ifndef SERVER_WAITING_H
#define SERVER_WAITING_H

#include <QWidget>

namespace Ui {
class Server_Waiting;
}

class Server_Waiting : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Waiting(QWidget *parent = nullptr);
    ~Server_Waiting();

private slots:
 
signals:
    void shutDownButtonClicked();

private:
    Ui::Server_Waiting *ui;
};

#endif // SERVER_WAITING_H
