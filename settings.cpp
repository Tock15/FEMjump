#include "settings.h"
#include "ui_settings.h"
#include <QJsonObject>
#include <QJsonDocument>
Settings::Settings(SettingsManager *settingsManager,Game *game,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
    ,settingsManager(settingsManager)
    ,game(game)
{
    ui->setupUi(this);
    QStringList themes = { "light", "dark", "cyberpunk", "forest" };
    ui->themeComboBox->addItems(themes);
    ui->volumeSlider->setValue(settingsManager->audioVolume());
    QString currentTheme = settingsManager->theme();
    int index = themes.indexOf(currentTheme);
    if (index >= 0) {
        ui->themeComboBox->setCurrentIndex(index);
    }

    connect(ui->themeComboBox, &QComboBox::currentTextChanged, this, [=](const QString &theme) {
        settingsManager->setTheme(theme);
        emit themeToggle();
    });

    connect(ui->menuBtn, &QPushButton::clicked, this, &Settings::backToMainMenu);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, [=](int val) {
        settingsManager->setAudioVolume(val);
        game->setJumpSoundVolume(val / 100.0f);
    });

}

Settings::~Settings()
{
    delete ui;
}
