#include "player_dashboard.h"
#include "ui_player_dashboard.h"

inline void init()
{
    Q_INIT_RESOURCE(pd_images);
}

inline void cleanUp()
{
    Q_CLEANUP_RESOURCE(pd_images);
}

Player_Dashboard::Player_Dashboard(const QString &file,
                                   QWidget *parent )
    : QSvgWidget(":/pd_images/player_dashboard.svg",parent),
      ui(new Ui::Player_Dashboard)
{
    init();
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

Player_Dashboard::~Player_Dashboard()
{
    delete ui;
}

void Player_Dashboard::on_pushButton_3_clicked()
{
    resize(size().width() + 20, size().height() + 30);
}

