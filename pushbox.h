#ifndef PUSHBOX_H
#define PUSHBOX_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <player.h>

class PushBox: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PushBox(int x, int y);
    bool isPushable(const char& direction);

signals:
    void boxPosIsUpdated();
};

#endif // PUSHBOX_H
