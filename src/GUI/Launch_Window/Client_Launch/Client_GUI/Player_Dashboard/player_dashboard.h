#ifndef PLAYER_DASHBOARD_H
#define PLAYER_DASHBOARD_H

#include <QSvgWidget>

namespace Ui
{
class Player_Dashboard;
}

class Player_Dashboard : public QSvgWidget
{
    Q_OBJECT

public:
    explicit Player_Dashboard(QWidget* parent = nullptr);
    ~Player_Dashboard();

    int
    army(std::optional<int> points = std::nullopt);
    int
    science(std::optional<int> points);
    std::pair<int, int>
    oil(std::optional<int> points    = std::nullopt,
        std::optional<int> resources = std::nullopt);
    std::pair<int, int>
    mineral(std::optional<int> points    = std::nullopt,
            std::optional<int> resources = std::nullopt);
    std::pair<int, int>
    farm(std::optional<int> points    = std::nullopt,
         std::optional<int> resources = std::nullopt);
    std::pair<int, int>
    industry(std::optional<int> points    = std::nullopt,
             std::optional<int> resources = std::nullopt);

    int
    index(std::optional<int> index = std::nullopt);

private:
    //! group of points
    int                   _index{0};

    Ui::Player_Dashboard* ui;
};

#endif  // PLAYER_DASHBOARD_H
