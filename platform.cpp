#include "platform.h"

Platform::Platform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
    //stone grey
    setBrush(QBrush(Qt::gray));
    #include <QPen>
}
