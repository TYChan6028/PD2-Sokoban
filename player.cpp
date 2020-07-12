#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <gamelvl1.h>


Player::Player(int x, int y)
{
    this->setPos(x, y);
    QPixmap pic(":/resources/creeper.png");
    setPixmap(pic.scaled(102, 102));
    // load sound effect
    explodeSound = new QMediaPlayer();
    explodeSound->setMedia(QUrl("qrc:/resources/explosion.mp3"));
    explodeSound->setVolume(100);
}

void Player::keyPressEvent(QKeyEvent *e)
{
    QList<QGraphicsItem*> collidedItems = collidingItems(Qt::IntersectsItemBoundingRect);
    if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up) {
        if (checkCollideWithWall('U', collidedItems) == false
                && checkBoxPushable('U', collidedItems) == true) {
            setPos(x(), y()-100);
            emit stepCountIsUpdated(++stepCount);
            emit playerPosIsUpdated();
        }
    }
    else if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down) {
        if (checkCollideWithWall('D', collidedItems) == false
                && checkBoxPushable('D', collidedItems) == true) {
            setPos(x(), y()+100);
            emit stepCountIsUpdated(++stepCount);
            emit playerPosIsUpdated();
        }
    }
    else if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left) {
        if (checkCollideWithWall('L', collidedItems) == false
                && checkBoxPushable('L', collidedItems) == true) {
            setPos(x()-100, y());
            emit stepCountIsUpdated(++stepCount);
            emit playerPosIsUpdated();
        }
    }
    else if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right) {
        if (checkCollideWithWall('R', collidedItems) == false
                && checkBoxPushable('R', collidedItems) == true) {
            setPos(x()+100, y());
            emit stepCountIsUpdated(++stepCount);
            emit playerPosIsUpdated();
        }
    }
    else if (e->key() == Qt::Key_Space) {
        emit restartGame();
    }
    else if (e->key() == Qt::Key_Backspace && creeperMode == true) {
        if (explodeSound->state() == QMediaPlayer::PlayingState)
            explodeSound->setPosition(0);
        else
            explodeSound->play();
        emit creeperExplode(int(this->x()+1), int(this->y()+1));
    }
}

bool Player::checkCollideWithWall(const char& direction,
                                  const QList<QGraphicsItem*> &collidedItems)
{
    if (direction == 'U') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a wall
            if (typeid(*(collidedItems[i])) == typeid(Wall)) {
                // check if the wall is above him
                if (int(this->x()+1) == int(collidedItems[i]->x())
                        && int(this->y()-99) == int(collidedItems[i]->y())) {
                    return true;
                }
            }
        };
    }
    else if (direction == 'D') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a wall
            if (typeid(*(collidedItems[i])) == typeid(Wall)) {
                // check if the wall is below him
                if (int(this->x()+1) == int(collidedItems[i]->x())
                        && int(this->y()+101) == int(collidedItems[i]->y())) {
                    return true;
                }
            }
        };
    }
    else if (direction == 'L') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a wall
            if (typeid(*(collidedItems[i])) == typeid(Wall)) {
                // check if the wall is to the left of him
                if (int(this->x()-99) == int(collidedItems[i]->x())
                        && int(this->y()+1) == int(collidedItems[i]->y())) {
                    return true;
                }
            }
        };
    }
    else if (direction == 'R') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a wall
            if (typeid(*(collidedItems[i])) == typeid(Wall)) {
                // check if the wall is to the right of him
                if (int(this->x()+101) == int(collidedItems[i]->x())
                        && int(this->y()+1) == int(collidedItems[i]->y())) {
                    return true;
                }
            }
        };
    }
    return false;
}

bool Player::checkBoxPushable(const char &direction,
                              const QList<QGraphicsItem*> &collidedItems)
{
    if (direction == 'U') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a box within his vincinity
            if (typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // check if the box is above him
                if (int(this->x()) == int(collidedItems[i]->x())
                        && int(this->y()-100) == int(collidedItems[i]->y())) {
                    // check if there is something behind the box
                    emit collidedWithBox('U', int(collidedItems[i]->x()), int(collidedItems[i]->y()));
                    if (boxIsPushable == false)
                        return false;
                    else {

                    }
                }
            }
        };
    }
    else if(direction == 'D') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a box within his vincinity
            if (typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // check if the box is below him
                if (int(this->x()) == int(collidedItems[i]->x())
                        && int(this->y()+100) == int(collidedItems[i]->y())) {
                    // check if there is something behind the box
                    emit collidedWithBox('D', int(collidedItems[i]->x()), int(collidedItems[i]->y()));
                    if (boxIsPushable == false)
                        return false;
                    else {

                    }
                }
            }
        };
    }
    else if(direction == 'L') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a box within his vincinity
            if (typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // check if the box is to the left of him
                if (int(this->x()-100) == int(collidedItems[i]->x())
                        && int(this->y()) == int(collidedItems[i]->y())) {
                    // check if there is something to the left of the box
                    emit collidedWithBox('L', int(collidedItems[i]->x()), int(collidedItems[i]->y()));
                    if (boxIsPushable == false)
                        return false;
                    else {

                    }
                }
            }
        };
    }
    else if(direction == 'R') {
        for (int i=0; i<collidedItems.size(); ++i) {
            // check if player collided with a box within his vincinity
            if (typeid(*(collidedItems[i])) == typeid(PushBox)) {
                // check if the box is to the right of him
                if (int(this->x()+100) == int(collidedItems[i]->x())
                        && int(this->y()) == int(collidedItems[i]->y())) {
                    // check if there is something to the right of the box
                    emit collidedWithBox('R', int(collidedItems[i]->x()), int(collidedItems[i]->y()));
                    if (boxIsPushable == false)
                        return false;
                    else {

                    }
                }
            }
        };
    }
    return true;
}

void Player::enableCreeperMode()
{
    creeperMode = true;
}

void Player::receivePushableAns(bool ans)
{
    boxIsPushable = ans;
}
