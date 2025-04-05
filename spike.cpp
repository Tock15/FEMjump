#include "spike.h"
#include <QPolygonF>
#include <QPointF>

Spike::Spike(QGraphicsItem *parent) : QObject(), QGraphicsPolygonItem(parent) {
    QPolygonF triangle;
    triangle << QPointF(0, 30)    // bottom left
             << QPointF(15, 0)    // top
             << QPointF(30, 30);  // bottom right

    setPolygon(triangle);
    setBrush(Qt::red);
    setPen(QPen(Qt::black, 1));
}
