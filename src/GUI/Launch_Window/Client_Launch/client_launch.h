#ifndef CLIENT_LAUNCH_H
#define CLIENT_LAUNCH_H

#include "client_gui.h"

#include <QWidget>

namespace Ui
{
class Client_Launch;
}

class Client_Launch : public QWidget
{
    Q_OBJECT

public:
    explicit Client_Launch(QWidget* parent = nullptr);
    ~Client_Launch();

private:
    Ui::Client_Launch* ui;
};

#endif  // CLIENT_LAUNCH_H
