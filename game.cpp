#include "game.h"
#include "jumpeffect.h"
#include "player.h"
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QKeyEvent>
#include <vector>
Game::Game(SettingsManager *settingsManager,QWidget *parent)
    : QWidget(parent), player(nullptr), settingsManager(settingsManager) //I set player as a private member of game class so we can call functions from it
{
    setFocusPolicy(Qt::StrongFocus);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setFixedSize(650, 720);
    scene->setSceneRect(0, 0, 600, 2000);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);  // Ensure the QGraphicsView is centered
    layout->addWidget(view);
    view->centerOn(0, scene->sceneRect().bottom());
    setLayout(layout);
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Game::handleMovement);
    leftKeyPressed = false;
    rightKeyPressed = false;
    jumpSound = new QSoundEffect(this);
    jumpSound->setSource(QUrl("qrc:/sounds/jumpSound.wav"));
    jumpSound->setVolume(settingsManager->audioVolume() / 100.0f);
    collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &Game::checkCollisions);
    collisionTimer->start(7);
}
Game::~Game() {

}
void Game::setJumpSoundVolume(float volume) {
    if (jumpSound) {
        jumpSound->setVolume(volume);
    }
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
        player->startChargingJump();
        qDebug() << "Start Charging here";
        break;
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
        JumpEffect *effect = new JumpEffect(player->x()+10, player->y()+50);
        scene->addItem(effect);
        jumpSound->play();
        break;
    }
}



void Game::clearScene() {
    scene->clear();
}

void Game::handleMovement() {
    checkCollisions();
    if (player && player->isChargingJump()) {
        return;
    }
    if (player && player->isJumping) {
        return;
    }
    if (leftKeyPressed && !noLeft) {
        if (player->x() <= -30) {
            return;
        }
        player->goLeft();
    }
    if (rightKeyPressed && !noRight) {
        if (player->x() >= 620 - player->boundingRect().width()) {
            return;
        }
        player->goRight();
    }
}
void Game::loadLevel1() {
    clearScene();
    std::vector<Platform*> platforms;
    //platforms.push_back(new Platform(100, 1900, 100, 20));
    platforms.push_back(new Platform(420, 1700, 100, 20));
    platforms.push_back(new Platform(450, 1500, 100, 20));
    platforms.push_back(new Platform(50, 1300, 100, 20));
    platforms.push_back(new Platform(420, 1100, 50, 20));
    Wall *wall1 = new Wall(200, 1500, 20, 500);
    scene->addItem(wall1);


    player = new Player();
    scene->addItem(player);
    connect(player, &Player::disableLeft, this, &Game::onDisableLeft);
    connect(player, &Player::disableRight, this, &Game::onDisableRight);
    for(auto p : platforms){
        scene->addItem(p);
    }

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
    player = new Player();
    scene->addItem(player);
    Platform *platform = new Platform(100, 300, 100, 20);
    platform->setPos(300, 400);
    scene->addItem(platform);
    qDebug() << "Endless loaded";
}

void Game::onDisableRight()
{
    noRight = true;
}
void Game::onDisableLeft(){
    noLeft = true;
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
void Game::checkCollisions() {
    if (!player) return;

    bool touchingLeftWall = false;
    bool touchingRightWall = false;

    QList<QGraphicsItem *> collidingItemsList = player->collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        if (Wall *wall = dynamic_cast<Wall *>(item)) {
            QRectF playerRect = player->sceneBoundingRect();
            QRectF wallRect = wall->sceneBoundingRect();

            if (playerRect.right() >= wallRect.left() && playerRect.left() < wallRect.left()) {
                touchingRightWall = true;
            }
            if (playerRect.left() <= wallRect.right() && playerRect.right() > wallRect.right()) {
                touchingLeftWall = true;
            }
        }
    }

    // Disable movement when colliding
    if (touchingLeftWall) {
        onDisableLeft();
    } else {
        noLeft = false;
    }

    if (touchingRightWall) {
        onDisableRight();
    } else {
        noRight = false;
    }
}






