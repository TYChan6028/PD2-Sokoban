#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>

class MainMenu: public QGraphicsView
{
public:
    MainMenu();
    QLabel* title;
    QPushButton* startButton;
    QPushButton* resumeButton;
    QComboBox* lvlSelect;
    QPushButton* quitButton;

private:
    int viewW = 1016;
    int viewH = 900;
    int buttonW = 350;
    int buttonH = 70;
    int margin;
    int gap = 20;
};

#endif // MAINMENU_H
