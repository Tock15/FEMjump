#include "mainmenu.h"
#include "ui_mainmenu.h"

#include <QPushButton>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::MainMenu) {
    ui->setupUi(this);

    // Connect the button (designed in Qt Designer with objectName "btnLevelSelect")
    connect(ui->btnLevelSelect, &QPushButton::clicked, this, &MainMenu::openLevelSelect);
    connect(ui->btnSettingsSelect,  &QPushButton::clicked, this, &MainMenu::openSettings);

}

MainMenu::~MainMenu() {
    delete ui;
}
