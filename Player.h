#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem{
private:

public:
    Player();
    void goRight();
    void goLeft();
    void Jump();

};

#endif // PLAYER_H
