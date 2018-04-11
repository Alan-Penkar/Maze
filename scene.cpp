#include "scene.h"
MazeScene::MazeScene() :
    QGraphicsScene(0, 0, (MAZE_SIZE+1)*TILE_SIZE +2,(MAZE_SIZE+1)*TILE_SIZE +2)
{
    this->setBackgroundBrush(Qt::white);
    maze = new Maze(MAZE_SIZE, MAZE_SIZE);
    buildWalls();
    ball = new Ball(TILE_SIZE-8);
    ball->setPos(5,5);
    this->addItem(ball);
    setGoal();
}
MazeScene::~MazeScene(){

    maze->~Maze();
    delete goal;
    delete ball;
}

qreal MazeScene::width(){
    return 2 + MAZE_SIZE * TILE_SIZE;
}

qreal MazeScene::height(){
    return 2 + MAZE_SIZE * TILE_SIZE;
}

void MazeScene::keyEvent(QKeyEvent* event){
    QPointF current = maze->getBallPos();
    switch(event->key() ) {
        case Qt::Key_Up:
            if (current != maze->moveBall('u')){
                ball->moveBall(0,-TILE_SIZE);
            }
            break;
        case Qt::Key_Down:
            if (current != maze->moveBall('d')){
                ball->moveBall(0,TILE_SIZE);
            }
            break;
        case Qt::Key_Left:
            if (current != maze->moveBall('l')){
                ball->moveBall(-TILE_SIZE, 0);
            }
            break;
        case Qt::Key_Right:
            if (current != maze->moveBall('r')){
                ball->moveBall(TILE_SIZE, 0);
            }
            break;
    }
    if (maze->hasWon()){
        std::cout << "You Won - Starting Over" << std::endl;
        restart();
    }

}

void MazeScene::restartEvent(QEvent *)
{
    restart();
}

void MazeScene::restart(){
    maze->restart();
    reDraw();
}

void MazeScene::reDraw(){
    reBuildWalls();
    ball->setPos(maze->getBallPos());
}

void MazeScene::reBuildWalls(){
    //vLines
    for (int i = 0; i < MAZE_SIZE + 1; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
                if (!maze->hasWallAt('v',i,j)){
                    vLines[i][j]->setVisible(false);
                } else {
                    vLines[i][j]->setVisible(true);
                }
        }
    }

    //hlines
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE + 1 ; j++) {
                if (!maze->hasWallAt('h',i,j)){
                    hLines[i][j]->setVisible(false);
                } else {
                    hLines[i][j]->setVisible(true);
                }
        }
    }
}

void MazeScene::buildWalls()
{
    int startX, startY, endX, endY;
    //vLines
    for (int i = 0; i < MAZE_SIZE + 1; i++) {
        std::vector<QGraphicsLineItem*> blank;
        vLines.push_back(blank);
        for (int j = 0; j < MAZE_SIZE; j++) {
                startX=1+TILE_SIZE*i;
                endX = 1+TILE_SIZE*i;
                startY = 1 + TILE_SIZE*j;
                endY = 1 + TILE_SIZE*(j+1);
                vLines[i].push_back(new QGraphicsLineItem(startX,startY,endX, endY));
                if (!maze->hasWallAt('v',i,j)){
                    vLines[i][j]->setVisible(false);
                }
                this->addItem(vLines[i][j]);
        }
    }

    //hlines
    for (int i = 0; i < MAZE_SIZE; i++) {
        std::vector<QGraphicsLineItem*> blank;
        hLines.push_back(blank);
        for (int j = 0; j < MAZE_SIZE + 1 ; j++) {
                startY=1+TILE_SIZE*j;
                endY = 1+TILE_SIZE*j;
                startX = 1 + TILE_SIZE*i;
                endX = 1 + TILE_SIZE*(i+1);
                hLines[i].push_back(new QGraphicsLineItem(startX,startY,endX, endY));
                if (!maze->hasWallAt('h',i,j)){
                    hLines[i][j]->setVisible(false);
                }
                this->addItem(hLines[i][j]);
        }
    }
}

void MazeScene::deleteWalls()
{
    //vLines
    for (int i = 0; i < MAZE_SIZE + 1; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            delete vLines[i][j];
        }
    }

    //hlines
    for (int i = 0; i < MAZE_SIZE ; i++) {
        for (int j = 0; j < MAZE_SIZE +1; j++) {
            delete hLines[i][j];
        }
    }
}

void MazeScene::setGoal()
{
    QPixmap *goalpix = new QPixmap(":/images/goal.png");
    QPixmap pic = goalpix->scaled(TILE_SIZE-1, TILE_SIZE-1);
    delete goalpix;
    goal = new QGraphicsPixmapItem(pic);
    QPointF gPos = maze->getGoalPos();
    gPos.setX((gPos.x()-1)*TILE_SIZE + 3);
    gPos.setY((gPos.y()-1)*TILE_SIZE + 3);
    goal->setPos(gPos);
    //goal->setZValue(1000);
    this->addItem(goal);
}
