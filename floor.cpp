#include "floor.h"

Floor::Floor(int x, int y)
{
    this->setPos(x, y);
    QPixmap pic(":/resources/floor.png");
    setPixmap(pic.scaled(100, 100));
}
