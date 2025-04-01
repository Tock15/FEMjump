#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QTimer>

class Player : public QGraphicsPixmapItem, public QObject{
private:
    QTimer *timer;
    int velocityY;
    bool isJumping;
    bool landed;
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


};

#endif // PLAYER_H
