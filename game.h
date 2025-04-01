#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include "platform.h"
#include "player.h"
class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void clearScene();
signals:
    void switchToLevel();
public slots:
    void handleMovement();
    void loadLevel1();
    void loadLevel2();
    void loadLevelendless();
    // void checkCollisions();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    QTimer *moveTimer;
    bool leftKeyPressed;
    bool rightKeyPressed;
    QGraphicsScene *scene;
    QTimer *collisionTimer;
    QGraphicsView *view;
    Player *player;
};

#endif // GAME_H
