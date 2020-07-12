#include "gamelvl0.h"
#include <QDebug>

GameLvl0::GameLvl0(QWidget *parent)
{
    // create a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    // visualize scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    //create gamemap
    for (int i=0; i<floorPosList.size(); i+=2) { // floor
        floorList.push_back(new Floor(floorPosList[i], floorPosList[i+1]));
        scene->addItem(floorList[(i/2)]);
    }
    for (int i=0; i<wallPosList.size(); i+=2) { // wall
        wallList.push_back(new Wall(wallPosList[i], wallPosList[i+1]));
        scene->addItem(wallList[(i/2)]);
    }
    for (int i=0; i<checkpointPosList.size(); i+=2) { // checkpoint
        checkpointList.push_back(new Checkpoint(checkpointPosList[i], checkpointPosList[i+1], i/2));
        scene->addItem(checkpointList[(i/2)]);
    }
    for (int i=0; i<boxPosList.size(); i+=2) { // box
        boxList.push_back(new PushBox(boxPosList[i], boxPosList[i+1]));
        scene->addItem(boxList[(i/2)]);
    }

    // create the player inside scene
    player = new Player(299, 299);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add player to scene
    scene->addItem(player);

    // connect
    connect(player, &Player::restartGame, this, &GameLvl0::relayRestartSignal);
    connect(player, &Player::collidedWithBox, this, &GameLvl0::isBoxPushable);
    connect(this, &GameLvl0::returnPushableAns, player, &Player::receivePushableAns);
    for (int i=0; i<checkpointList.size(); ++i) {
        connect(player, &Player::playerPosIsUpdated,
                checkpointList[i], &Checkpoint::checkAdjacentToBox);
        connect(checkpointList[i], &Checkpoint::statusUpdate,
                this, &GameLvl0::updateCheckpointStatus);
    }

    // initialize checkpointStatus
    for (int i=0; i<checkpointList.size(); ++i)
        checkpointStatusList.push_back(false);

    // load sound effects
    checkpointSound = new QMediaPlayer();
    checkpointSound->setMedia(QUrl("qrc:/resources/push.mp3"));
    checkpointSound->setVolume(100);
    winSound = new QMediaPlayer();
    winSound->setMedia(QUrl("qrc:/resources/cheering.mp3"));
    winSound->setVolume(100);
}

void GameLvl0::checkWinningCondition()
{
    for (int i=0; i<checkpointStatusList.size(); ++i) {
        if (checkpointStatusList[i] == false)
            return;
    }
    winSound->play();
    emit winGame(0);
}

void GameLvl0::relayRestartSignal()
{
    emit restartGameLvl0(0);
}

void GameLvl0::isBoxPushable(const char& direction, int boxXCoor, int boxYCoor)
{
    for (int i=0; i<boxList.size(); ++i) {
        if (int(boxList[i]->x()) == boxXCoor && int(boxList[i]->y()) == boxYCoor) {
            emit returnPushableAns(boxList[i]->isPushable(direction));
        }
    }
}

void GameLvl0::updateCheckpointStatus(int checkpointIdx, bool newStatus)
{
    if (checkpointStatusList[checkpointIdx] != newStatus) {
        if (newStatus == true) {
            if (checkpointSound->state() == QMediaPlayer::PlayingState)
                checkpointSound->setPosition(0);
            else
                checkpointSound->play();
        }
        checkpointStatusList[checkpointIdx] = newStatus;
        checkWinningCondition();
    }

}

const QVector<int> GameLvl0::wallPosList =
{
    0, 0, 100, 0, 200, 0, 300, 0, 400, 0, 500, 0, 600, 0,
    0, 100, 600, 100,
    0, 200, 600, 200,
    0, 300, 600, 300,
    0, 400, 600, 400,
    0, 500, 600, 500,
    0, 600, 100, 600, 200, 600, 300, 600, 400, 600, 500, 600, 600, 600
};

const QVector<int> GameLvl0::floorPosList =
{
    0, 0, 100, 0, 200, 0, 300, 0, 400, 0, 500, 0, 600, 0,
    0, 100, 100, 100, 200, 100, 300, 100, 400, 100, 500, 100, 600, 100,
    0, 200, 100, 200, 200, 200, 300, 200, 400, 200, 500, 200, 600, 200,
    0, 300, 100, 300, 200, 300, 300, 300, 400, 300, 500, 300, 600, 300,
    0, 400, 100, 400, 200, 400, 300, 400, 400, 400, 500, 400, 600, 400,
    0, 500, 100, 500, 200, 500, 300, 500, 400, 500, 500, 500, 600, 500,
    0, 600, 100, 600, 200, 600, 300, 600, 400, 600, 500, 600, 600, 600
};

const QVector<int> GameLvl0::boxPosList =
{
    199, 199,
    399, 199,
    199, 399,
    399, 399
};

const QVector<int> GameLvl0::checkpointPosList =
{
    140, 140,
    540, 140,
    140, 540,
    540, 540
};
