#include "mainmenu.h"

MainMenu::MainMenu()
{
    setFixedSize(viewW, viewH);
    // load buttons
    title = new QLabel("Sokoban", this);
    startButton = new QPushButton("START", this);
    resumeButton = new QPushButton("RESUME", this);
    lvlSelect = new QComboBox(this);
    lvlSelect->addItem("                    LEVEL 0");
    lvlSelect->addItem("                    LEVEL 1");
    quitButton = new QPushButton("QUIT", this);
    // set font style
    QFont font1("Arial", 80, QFont::Black);
    title->setFont(font1);
    title->setAlignment(Qt::AlignCenter);
    QFont font2("Ubuntu", 16, QFont::Normal);
    startButton->setFont(font2);
    resumeButton->setFont(font2);
    lvlSelect->setFont(font2);
    quitButton->setFont(font2);
    // set button geometry
    margin = (viewW - buttonW*2 - gap) / 2;
    title->setGeometry(margin, viewH/2-200, viewW-margin*2, 200);
    startButton->setGeometry(margin, viewH/2+margin, buttonW, buttonH);
    resumeButton->setGeometry(startButton->x()+buttonW+gap, viewH/2+margin, buttonW, buttonH);
    lvlSelect->setGeometry(margin, startButton->y()+buttonH+gap, buttonW, buttonH);
    quitButton->setGeometry(resumeButton->x(), lvlSelect->y(), buttonW, buttonH);
}
