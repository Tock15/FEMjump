#include "settingsmanager.h"
#include <QDebug>

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent) {}

void SettingsManager::load() {
    QFile file(settingsFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "file not found using default";
        save();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    settings = doc.object();
    file.close();
}

void SettingsManager::save() {
    QFile file(settingsFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "failed to save settings.";
        return;
    }

    QJsonDocument doc(settings);
    file.write(doc.toJson());
    file.close();
}

QString SettingsManager::theme() const {
    return settings.value("theme").toString("light");
}

void SettingsManager::setTheme(const QString& theme) {
    settings["theme"] = theme;
}

int SettingsManager::audioVolume() const {
    return settings.value("audioVolume").toInt(100);
}

void SettingsManager::setAudioVolume(int volume) {
    settings["audioVolume"] = volume;
}

int SettingsManager::highScore() const {
    return settings.value("highScore").toInt(0);
}

void SettingsManager::setHighScore(int score) {
    settings["highScore"] = score;
}
