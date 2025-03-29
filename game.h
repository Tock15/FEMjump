#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>


class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void clearScene();
public slots:
    void loadLevel1();
    void loadLevel2();
    void loadLevelendless();
private:

    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // GAME_H
