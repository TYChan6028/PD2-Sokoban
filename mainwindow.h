#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "mainmenu.h"
#include "sidemenu.h"
#include "gamelvl0.h"
#include "gamelvl1.h"
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend int main(int argc, char *argv[]);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void launchMainMenu();
    void onMMStartClicked();
    void onMMResumeClicked();
    void loadResumeGame();
    void launchSideMenu();
    void onSMCheatCodeEditingFinished();
    void onSMSaveClicked();
    void onSMBackClicked();
    void launchGame(int gamLvl);
    void gameRestart(int gameLvl);
    void gameLevelUp(int gameLvl);
    void explodeWall(int playerXCoor, int playerYCoor);

signals:
    void gameSavedSuccessfully();
    void validCheatCodeEntered();

private:
    Ui::MainWindow *ui;
    MainMenu* mainMenu = nullptr;
    SideMenu* sideMenu = nullptr;
    GameLvl0* gameLvl0 = nullptr;
    GameLvl1* gameLvl1 = nullptr;
    int gameLevel;
    QVector<int> resumeGameBuffer;
    QMediaPlaylist* playlist;
    QMediaPlayer* music;
};

#endif // MAINWINDOW_H
