#include "game.h"
#include "player.h"
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
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Game::handleMovement);
    leftKeyPressed = false;
    rightKeyPressed = false;
    // collisionTimer = new QTimer(this);
    // connect(collisionTimer, &QTimer::timeout, this, &Game::checkCollisions);
    // collisionTimer->start(7);
}
Game::~Game() {

}
//The jumping mechanice goes in the space  section for the case
// Design the levels in the loadlevel section and thats probably it for the game
// i might do the settings and like options to switch resolutions and fullscreen later as options in the settings
void Game::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_Space:
        if(event->isAutoRepeat()){
            event->ignore();
            break;
        }
        else{
            player->startChargingJump();
            qDebug() << "Start Charging here";
            break;
        }
    case Qt::Key_Escape:
        qDebug() << "Escape pressed";
        emit switchToLevel();
        break;
    case Qt::Key_A:
        leftKeyPressed = true;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);
        }
        break;
    case Qt::Key_D:
        rightKeyPressed = true;
        if (!moveTimer->isActive()) {
            moveTimer->start(16);
        }
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}
void Game::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_A:
        leftKeyPressed = false;
        if (!leftKeyPressed && !rightKeyPressed) {
            moveTimer->stop();
        }
        break;
    case Qt::Key_D:
        rightKeyPressed = false;
        if (!leftKeyPressed && !rightKeyPressed) {
            moveTimer->stop();
        }
        break;
    case Qt::Key_Space:
        player->releaseJump();
        break;
    default:
        QWidget::keyReleaseEvent(event);
        break;
    }
}

void Game::clearScene() {
    scene->clear();
}
void Game::handleMovement() {
    if (player && player->isChargingJump()) {
        return;
    }
    if (player && player->isJumping) {
        return;
    }
    if (leftKeyPressed) {
        player->goLeft();
    }
    if (rightKeyPressed) {
        player->goRight();
    }
}
void Game::loadLevel1() {
    clearScene();
    Platform *platform = new Platform(100, 600, 100, 20);
    Platform *platform2 = new Platform(220, 530, 100, 20);

    player = new Player();
    scene->addItem(player);
    scene->addItem(platform);
    scene->addItem(platform2);

    qDebug() << "Level 1 loaded";
}

void Game::loadLevel2() {
    clearScene();
    player = new Player();
    scene->addItem(player);
    Platform *platform = new Platform(100, 300, 100, 20);
    platform->setPos(200, 350);
    scene->addItem(platform);
    qDebug() << "Level 2 loaded";
}

void Game::loadLevelendless() {
    clearScene();
    Platform *platform = new Platform(100, 300, 100, 20);
    platform->setPos(300, 400);
    scene->addItem(platform);
    qDebug() << "Endless loaded";
}
// void Game::checkCollisions() {
//     if (!player)
//         return;

//     // get player 2d rectangular dimension
//     QRectF playerRect = player->sceneBoundingRect();

//     // check all items that player is colliding with
//     QList<QGraphicsItem*> collisions = player->collidingItems();
//     for (QGraphicsItem *item : collisions) {
//         if (Platform *plat = dynamic_cast<Platform*>(item)) {
//             QRectF platRect = plat->sceneBoundingRect();

//             // get the top and bottom to check if they pass
//             qreal playerBottom = playerRect.bottom();
//             qreal platTop = platRect.top();

//             // check if they overlap horiontally
//             bool horizontalOverlap = (playerRect.right() > platRect.left()) &&
//                                      (playerRect.left() < platRect.right());

//             //land if the player is falling.
//             if (player->getVelocityY() > 0 && horizontalOverlap) {
//                 if (playerBottom >= platTop && (playerBottom - player->getVelocityY()) < platTop) {
//                     player->setY(platTop - player->boundingRect().height());
//                     player->land();
//                 }
//             }
//         }
//     }
// }
// void Game::checkCollisions() {
//     if (!player) return;

//     QList<QGraphicsItem *> collidingItemsList = player->collidingItems();
//     for (QGraphicsItem *item : collidingItemsList) {
//         Platform *platform = dynamic_cast<Platform *>(item);
//         if (platform) {
//             QRectF playerRect = player->sceneBoundingRect();
//             QRectF platRect = platform->sceneBoundingRect();

//             qreal playerBottom = playerRect.bottom();
//             qreal platTop = platRect.top();
//             qreal playerPrevBottom = playerBottom - player->getVelocityY(); // Where the player was last frame
//             bool horizontalOverlap = (playerRect.right() > platRect.left()) &&
//                                      (playerRect.left() < platRect.right());

//             // Check if player is falling onto the platform
//             if (player->getVelocityY() > 0 && horizontalOverlap) {
//                 if (playerBottom >= platTop && playerPrevBottom < platTop) {
//                     player->setPos(player->x(), platTop - player->boundingRect().height());
//                     player->land();
//                     return;
//                 }
//             }
//         }
//     }
// }





