#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

class SettingsManager : public QObject {
    Q_OBJECT
public:
    explicit SettingsManager(QObject* parent = nullptr);

    void load();   // load from json file
    void save();   // save to json file

    QString theme() const;
    void setTheme(const QString& theme);

    int audioVolume() const;
    void setAudioVolume(int volume);

    int highScore() const;
    void setHighScore(int score);

private:
    QJsonObject settings;
    QString settingsFilePath = "settings.json";
};

#endif // SETTINGSMANAGER_H
