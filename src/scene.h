#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGlobal>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <vector>
#include "globals.h"
#include "maze.h"
#include "ball.h"
#include <iostream>
#include <QKeyEvent>
#include <QPixmap>
#include <QtNumeric>


class MazeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MazeScene();
    ~MazeScene();
    qreal width();
    qreal height();
    void restart();

public slots:
    void keyEvent(QKeyEvent*);
    void restartEvent(QEvent*);

private:
    //void generateMaze();
    //arrays for the H and V lines.
    //hLines has size+1 rows and size columns
    //vLines has size rows and size +1 columns
    void reDraw();
    void reBuildWalls();
    std::vector<std::vector<QGraphicsLineItem*> > hLines;
    std::vector<std::vector<QGraphicsLineItem*> > vLines;
    void createItems();
    void buildWalls();
    void deleteWalls();
    void setGoal();
    //Logic Controller
    Maze* maze;

    //QGraphics Items
    Ball* ball;
    QGraphicsPixmapItem *goal;
};
