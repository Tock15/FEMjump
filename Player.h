#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>

class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    QTimer *timer;
    QTimer *jumpChargeTimer;
    int velocityY;
    double velocityX;
    bool landed;
    int facingDirection; // 0 = left 1 = right
    int jumpPower;
    bool chargingJump;
private slots:
    void updatePosition();
public:
    bool isChargingJump();
    Player();
    bool isJumping;
    void goRight();
    void goLeft();
    void jump();
    void applyGravity();
    void land();
    int getVelocityY() const;
    double getVelocityX();
    void setVelocityX(double newV);
    void turn();
    void startChargingJump();
    void increaseJumpPower();
    void releaseJump();
signals:
    void disableRight();
    void disableLeft();


};

#endif // PLAYER_H
