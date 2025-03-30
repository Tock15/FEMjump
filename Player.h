#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QTimer>

class Player : public QGraphicsPixmapItem, public QObject{
private:
    QTimer *timer;
    int velocityY;
    bool isJumping;
private slots:
    void updatePosition();
public:
    Player();
    void goRight();
    void goLeft();
    void jump();
    void applyGravity();


};

#endif // PLAYER_H
