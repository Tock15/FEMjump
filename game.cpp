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
    if (leftKeyPressed && !noLeft && !win) {
        if (player->x() <= -30) {
            return;
        }
        player->goLeft();
    }
    if (rightKeyPressed && !noRight && !win) {
        if (player->x() >= 620 - player->boundingRect().width()) {
            return;
        }
        player->goRight();
    }
}
void Game::loadLevel1() {
    win = false;
    winTextItem = nullptr;
    scene->removeItem(winTextItem);
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

    platforms.push_back(new Platform(425,1380,100,20));
    walls.push_back(new Wall(425,1400,100,20));

    platforms.push_back(new Platform(250,1240,100,10));
    walls.push_back(new Wall(250,1250,100,10));

    platforms.push_back(new Platform(50,1240,100,10));
    walls.push_back(new Wall(50,1250,100,10));

    platforms.push_back(new Platform(75,1090,300,10));
    walls.push_back(new Wall(75,1100,300,20));

    platforms.push_back(new Platform(275,990,100,10));
    walls.push_back(new Wall(275,1000,100,90));

    platforms.push_back(new Platform(550,940,100,10));
    walls.push_back(new Wall(550,950,100,20));

    platforms.push_back(new Platform(275,790,100,10));
    walls.push_back(new Wall(275,800,100,20));

    platforms.push_back(new Platform(150,690,50,10));
    walls.push_back(new Wall(130,500,20,200));
    platforms.push_back(new Platform(130,490,20,10));

    platforms.push_back(new Platform(400,590,50,10));
    walls.push_back(new Wall(400,600,50,50));


    platforms.push_back(new Platform(400,290,25,10));
    walls.push_back(new Wall(400,300,25,200));


    WinPlatform *winP = new WinPlatform(10,100,100,10);
    scene->addItem(winP);

    // Spike *spike1 = new Spike();
    // spike1->setPos(-25,1750);
    // scene->addItem(spike1);




    player = new Player();
    scene->addItem(player);
    player->setPos(200,1850);
    connect(player, &Player::disableLeft, this, &Game::onDisableLeft);
    connect(player, &Player::disableRight, this, &Game::onDisableRight);
    connect(player, &Player::respawn,this,&Game::respawnCharacter);
    connect(player, &Player::reachedWin, this, &Game::handleWin);

    for(auto p : platforms){
        scene->addItem(p);
    }
    for(auto w : walls){
        scene->addItem(w);
    }


    qDebug() << "Level 1 loaded";
}

void Game::loadLevel2() {
    scene->removeItem(winTextItem);
    winTextItem = nullptr;
    win = false;
    clearScene();
    std::vector<Platform*> platforms;
    std::vector<Wall*> walls;
    std::vector<Spike*> spikes;

    // Spawn platform
    platforms.push_back(new Platform(-25, 1950, 650, 20));

    // Player
    player = new Player();
    scene->addItem(player);
    player->setPos(200,1850);
    connect(player, &Player::disableLeft, this, &Game::onDisableLeft);
    connect(player, &Player::disableRight, this, &Game::onDisableRight);
    connect(player, &Player::respawn, this, &Game::respawnCharacter);
    connect(player, &Player::reachedWin, this, &Game::handleWin);

    platforms.push_back(new Platform(-25, 1730, 100, 20));
    walls.push_back(new Wall(-25, 1750, 100, 200));
    for (int i = 0; i < 10; i++) {
        spikes.push_back(new Spike(300 + 30 * i, 1920));
    }

    platforms.push_back(new Platform(250, 1690, 50, 10));
    walls.push_back(new Wall(250, 1700, 50, 10));

    platforms.push_back(new Platform(450, 1690, 50, 10));
    walls.push_back(new Wall(450, 1700, 50, 10));

    platforms.push_back(new Platform(450, 1390, 60, 10));
    walls.push_back(new Wall(450, 1400, 60, 10));

    walls.push_back(new Wall(440, 1210, 10, 200));

    platforms.push_back(new Platform(-25, 1440, 400, 10));
    walls.push_back(new Wall(-25, 1450, 400, 70));

    spikes.push_back(new Spike(345, 1410));
    spikes.push_back(new Spike(315, 1410));

    platforms.push_back(new Platform(-25, 1290, 75, 10));
    walls.push_back(new Wall(-25, 1300, 75, 140));

    walls.push_back(new Wall(150, 1100, 100, 250));
    platforms.push_back(new Platform(100, 1090, 150, 10));
    walls.push_back(new Wall(100, 1100, 50, 10));

    platforms.push_back(new Platform(500, 990, 50, 10));
    walls.push_back(new Wall(500, 1000, 50, 10));

    platforms.push_back(new Platform(300, 900, 100, 10));
    walls.push_back(new Wall(300, 910, 100, 10));

    platforms.push_back(new Platform(150, 800, 60, 10));
    walls.push_back(new Wall(150, 810, 60, 10));

    spikes.push_back(new Spike(150, 770));
    spikes.push_back(new Spike(180, 770));

    platforms.push_back(new Platform(375, 700, 100, 10));
    walls.push_back(new Wall(375, 710, 100, 10));

    platforms.push_back(new Platform(100, 600, 150, 10));
    walls.push_back(new Wall(100, 610, 150, 10));

    spikes.push_back(new Spike(130, 570));
    spikes.push_back(new Spike(160, 570));
    spikes.push_back(new Spike(190, 570));

    platforms.push_back(new Platform(450, 500, 40, 10));
    walls.push_back(new Wall(450, 510, 40, 10));

    platforms.push_back(new Platform(250, 400, 100, 10));
    walls.push_back(new Wall(250, 410, 100, 10));

    spikes.push_back(new Spike(280, 370));
    spikes.push_back(new Spike(310, 370));

    platforms.push_back(new Platform(50, 300, 100, 10));
    walls.push_back(new Wall(50, 310, 100, 10));

    walls.push_back(new Wall(40, 100, 10, 220));

    WinPlatform* winP = new WinPlatform(500, 50, 100, 10);
    scene->addItem(winP);


    for (auto p : platforms) {
        scene->addItem(p);
    }
    for (auto w : walls) {
        scene->addItem(w);
    }
    for (auto s : spikes) {
        scene->addItem(s);
    }

    qDebug() << "Level 2 loaded";
}

// void Game::loadLevelendless() {
//     clearScene();
//     player = new Player();
//     scene->addItem(player);
//     Platform *platform = new Platform(100, 300, 100, 20);
//     platform->setPos(300, 400);
//     scene->addItem(platform);
//     qDebug() << "Endless loaded";
// }

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

void Game::respawnCharacter() {
    scene->removeItem(player);

    QTimer::singleShot(500, this, [this]() {
        player->setPos(200, 1850);
        player->setVelocityX(0);
        scene->addItem(player);
    });
}

void Game::handleWin()
{
    if (!winTextItem) {
        win = true;
        winTextItem = new QGraphicsTextItem("YOU WON!\n Press Esc to go back \nto level select");
        winTextItem->setFont(QFont("Arial", 30, QFont::Bold));
        winTextItem->setDefaultTextColor(Qt::green);
        winTextItem->setPos(scene->width() / 2 - winTextItem->boundingRect().width() / 2,
                            225);
        scene->addItem(winTextItem);
    }
}






