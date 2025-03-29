#include "levelselect.h"

LevelSelect::LevelSelect(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *backButton = new QPushButton("Back to Main Menu");
    connect(backButton, &QPushButton::clicked, this, &LevelSelect::backToMainMenu);

    layout->addWidget(backButton);
    setLayout(layout);
}
