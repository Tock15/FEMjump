#include "Player.h"
#include <QDebug>
#include <qevent.h>

Player::Player(): velocityY(0), isJumping(false)
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
        isJumping = true;
    }
}
void Player::applyGravity(){
    velocityY += 1;  // Simulate gravity
    setPos(x(), y() + velocityY);
}
void Player::updatePosition() {
    applyGravity();

    if (y() > 600) {
        setPos(x(), 600);
        velocityY = 0;
        isJumping = false;  // Allow jumping again
    }
}
