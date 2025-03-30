#include "game.h"
#include "Player.h"
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QKeyEvent>
Game::Game(QWidget *parent)
    : QWidget(parent), player(nullptr) //I set player as a private member of game class so we can call functions from it
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
//The jumping mechanice goes in the space  section for the case
// Design the levels in the loadlevel section and thats probably it for the game
// i might do the settings and like options to switch resolutions and fullscreen later as options in the settings
void Game::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Space:
        qDebug() << "Space pressed";
        break;
    case Qt::Key_Escape:
        qDebug() << "Escape pressed";
        emit switchToLevel();
        break;
    case Qt::Key_A:
        player->goLeft();
        qDebug() << "go left";
        break;
    case Qt::Key_D:
        player->goRight();
        qDebug() << "go right";
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}
void Game::clearScene() {
    scene->clear();
}

void Game::loadLevel1() {
    clearScene();
    // QGraphicsRectItem *platform = new QGraphicsRectItem(0, 0, 100, 20);
    // platform->setPos(100, 300);
    player = new Player();
    scene->addItem(player);
    qDebug() << "Level 1 loaded";
}

void Game::loadLevel2() {
    clearScene();
    player = new Player();
    scene->addItem(player);
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
