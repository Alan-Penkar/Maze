#pragma once
#include <QGraphicsItem>
#include <QPainter>

class Ball : public QGraphicsItem
{
public:
    Ball();
    Ball(int s);
    //Override bounding box
    QRectF boundingRect() const;

    //Override Paint method
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem * option,
               QWidget* widget);
    void moveBall(int dx, int dy);
private:
    int diameter;
};

