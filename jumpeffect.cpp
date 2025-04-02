#include "JumpEffect.h"
#include <QGraphicsScene>

JumpEffect::JumpEffect(qreal x, qreal y) {

    setPixmap(QPixmap(":/img/jump.png").scaled(40, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setPos(x, y);
    setOpacity(1.0);

    // Create and start a timer to update the jump effect
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &JumpEffect::updateEffect);
    timer->start(16);  // Update every 16ms (~60 FPS)
}

void JumpEffect::updateEffect() {
    // Move the jump effect particles upward
    setPos(x(), y() - 3);

    // Fade out the jump effect over time
    setOpacity(opacity() - 0.1);

    // Remove the jump effect after it fades out
    if (opacity() <= 0) {
        scene()->removeItem(this);
        delete this;  // Delete the jump effect object to free memory
    }
}
