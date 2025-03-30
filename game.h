#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "Player.h"

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
    void loadLevel1();
    void loadLevel2();
    void loadLevelendless();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:

    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player;
};

#endif // GAME_H
