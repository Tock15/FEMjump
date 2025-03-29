#include "levelselect.h"
#include "ui_levelselect.h"  // This should now match the generated header

#include <QPushButton>  // If you need QPushButton for connection

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LevelSelect)
{
    ui->setupUi(this);
    connect(ui->btnBack, &QPushButton::clicked, this, &LevelSelect::backToMainMenu);
    connect(ui->oneBtn, &QPushButton::clicked, this, &LevelSelect::goToLevel1);
    connect(ui->twoBtn, &QPushButton::clicked, this, &LevelSelect::goToLevel2);
    connect(ui->endlessBtn, &QPushButton::clicked, this, &LevelSelect::goToEndless);

}

LevelSelect::~LevelSelect() {
    delete ui;
}
