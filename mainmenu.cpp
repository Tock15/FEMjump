#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *levelSelectButton = new QPushButton("Level Select");
    connect(levelSelectButton, &QPushButton::clicked, this, &MainMenu::openLevelSelect);

    layout->addWidget(levelSelectButton);
    setLayout(layout);
}
