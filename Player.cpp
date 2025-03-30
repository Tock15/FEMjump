#include "Player.h"
#include <QDebug>
#include <qevent.h>
void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_A){
        qDebug() << "Go left";
    }
    switch(event->key()){
    case Qt::Key_A:
        qDebug() << "Go left";
    }
}
