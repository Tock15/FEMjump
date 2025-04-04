#include "wall.h"

Wall::Wall(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x,y,width,height)
{
    xPos = x;
    setBrush(QBrush(Qt::gray));
    setPen(QPen(Qt::NoPen));
}

qreal Wall::getX(){
    return xPos;
}
