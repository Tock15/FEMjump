#ifndef WINPLATFORM_H
#define WINPLATFORM_H

#include "platform.h"
#include <QObject>

class WinPlatform : public Platform
{
    Q_OBJECT
public:
    explicit WinPlatform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);

signals:
};

#endif // WINPLATFORM_H
