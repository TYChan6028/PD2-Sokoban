#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QList>
#include <QMediaPlayer>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    friend class MainWindow;
public:
    Player(int x, int y);
    void keyPressEvent(QKeyEvent *e);
    bool checkCollideWithWall(const char& direction,
                              const QList<QGraphicsItem*> &collidedItems);
    bool checkBoxPushable(const char& direction,
                          const QList<QGraphicsItem*> &collidedItems);

public slots:
    void enableCreeperMode();
    void receivePushableAns(bool ans);

signals:
    void creeperExplode(int playerXCoor, int playerYCoor);
    void collidedWithBox(const char& direction, int boxXCoor, int BoxYCoor);
    void stepCountIsUpdated(int stepCount);
    void playerPosIsUpdated();
    void restartGame();

private:
    int stepCount = 0;
    bool creeperMode = false;
    bool boxIsPushable;
    QMediaPlayer* explodeSound;
};

#endif // PLAYER_H
