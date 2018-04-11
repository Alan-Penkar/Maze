#include "ball.h"

Ball::Ball(){
    setFlag(ItemIsMovable);
    diameter = 10;
}

Ball::Ball(int s){
    setFlag(ItemIsMovable);
    diameter = s;
}

QRectF Ball::boundingRect() const{
    return QRectF(0,0,diameter,diameter);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();

    QBrush brush(Qt::blue);
    //brush.setStyle(Qt::RadialGradientPattern);
    painter->setBrush(brush);
    painter->drawEllipse(rect);

}

void Ball::moveBall(int dx, int dy){
    QPointF current = this->pos();
    if (current.x() + dx > 0 && current.y() + dy > 0){
        this->setPos(current.x() + dx, current.y() + dy);
    }
    update();
}

