#include "Player.h"
#include "platform.h"
#include <QDebug>
#include <qevent.h>

Player::Player(): velocityY(0), isJumping(false), landed(false), facingDirection(1),velocityX(0), jumpPower(0), chargingJump(false)
{
    setPixmap(QPixmap(":/img/astolfoR.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::updatePosition);
    timer->start(16); // Runs every 16ms (~60 FPS)
    jumpChargeTimer = new QTimer(this);
    connect(jumpChargeTimer, &QTimer::timeout, this, &Player::increaseJumpPower);
}

void Player::goRight()
{
    if(facingDirection == 0){
        turn();
    }
    facingDirection = 1;
    velocityX = 5;
    setPos(x()+5,y());
}

void Player::goLeft()
{
    if(facingDirection == 1){
        turn();
    }
    facingDirection = 0;
    velocityX = -5;
    setPos(x()-5,y());
}

void Player::jump()
{
    if (!isJumping) {  // Prevent double jumps
        velocityY = -15;
        landed = false;
        isJumping = true;
    }
}
void Player::applyGravity(){
    const int maxFallSpeed = 20;
    velocityY += 1;  // Simulate gravity
    if (velocityY > maxFallSpeed) {
        velocityY = maxFallSpeed;
    }

    setPos(x(), y() + velocityY);
}
void Player::updatePosition() {
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    bool isOnPlatform = false;

    for (QGraphicsItem *item : collidingItemsList) {
        Platform *platform = dynamic_cast<Platform *>(item);
        if (platform) {
            QRectF playerRect = sceneBoundingRect();
            QRectF platRect = platform->sceneBoundingRect();

            qreal playerBottom = playerRect.bottom();
            qreal platTop = platRect.top();
            //qreal playerPrevBottom = playerBottom - velocityY;

            bool horizontalOverlap = (playerRect.right() > platRect.left()) &&
                                     (playerRect.left() < platRect.right());

            // If player is falling and lands on the platform
            if (velocityY > 0 && horizontalOverlap && playerBottom >= platTop) {
                setPos(x(), platTop - boundingRect().height());
                land();
                landed = true;
                isOnPlatform = true;
                break;  // Exit the loop once we've landed
            }
        }
    }

    if (!landed || !isOnPlatform) {
        applyGravity();
    }
    if(isJumping){
        setPos(x() + velocityX, y());
    }

    if (y() > 600) {
        setPos(x(), 600);
        velocityY = 0;
        isJumping = false;  // Allow jumping again
    }
}
void Player::land() {
    velocityY = 0;
    isJumping = false;
}
int Player::getVelocityY() const {
    return velocityY;
}
void Player::turn(){
    if(facingDirection == 1){ // turn left
        setPixmap(QPixmap(":/img/astolfo.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(facingDirection == 0){ // turn right
        setPixmap(QPixmap(":/img/astolfoR.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
void Player::startChargingJump() {
    if (!isJumping) {
        chargingJump = true;
        jumpPower = 5; // Start with a minimum jump power
        velocityX = 0;
        jumpChargeTimer->start(25);
        qDebug() << "Jump charging started!";
    }
}

void Player::increaseJumpPower() {
    if (chargingJump && jumpPower < 50 ) { // Cap max power
        jumpPower++;
        if(facingDirection == 0 && velocityX >= -10){
            velocityX -=0.25;
        }
        else if(facingDirection == 1 && velocityX <=10){
            velocityX +=0.25;
        }
        qDebug() << "Charging jump power: " << jumpPower;
    }
}

void Player::releaseJump() {
    if (chargingJump) {
        velocityY = -jumpPower; // Apply charged jump
        isJumping = true;
        chargingJump = false;
        jumpPower = 0;
        jumpChargeTimer->stop();
        qDebug() << "Jump released! Power: " << velocityY;
    }
}
