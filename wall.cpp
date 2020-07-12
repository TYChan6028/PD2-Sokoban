#include "wall.h"
#include <QDebug>

Wall::Wall(int x, int y)
{
    this->setPos(x, y);
    QPixmap pic(":/resources/brick.png");
    setPixmap(pic.scaled(100, 100));
}
