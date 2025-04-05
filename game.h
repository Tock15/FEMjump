#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include "platform.h"
#include "player.h"
#include "wall.h"
#include "spike.h"
#include "settingsmanager.h"
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
class QSoundEffect;
class QMediaPlayer;
class QAudioOutput;
class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(SettingsManager *settingsManager, QWidget *parent = nullptr);
    ~Game();
    void clearScene();
    void setJumpSoundVolume(float volume);
    void setMusicVolume(float volume);
signals:
    void switchToLevel();
public slots:
    void handleMovement();
    void loadLevel1();
    void loadLevel2();
    void loadLevelendless();
    void onDisableRight();
    void onDisableLeft();
    void checkCollisions();
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
    QSoundEffect *jumpSound;
    SettingsManager *settingsManager;
    bool noLeft;
    bool noRight;
    QMediaPlayer *bgMusic;
    QAudioOutput *bgAudio;
    QStringList musicTracks;
    int currentTrackIndex = 0;
    int score = 0;
    int highScore = 0;
};

#endif // GAME_H
