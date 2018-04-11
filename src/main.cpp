#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtGui>
#include <QTime>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; //This is the view
    w.resize(w.centralWidget()->baseSize());
    w.show();

    return a.exec();
}
