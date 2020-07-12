#include "pushbox.h"
#include <wall.h>
#include <QDebug>

PushBox::PushBox(int x, int y)
{
    this->setPos(x, y);
    QPixmap pic(":/resources/tnt_new.jpg");
    setPixmap(pic.scaled(102, 102));
}

bool PushBox::isPushable(const char& direction)
{
    QList<QGraphicsItem*> collidedItems = collidingItems(Qt::IntersectsItemBoundingRect);
    if (direction == 'U') {
        for (int i=0; i<collidedItems.size(); ++i) {
            if (typeid(*(collidedItems[i])) == typeid(Wall)
                    || typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // determine if there is a box above this item
                if (int(this->x()) == int(collidedItems[i]->x())
                        && int(this->y()-100) == int(collidedItems[i]->y())) {
//                    qDebug()<<collidedItems[i] << "is a box";
                    return false;
                }
                // determine if there is a wall above this item
                if (int(this->x()+1) == int(collidedItems[i]->x())
                        && int(this->y()-99) == int(collidedItems[i]->y())) {
//                    qDebug()<<collidedItems[i] << "is a wall";
                    return false;
                }
            }
        };
        // set new box position
        this->setPos(x(), y()-100);
        emit boxPosIsUpdated();
    }
    else if (direction == 'D') {
        for (int i=0; i<collidedItems.size(); ++i) {
            if (typeid(*(collidedItems[i])) == typeid(Wall)
                    || typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // determine if there is a box below this item
                if (int(this->x()) == int(collidedItems[i]->x())
                        && int(this->y()+100) == int(collidedItems[i]->y())) {
                    return false;
                }
                // determine if there is a wall below this item
                if (int(this->x()+1) == int(collidedItems[i]->x())
                        && int(this->y()+101) == int(collidedItems[i]->y())) {
                    return false;
                }
            }
        };
        // set new box position
        this->setPos(x(), y()+100);
        emit boxPosIsUpdated();
    }
    else if (direction == 'L') {
        for (int i=0; i<collidedItems.size(); ++i) {
            if (typeid(*(collidedItems[i])) == typeid(Wall)
                    || typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // determine if there is a box to the left of this item
                if (int(this->x()-100) == int(collidedItems[i]->x())
                        && int(this->y()) == int(collidedItems[i]->y())) {
                    return false;
                }
                // determine if there is a wall to the left of this item
                if (int(this->x()-99) == int(collidedItems[i]->x())
                        && int(this->y()+1) == int(collidedItems[i]->y())) {
                    return false;
                }
            }
        };
        // set new box position
        this->setPos(x()-100, y());
        emit boxPosIsUpdated();
    }
    else if (direction == 'R') {
        for (int i=0; i<collidedItems.size(); ++i) {
            if (typeid(*(collidedItems[i])) == typeid(Wall)
                    || typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // determine if there is a box to the right of this item
                if (int(this->x()+100) == int(collidedItems[i]->x())
                        && int(this->y()) == int(collidedItems[i]->y())) {
                    return false;
                }
                // determine if there is a wall to the right of this item
                if (int(this->x()+101) == int(collidedItems[i]->x())
                        && int(this->y()+1) == int(collidedItems[i]->y())) {
                    return false;
                }
            }
        };
        // set new box position
        this->setPos(x()+100, y());
        emit boxPosIsUpdated();
    }
    return true;
}
