#include "game.h"
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QKeyEvent>
Game::Game(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setFixedSize(1280, 720);
    scene->setSceneRect(0, 0, 1280, 720);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);
}
Game::~Game() {

}
void Game::clearScene() {
    scene->clear();
}

void Game::loadLevel1() {
    clearScene();
    QGraphicsRectItem *platform = new QGraphicsRectItem(0, 0, 100, 20);
    platform->setPos(100, 300);
    scene->addItem(platform);
    qDebug() << "Level 1 loaded";
}

void Game::loadLevel2() {
    clearScene();
    QGraphicsRectItem *platform = new QGraphicsRectItem(0, 0, 150, 20);
    platform->setPos(200, 350);
    scene->addItem(platform);
    qDebug() << "Level 2 loaded";
}

void Game::loadLevelendless() {
    clearScene();
    QGraphicsRectItem *platform = new QGraphicsRectItem(0, 0, 200, 20);
    platform->setPos(300, 400);
    scene->addItem(platform);
    qDebug() << "Endless loaded";
}
