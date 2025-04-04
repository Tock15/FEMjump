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
    ui->themeToggleButton->setChecked(settingsManager->theme() == "dark");
    ui->volumeSlider->setValue(settingsManager->audioVolume());
    connect(ui->menuBtn, &QPushButton::clicked, this, &Settings::backToMainMenu);
    connect(ui->themeToggleButton, &QCheckBox::toggled, this, [=](bool checked) {
        settingsManager->setTheme(checked ? "dark" : "light");
        emit themeToggle(checked);
    });

    connect(ui->volumeSlider, &QSlider::valueChanged, this, [=](int val) {
        settingsManager->setAudioVolume(val);
        game->setJumpSoundVolume(val / 100.0f);
    });

}

Settings::~Settings()
{
    delete ui;
}
