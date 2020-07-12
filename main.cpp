#include "mainwindow.h"
#include <QApplication>
//#include <QDesktopWidget>
#include <QDebug>
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QDesktopWidget dw;
    MainWindow w;
    w.show();
//    int x = dw.width()*0.9;
//    int y = dw.height();
//    w.setFixedSize(x, y);
//    QLayout::setSizeConstraint(QLayout::SetFixedSize);
    return a.exec();

}
