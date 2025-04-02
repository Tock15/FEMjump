#ifndef JUMPEFFECT_H
#define JUMPEFFECT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class JumpEffect : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit JumpEffect(qreal x, qreal y);

private slots:
    void updateEffect();

private:
    QTimer *timer;
};

#endif // JUMPEFFECT_H
