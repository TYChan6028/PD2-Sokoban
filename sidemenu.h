#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QObject>
#include <QDockWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include "player.h"
#include <QDebug>

class SideMenu: public QDockWidget
{
    Q_OBJECT
    friend class MainWindow; friend int main(int argc, char *argv[]);
public:
    SideMenu(int height);
    QGraphicsView* scene;
    QLabel* countTopText;
    QLabel* stepCount;
    QLabel* countDownText;
    QLineEdit* cheatCode;
    QLabel* gameSavedText;
    QPushButton* saveButton;
    QPushButton* backButton;
    QPushButton* quitButton;

public slots:
    void changeStepCount(int newStepCount);
    void showGameSavedText();

private:
    int menuWidth;
    int menuHeight;
};

#endif // SIDEMENU_H
