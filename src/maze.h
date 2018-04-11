#pragma once
#include <QTime>
#include <QPoint>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <iostream>
#include "globals.h"


class Maze
{
public:
    Maze();
    ~Maze();
    Maze(int w, int h);
    bool hasWallAt(char c, int x, int y);
    QPointF moveBall(char dir);
    bool hasWallBetween(int sx, int sy, int ex, int ey);
    QPointF getBallPos();
    QPointF getGoalPos();
    bool hasWon();
    void restart();
private:
    struct Node{
        int x, y;
        Maze::Node *left, *right, *up, *down;
    };
    bool hasWallBetween(Maze::Node* from, Maze::Node* to);
    std::vector<std::vector<Maze::Node*> > nodes;
    std::set<Maze::Node*> visited;
    std::vector<Maze::Node*> toVisit;
    std::vector<Maze::Node*> fromVisit;
    std::vector<std::vector<bool> > hLinesShow;
    std::vector<std::vector<bool> > vLinesShow;
    void walkMaze(Maze::Node* n);
    void createNodes();
    void deleteNodes();
    void createWalls();
    void breakWall(Maze::Node* from, Maze::Node* to);
    bool onToVisitList(Maze::Node* n);
    int w, h;
    Maze::Node* ballNode;
    Maze::Node* goalNode;
    void rebuildWalls();
};
