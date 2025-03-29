#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem{
private:

public:
    void keyPressEvent(QKeyEvent * event);

};

#endif // PLAYER_H
