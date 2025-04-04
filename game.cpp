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
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    bgAudio = new QAudioOutput(this);
    bgAudio->setVolume(settingsManager->audioVolume() / 100.0f);

    bgAudio = new QAudioOutput(this);
    bgAudio->setVolume(settingsManager->audioVolume() / 100.0f);

    bgMusic = new QMediaPlayer(this);
    bgMusic->setAudioOutput(bgAudio);

    musicTracks << "qrc:/music/theme1.mp3" << "qrc:/music/theme2.mp3" << "qrc:/music/theme3.mp3";

    bgMusic->setSource(QUrl(musicTracks[currentTrackIndex]));
    bgMusic->play();
    connect(bgMusic, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            currentTrackIndex = (currentTrackIndex + 1) % musicTracks.size();  // Loop
            bgMusic->setSource(QUrl(musicTracks[currentTrackIndex]));
            bgMusic->play();
        }
    });
}
void Game::setMusicVolume(float volume) {
    if (bgAudio) {
        bgAudio->setVolume(volume);
    }
}
Game::~Game() {
    if (bgMusic) {
        bgMusic->stop();
        bgMusic->setSource(QUrl());
        bgMusic->disconnect();
    }

    if (bgAudio) {
        delete bgAudio;
        bgAudio = nullptr;
    }
qDebug() << "bgMusic status:" << bgMusic->mediaStatus();
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
    std::vector<Wall*> walls;
    platforms.push_back(new Platform(-25, 1950, 650, 20)); //spawn

    // Platforms and wall go together in pairs where platform y = wall's y - platform's height
    platforms.push_back(new Platform(-25, 1780, 200, 20));
    walls.push_back(new Wall(-25, 1800, 200, 200));

    platforms.push_back(new Platform(450, 1780, 200, 20));
    walls.push_back(new Wall(450, 1800, 200, 200));

    platforms.push_back(new Platform(175,1580,270,20));
    walls.push_back(new Wall(175,1600,270,20));









    player = new Player();
    scene->addItem(player);
    player->setPos(300,1750);
    connect(player, &Player::disableLeft, this, &Game::onDisableLeft);
    connect(player, &Player::disableRight, this, &Game::onDisableRight);

    for(auto p : platforms){
        scene->addItem(p);
    }
    for(auto w : walls){
        scene->addItem(w);
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






