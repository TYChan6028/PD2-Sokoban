#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // launch main menu
    launchMainMenu();
    // load background music
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/pink_panther_theme.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setMedia(playlist);
    music->setVolume(60);
    music->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchMainMenu()
{
    mainMenu = new MainMenu();
    setCentralWidget(mainMenu);
    mainMenu->setFocus();
    connect(mainMenu->startButton, &QPushButton::clicked,
            this, &MainWindow::onMMStartClicked);
    connect(mainMenu->resumeButton, &QPushButton::clicked,
            this, &MainWindow::onMMResumeClicked);
    connect(mainMenu->quitButton, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::onMMStartClicked()
{
    gameLevel = mainMenu->lvlSelect->currentIndex();
    launchGame(gameLevel);
}

void MainWindow::onMMResumeClicked()
{
    QFile myFile("savedgame.txt");
    if (!myFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File failed to open";
        qDebug() << myFile.errorString();
        return;
    }
    QTextStream in(&myFile);
    resumeGameBuffer.clear();
    int temp;
    while (!in.atEnd()) {
        in >> temp;
        resumeGameBuffer.push_back(temp);
    }
    myFile.close();
    loadResumeGame();
    return;
}

void MainWindow::loadResumeGame()
{
    int bufferIndex = resumeGameBuffer.size() - 1; // have to change when add highscore
    // load game level
    gameLevel = resumeGameBuffer[0];
    if (gameLevel == 0) {
        gameLvl0 = new GameLvl0();
        // load player position
        gameLvl0->player->setPos(resumeGameBuffer[1], resumeGameBuffer[2]);
        // load box positions
        for (int i=0; i<gameLvl0->boxPosList.size(); i+=2) {
            gameLvl0->boxList[i/2]->setPos(resumeGameBuffer[i+3], resumeGameBuffer[i+4]);
        }
        // set player step count
        gameLvl0->player->stepCount = resumeGameBuffer[bufferIndex];
    }
    else if (gameLevel == 1) {
        gameLvl1 = new GameLvl1();
        gameLvl1->player->setPos(resumeGameBuffer[1], resumeGameBuffer[2]);
        for (int i=0; i<gameLvl1->boxPosList.size(); i+=2) {
            gameLvl1->boxList[i/2]->setPos(resumeGameBuffer[i+3], resumeGameBuffer[i+4]);
        }
        gameLvl1->player->stepCount = resumeGameBuffer[bufferIndex];
    }
    launchGame(gameLevel);
    // set player step count on side menu
    sideMenu->stepCount->setNum(resumeGameBuffer[bufferIndex]);
    return;
}

void MainWindow::launchSideMenu()
{
    sideMenu = new SideMenu(centralWidget()->height());
//    sideMenu = new SideMenu(this);
    addDockWidget(Qt::RightDockWidgetArea, sideMenu);
    if (gameLevel == 0) {
        connect(gameLvl0->player, &Player::stepCountIsUpdated,
                sideMenu, &SideMenu::changeStepCount);
    }
    else if (gameLevel == 1) {
        connect(gameLvl1->player, &Player::stepCountIsUpdated,
                sideMenu, &SideMenu::changeStepCount);
    }
    connect(sideMenu->cheatCode, &QLineEdit::editingFinished,
            this, &MainWindow::onSMCheatCodeEditingFinished);
    connect(this, &MainWindow::gameSavedSuccessfully,
            sideMenu, &SideMenu::showGameSavedText);
    connect(sideMenu->saveButton, &QPushButton::clicked,
            this, &MainWindow::onSMSaveClicked);
    connect(sideMenu->backButton, &QPushButton::clicked,
            this, &MainWindow::onSMBackClicked);
    connect(sideMenu->quitButton, &QPushButton::clicked, this, &MainWindow::close);
    return;
}

void MainWindow::onSMCheatCodeEditingFinished()
{
    centralWidget()->setFocus();
    if (sideMenu->cheatCode->text() == "creeper") {
        emit validCheatCodeEntered();
        if (gameLevel == 0) {
            connect(gameLvl0->player, &Player::creeperExplode,
                    this, &MainWindow::explodeWall);
        }
        else if (gameLevel == 1) {
            connect(gameLvl1->player, &Player::creeperExplode,
                    this, &MainWindow::explodeWall);
        }
    }
}

void MainWindow::onSMSaveClicked()
{
    QFile myFile("savedgame.txt"); // ../test/output.txt
    if (!myFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "File failed to open";
        qDebug() << myFile.errorString();
        return;
    }
    // order: game lvl | player pos | box pos | step ct | top scores
    QTextStream out(&myFile);
    // game lvl
    out << gameLevel << "\t";
    if (gameLevel == 0) {
        // player pos
        out << gameLvl0->player->pos().x() << "\t";
        out << gameLvl0->player->pos().y() << "\t";
        // box pos
        for (int i=0; i<gameLvl0->boxList.size(); i++) {
            out << gameLvl0->boxList[i]->pos().x() << "\t";
            out << gameLvl0->boxList[i]->pos().y() << "\t";
        }
    }
    else if (gameLevel == 1) {
        // player pos
        out << gameLvl1->player->pos().x() << "\t";
        out << gameLvl1->player->pos().y() << "\t";
        // box pos
        for (int i=0; i<gameLvl1->boxList.size(); i++) {
            out << gameLvl1->boxList[i]->pos().x() << "\t";
            out << gameLvl1->boxList[i]->pos().y() << "\t";
        }
    }
    // step count
    out << sideMenu->stepCount->text().toInt();
    // close file
    myFile.flush();
    myFile.close();
    emit gameSavedSuccessfully();
    // return focus to game
    centralWidget()->setFocus();
}

void MainWindow::onSMBackClicked()
{
    if (gameLevel == 0) {
        delete gameLvl0;
        gameLvl0 = nullptr;
    }
    else if (gameLevel == 1) {
        delete gameLvl1;
        gameLvl1 = nullptr;
    }
    delete sideMenu;
    sideMenu = nullptr;
    launchMainMenu();
    setFixedSize(centralWidget()->width(), centralWidget()->height()+40);
    return;
}

void MainWindow::launchGame(int gameLvl)
{
    gameLevel = gameLvl;
    if (mainMenu) {
        delete mainMenu;
        mainMenu = nullptr;
    }
    if (sideMenu) {
        delete sideMenu;
        sideMenu = nullptr;
    }
    if (gameLevel == 0) {
        // instantiate new game
        if (!gameLvl0)
            gameLvl0 = new GameLvl0();
        setCentralWidget(gameLvl0);
        gameLvl0->setFocus();
        // connect
        connect(gameLvl0, &GameLvl0::restartGameLvl0, this, &MainWindow::gameRestart);
        connect(gameLvl0, &GameLvl0::winGame, this, &MainWindow::gameLevelUp);
        connect(this, &MainWindow::validCheatCodeEntered,
                gameLvl0->player, &Player::enableCreeperMode);
    }
    else if (gameLevel == 1) {
        if (!gameLvl1)
            gameLvl1 = new GameLvl1();
        setCentralWidget(gameLvl1);
        gameLvl1->setFocus();
        connect(gameLvl1, &GameLvl1::restartGameLvl1, this, &MainWindow::gameRestart);
        connect(gameLvl1, &GameLvl1::winGame, this, &MainWindow::gameLevelUp);
        connect(this, &MainWindow::validCheatCodeEntered,
                gameLvl1->player, &Player::enableCreeperMode);
    }
    launchSideMenu();
    setFixedSize(centralWidget()->width()+sideMenu->menuWidth+16,
                 centralWidget()->height()+40);
//    setFixedSize(centralWidget()->width()+sideMenu->menuWidth,
//                 centralWidget()->height());
    return;
}

void MainWindow::gameRestart(int gameLevel)
{
    if (gameLevel == 0) {
        delete gameLvl0;
        gameLvl0 = nullptr;
    }
    else if (gameLevel == 1) {
        delete gameLvl1;
        gameLvl1 = nullptr;
    }
    launchGame(gameLevel);
    return;
}

void MainWindow::gameLevelUp(int gameLevel)
{
    if (gameLevel == 0) {
        delete gameLvl0;
        gameLvl0 = nullptr;
        launchGame(gameLevel+1);
    }
    else if (gameLevel == 1) {
        delete gameLvl1;
        gameLvl1 = nullptr;
        launchMainMenu();
    }

    return;
}

void MainWindow::explodeWall(int playerXCoor, int playerYCoor)
{
    if (gameLevel == 0) {
        for (int i=0; i<gameLvl0->wallList.size(); i++) {
            Wall*& wall = gameLvl0->wallList[i];
            if (int(wall->x()-100) == playerXCoor && int(wall->y()) == playerYCoor) {
                delete wall;
                gameLvl0->wallList.remove(i);
            }
            else if (int(wall->x()+100) == playerXCoor && int(wall->y()) == playerYCoor) {
                delete wall;
                gameLvl0->wallList.remove(i);
            }
            else if (int(wall->x()) == playerXCoor && int(wall->y()-100) == playerYCoor) {
                delete wall;
                gameLvl0->wallList.remove(i);
            }
            else if (int(wall->x()) == playerXCoor && int(wall->y()+100) == playerYCoor) {
                delete wall;
                gameLvl0->wallList.remove(i);
            }
        }
    }
    else if (gameLevel == 1) {
        for (int i=0; i<gameLvl1->wallList.size(); i++) {
            Wall*& wall = gameLvl1->wallList[i];
            if (int(wall->x()-100) == playerXCoor && int(wall->y()) == playerYCoor) {
                delete wall;
                gameLvl1->wallList.remove(i);
            }
            else if (int(wall->x()+100) == playerXCoor && int(wall->y()) == playerYCoor) {
                delete wall;
                gameLvl1->wallList.remove(i);
            }
            else if (int(wall->x()) == playerXCoor && int(wall->y()-100) == playerYCoor) {
                delete wall;
                gameLvl1->wallList.remove(i);
            }
            else if (int(wall->x()) == playerXCoor && int(wall->y()+100) == playerYCoor) {
                delete wall;
                gameLvl1->wallList.remove(i);
            }
        }
    }
    return;
}

