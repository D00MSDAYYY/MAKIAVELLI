#ifndef CLIENT_CONNECTOR_H
#define CLIENT_CONNECTOR_H

#include <QWidget>

namespace Ui {
class Client_Connector;
}

class Client_Connector : public QWidget
{
    Q_OBJECT

public:
    explicit Client_Connector(QWidget *parent = nullptr);
    ~Client_Connector();
signals:
    void connectButtonClicked();

private:
    Ui::Client_Connector *ui;
};

#endif // CLIENT_CONNECTOR_H
