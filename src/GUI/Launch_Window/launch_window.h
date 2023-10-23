#ifndef LAUNCH_WINDOW_H
#define LAUNCH_WINDOW_H

#include <QDialog>
#include <QStackedWidget>

namespace Ui {
class Launch_Window;
}

class Launch_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Launch_Window(QWidget *parent = nullptr);
    ~Launch_Window();

private:
    Ui::Launch_Window *ui;
};

#endif // LAUNCH_WINDOW_H
