#include "Player.h"
#include <QDebug>
#include <qevent.h>

Player::Player()
{
    setPixmap(QPixmap(":/img/astolfo.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Player::goRight()
{
    setPos(x()+5,y());
}

void Player::goLeft()
{
    setPos(x()-5,y());
}

void Player::Jump()
{

}
