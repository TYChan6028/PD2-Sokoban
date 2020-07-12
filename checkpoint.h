#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include "pushbox.h"

class Checkpoint: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Checkpoint(int x, int y, int id);

public slots:
    void checkAdjacentToBox();

signals:
    void statusUpdate(int checkpointID, bool newStatus);

private:
    int checkpointID;
};

#endif // CHECKPOINT_H
