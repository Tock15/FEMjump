#include "Player.h"
#include "platform.h"
#include <QDebug>
#include <qevent.h>

Player::Player(): velocityY(0), isJumping(false), landed(false)
{
    setPixmap(QPixmap(":/img/astolfo.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::updatePosition);
    timer->start(16); // Runs every 16ms (~60 FPS)
}

void Player::goRight()
{
    setPos(x()+5,y());
}

void Player::goLeft()
{
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
            qreal playerPrevBottom = playerBottom - velocityY;

            bool horizontalOverlap = (playerRect.right() > platRect.left()) &&
                                     (playerRect.left() < platRect.right());

            // If player is falling and lands on the platform
            if (velocityY > 0 && horizontalOverlap && playerBottom >= platTop) {
                setPos(x(), platTop - boundingRect().height());
                land();
                landed = true;
                isOnPlatform = true;
                qDebug() << "Player landed";
                break;  // Exit the loop once we've landed
            }
        }
    }

    if (!landed || !isOnPlatform) {
        applyGravity();
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
