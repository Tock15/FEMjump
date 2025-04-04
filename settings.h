#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include "settingsmanager.h"
#include "game.h"
namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(SettingsManager *settingsManager, Game *game,QWidget *parent = nullptr);
    ~Settings();
signals:
    void backToMainMenu();
    void themeToggle();
private:
    Ui::Settings *ui;
    QJsonObject recordobj;
    QJsonDocument doc;
    SettingsManager *settingsManager;
    Game *game;
};

#endif // SETTINGS_H
