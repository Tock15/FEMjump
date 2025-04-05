#ifndef SPIKE_H
#define SPIKE_H

#include <QGraphicsPolygonItem>
#include <QObject>
#include <QBrush>
#include <QPen>

class Spike : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT
public:
    explicit Spike(qreal x, qreal y, QGraphicsItem *parent = nullptr);
};

#endif // SPIKE_H
