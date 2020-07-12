#include "checkpoint.h"
#include <QBrush>
#include <QDebug>

Checkpoint::Checkpoint(int x, int y, int id)
{
    checkpointID = id;
    setRect(x, y, 20, 20);
    setBrush(QBrush(Qt::cyan));
}

void Checkpoint::checkAdjacentToBox()
{
    QList<QGraphicsItem*> collidedItems = collidingItems(Qt::IntersectsItemBoundingRect);
    for (int i=0; i<collidedItems.size(); ++i) {
        if (typeid(*(collidedItems[i])) == typeid(PushBox)) {
            emit statusUpdate(checkpointID, true);
            return;
        }
    };
    emit statusUpdate(checkpointID, false);
}
