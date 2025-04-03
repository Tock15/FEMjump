#include "settings.h"
#include "ui_settings.h"
#include <QJsonObject>
#include <QJsonDocument>
Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->menuBtn, &QPushButton::clicked, this, &Settings::backToMainMenu);
    connect(ui->themeToggleButton, &QCheckBox::toggled, this, &Settings::themeToggle);


}

Settings::~Settings()
{
    delete ui;
}
