#include "Player.h"
#include <QDebug>
#include <qevent.h>
void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_A:
            qDebug() << "Go left";
            break;
        case Qt::Key_D:
            qDebug() << "Go right";
            break;
        case Qt::Key_Space:
            qDebug() << "Jump!";
            break;

    }
}
