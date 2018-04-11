#include "maze.h"

Maze::Maze()
{
    qsrand(QTime::currentTime().msec());
    w = MAZE_SIZE;
    h = MAZE_SIZE;
    createWalls();
}
Maze::Maze(int w_, int h_){
    qsrand(QTime::currentTime().msec());
    w = w_;
    h = h_;
    createWalls();
    createNodes();
    walkMaze(nodes[0][0]);
    ballNode = nodes[0][0];
    goalNode = nodes[w-1][h-1];
}

void Maze::restart(){
    rebuildWalls();
    visited = std::set<Maze::Node*>();
    std::cout << visited.size();
    walkMaze(nodes[0][0]);
    ballNode = nodes[0][0];
    goalNode = nodes[w-1][h-1];
}

Maze::~Maze(){
    deleteNodes();
}

void Maze::walkMaze(Maze::Node* n){
    visited.insert(n);
    int random;
    Maze::Node* ptr = nullptr;
    bool seenUp= false;
    bool seenDown= false;
    bool seenRight= false;
    bool seenLeft= false;
    //Checks all adjacent nodes in a random order to add to toVisit list if not on it
    //If there is a new node to visit- also placed on the path list
    while (!seenUp || !seenDown || !seenLeft || !seenRight){
        random = qrand() % 4;
        switch (random) {
        case 0:
            ptr = n->up;
            if (ptr != nullptr && visited.find(ptr) == visited.end() && !onToVisitList(ptr)){
                toVisit.push_back(ptr);
                fromVisit.push_back(n);
            }
            seenUp = true;
            break;
        case 1:
            ptr = n->left;
            if (ptr != nullptr && visited.find(ptr) == visited.end() && !onToVisitList(ptr)){
                toVisit.push_back(ptr);
                fromVisit.push_back(n);
            }
            seenLeft = true;
            break;
        case 2:
            ptr = n->right;
            if (ptr != nullptr && visited.find(ptr) == visited.end() && !onToVisitList(ptr)){
                toVisit.push_back(ptr);
                fromVisit.push_back(n);
            }
            seenRight = true;
            break;
        default:
            ptr = n->down;
            if (ptr != nullptr && visited.find(ptr) == visited.end() && !onToVisitList(ptr)){
                toVisit.push_back(ptr);
                fromVisit.push_back(n);
            }
            seenDown = true;
            break;
        }
    }
    //Visits the next node in the toVisit list if it is not empty
    if (toVisit.size() >0){
        Maze::Node *to = toVisit.back();
        Maze::Node *from = fromVisit.back();
        toVisit.pop_back();
        fromVisit.pop_back();
        breakWall(from, to);
        walkMaze(to);
    }
}

void Maze::breakWall(Maze::Node* from, Maze::Node* to){
    //std::cout << "Breaking wall from " << from->x << "," << from->y << " to " <<to->x << "," << to->y <<std::endl;
    if (from->x == to->x){
        //std::cout <<"Breaking hWall "<<from->x - 1 << "," << std::min(from->y, to->y) << std::endl;
        hLinesShow[from->x - 1][std::min(from->y, to->y)]= false;
    } else {
        //std::cout <<"Breaking vWall "<< std::min(from->x, to->x) << "," << from->y - 1 << std::endl;
        vLinesShow[std::min(from->x, to->x)][from->y - 1] = false;
    }

}

bool Maze::onToVisitList(Maze::Node* n){
    for (std::vector<Maze::Node*>::iterator it = toVisit.begin(); it!=toVisit.end() ;it++){
        if ( n == *it ){
            return true;
        }
    }
    return false;
}

