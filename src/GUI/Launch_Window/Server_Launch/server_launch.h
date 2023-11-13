#ifndef SERVER_LAUNCH_H
#define SERVER_LAUNCH_H

#include <QWidget>

namespace Ui {
class Server_Launch;
}

class Server_Launch : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Launch(QWidget *parent = nullptr);
    ~Server_Launch();

private:
    int server_creating_index;
    int server_index;
    Ui::Server_Launch *ui;
};

#endif // SERVER_LAUNCH_H
