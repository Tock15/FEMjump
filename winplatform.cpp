#include "winplatform.h"

WinPlatform::WinPlatform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : Platform(x, y, width, height, parent)
{
    setBrush(QBrush(Qt::green));
}