void Maze::createNodes(){
    //Creates grid of Nodes w*h from 0: w-1, h-1
    //These are set up with x, y  NOT row, col
    for (int i=0; i<w; i++){
        std::vector<Maze::Node*> blank;
        nodes.push_back(blank);
        for (int j=0; j<h; j++){
            Node *tmp = new Node;
            tmp->x = i+1;
            tmp->y = j+1;
            tmp->right = nullptr;
            tmp->left = nullptr;
            tmp->up = nullptr;
            tmp->down = nullptr;
            //Set all the left nodes of current node (and reverse)
            if (i>0){
                tmp->left = nodes[i-1][j];
                nodes[i-1][j]->right = tmp;
            } else {
                tmp->left = nullptr;
            }

            //Set all the up nodes of current node (and reverse)
            if (j>0){
                tmp->up = nodes[i][j-1];
                nodes[i][j-1]->down = tmp;
            } else {
                tmp->up = nullptr;
            }
            nodes[i].push_back(tmp);
        }
    }

}

void Maze::deleteNodes(){
    Maze::Node* n = nodes[0][0];
    std::stack<Maze::Node*> killMe;
    killMe.push(n);
    while (killMe.size()>0){
        n = killMe.top();
        killMe.pop();
        if (n->y == 1 && n->right !=nullptr){
            killMe.push(n->right);
        } else if (n->y<10) {
            killMe.push(n->down);
        }
        delete n;
    }
}

void Maze::createWalls(){
    //vLines
    for (int i = 0; i < w + 1; i++) {
        std::vector<bool> blank;
        vLinesShow.push_back(blank);
        for (int j = 0; j < w; j++) {
            vLinesShow[i].push_back(true);
        }
    }

    //hlines
    for (int i = 0; i < w; i++) {
        std::vector<bool> blank;
        hLinesShow.push_back(blank);
        for (int j = 0; j < h + 1 ; j++) {
            hLinesShow[i].push_back(true);
        }
    }
}

void Maze::rebuildWalls(){
    //vLines
    for (int i = 0; i < w + 1; i++) {
        for (int j = 0; j < w; j++) {
            vLinesShow[i][j] = true;
        }
    }

    //hlines
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h + 1 ; j++) {
            hLinesShow[i][j] = true;
        }
    }
}


bool Maze::hasWallAt(char c, int x, int y){
    if (c=='h'){
        return hLinesShow[x][y];
    }else {
        return vLinesShow[x][y];
    }
}

bool Maze::hasWallBetween(Maze::Node* from, Maze::Node* to){
    if (from->x == to->x){
        return hasWallAt('h',from->x - 1, std::min(from->y, to->y));
    } else {
        return hasWallAt('v', std::min(from->x, to->x), to->y - 1);
    }
}

bool Maze::hasWallBetween(int sx, int sy, int ex, int ey){
    if (sx == ex){
        return hasWallAt('h',sx - 1, std::min(sy, ey));
    } else {
        return hasWallAt('v', std::min(sx, ex), ey - 1);
    }
}

QPointF Maze::getBallPos()
{
    return QPointF(ballNode->x, ballNode->y);
}

QPointF Maze::getGoalPos()
{
    return QPointF(goalNode->x, goalNode->y);
}

bool Maze::hasWon()
{
    return goalNode == ballNode;
}

QPointF Maze::moveBall(char dir)
{
    switch (dir) {
    case 'u':
        if (ballNode->up !=nullptr && !hasWallBetween(ballNode, ballNode->up)){
            ballNode = ballNode->up;
        }
        break;
    case 'd':
        if (ballNode->down !=nullptr && !hasWallBetween(ballNode, ballNode->down)){
            ballNode = ballNode->down;
        }
        break;
    case 'l':
        if (ballNode->left !=nullptr && !hasWallBetween(ballNode, ballNode->left)){
            ballNode = ballNode->left;
        }
        break;
    case 'r':
        if (ballNode->right !=nullptr && !hasWallBetween(ballNode, ballNode->right)){
            ballNode = ballNode->right;
        }
        break;
    default:
        break;
    }
    return QPointF(ballNode->x, ballNode->y);
}
