#ifndef GAMELVL0_H
#define GAMELVL0_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include "player.h"
#include "wall.h"
#include "pushbox.h"
#include "floor.h"
#include "checkpoint.h"
#include <QVector>

class GameLvl0: public QGraphicsView
{
    Q_OBJECT
    friend class MainWindow;
public:
    GameLvl0(QWidget *parent = nullptr);
    void checkWinningCondition();
    static const QVector<int> wallPosList;
    static const QVector<int> floorPosList;
    static const QVector<int> checkpointPosList;
    static const QVector<int> boxPosList;

public slots:
    void relayRestartSignal();
    void isBoxPushable(const char& direction, int boxXCoor, int boxYCoor);
    void updateCheckpointStatus(int checkpointIdx, bool newStatus);

signals:
    void winGame(int gameLevel);
    void restartGameLvl0(int gameLevel);
    void returnPushableAns(bool ans);

private:
    QGraphicsScene *scene;
    Player* player;
    int viewWidth = 800;
    int viewHeight = 900;
    int sceneWidth = 700;
    int sceneHeight = 700;
    QVector<Wall*> wallList;
    QVector<Floor*> floorList;
    QVector<Checkpoint*> checkpointList;
    QVector<PushBox*> boxList;
    QVector<bool> checkpointStatusList;
    QMediaPlayer* checkpointSound;
    QMediaPlayer* winSound;
};

#endif // GAMELVL0_H
