#include "server_GUI.h"
#include "ui_server_GUI.h"

Server_GUI::Server_GUI(QWidget *parent,
                       int play_num, int bot_num,
                       int rounds, int thinking_time,
                       uint16_t port)
    : QWidget(parent),
      ui(new Ui::Server_GUI)
{
    ui->setupUi(this);
    _game_server = std::shared_ptr<Game_Server>{
        new Game_Server{play_num, bot_num, rounds, thinking_time}};
}

Server_GUI::~Server_GUI()
{
    std::cerr << "server GUI destr=======" << std::endl;
    _game_server.reset();
    delete ui;
}
