#include "sidemenu.h"

SideMenu::SideMenu(int height)
    : menuWidth(200), menuHeight(height)
{
    setAllowedAreas(Qt::RightDockWidgetArea);
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    scene = new QGraphicsView(this);

//    this->setWidget(scene);
//    scene->setGeometry(0, 0, menuWidth, menuHeight);

    scene->setFixedSize(menuWidth, menuHeight); //
//    setGeometry(0, 0, menuWidth, menuHeight);
    // add step counter
    int counterX = 100;
    stepCount = new QLabel(scene);
    stepCount->setGeometry(0, counterX+30, menuWidth, 100);
    stepCount->setText("0");
    QFont font("Arial", 30, QFont::Normal);
    stepCount->setFont(font);
    stepCount->setAlignment(Qt::AlignCenter);
    // add text above counter
    countTopText = new QLabel(scene);
    countTopText->setGeometry(0, counterX, menuWidth, 50);
    countTopText->setText("You took");
    countTopText->setAlignment(Qt::AlignCenter);
    // add text below counter
    countDownText = new QLabel(scene);
    countDownText->setGeometry(0, counterX+110, menuWidth, 50);
    countDownText->setText("steps");
    countDownText->setAlignment(Qt::AlignCenter);
    // add cheat code input bar
    cheatCode = new QLineEdit(scene);
    cheatCode->setGeometry(20, menuHeight-340, 160, 50);
    cheatCode->setPlaceholderText("Enter Cheat Code: ");
    cheatCode->setAlignment(Qt::AlignCenter);
    // add game saved pop up text
    gameSavedText = new QLabel(scene);
    gameSavedText->setGeometry(0, menuHeight-290, menuWidth, 50);
    gameSavedText->hide();
    gameSavedText->setText("GAME SAVED");
    gameSavedText->setAlignment(Qt::AlignCenter);
    // add save button
    saveButton = new QPushButton("SAVE", scene);
    saveButton->setGeometry(20, menuHeight-240, 160, 50);
    // add back button
    backButton = new QPushButton("BACK", scene);
    backButton->setGeometry(20, menuHeight-170, 160, 50);
    // add quit button
    quitButton = new QPushButton("QUIT", scene);
    quitButton->setGeometry(20, menuHeight-100, 160, 50);
}

void SideMenu::changeStepCount(int newStepCount)
{
    stepCount->setNum(newStepCount);
}

void SideMenu::showGameSavedText()
{
    gameSavedText->show();
    QTimer* timer = new QTimer(gameSavedText);
    connect(timer, &QTimer::timeout, gameSavedText, &QLabel::hide);
    timer->start(1000);
}
