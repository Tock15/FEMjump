#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>

class Wall : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Wall(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    qreal getX();

signals:
private:
    qreal xPos;
};

#endif // WALL_H
