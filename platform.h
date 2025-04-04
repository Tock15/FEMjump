#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class Platform : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Platform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // PLATFORM_H
