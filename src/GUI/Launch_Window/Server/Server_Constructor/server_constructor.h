#ifndef SERVER_CONSTRUCTOR_H
#define SERVER_CONSTRUCTOR_H

#include <QWidget>

namespace Ui
{
    class Server_Constructor;
}

class Server_Constructor : public QWidget
{
    Q_OBJECT

public:
    explicit Server_Constructor(QWidget *parent = nullptr);
    ~Server_Constructor();

private slots:
    void on_players_slider_valueChanged(int value);
    void on_bots_slider_valueChanged(int value);
    void on_rounds_slider_valueChanged(int value);
    void on_thinking_t_slider_valueChanged(int value);


signals:
    void createButtonClicked();

private:
    Ui::Server_Constructor *ui;
};

#endif // SERVER_CONSTRUCTOR_H
