#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QTimer>

class Player : public QGraphicsPixmapItem, public QObject{
private:
    QTimer *timer;
    int velocityY;
    int velocityX;
    bool isJumping;
    bool landed;
    int facingDirection; // 0 = left 1 = right
private slots:
    void updatePosition();
public:
    Player();
    void goRight();
    void goLeft();
    void jump();
    void applyGravity();
    void land();
    int getVelocityY() const;
    void turn();


};

#endif // PLAYER_H
