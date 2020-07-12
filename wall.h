#ifndef WALL_H
#define WALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <player.h>

class Wall: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Wall(int x, int y);
};

#endif // WALL_H
