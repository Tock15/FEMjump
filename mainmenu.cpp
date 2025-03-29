

#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    scene = new QGraphicsScene(this);

    QGraphicsPixmapItem *player = new QGraphicsPixmapItem();
    player->setPixmap(QPixmap(":/img/astolfo.png").scaled(50, 50));

    scene->addItem(player);

    view = new QGraphicsView(scene);
    view->setFixedSize(1280, 720);
    view->setSceneRect(0, 0, 1280, 720);

    QPushButton *levelSelectButton = new QPushButton("Level Select");
    connect(levelSelectButton, &QPushButton::clicked, this, &MainMenu::openLevelSelect);


    layout->addWidget(view);
    layout->addWidget(levelSelectButton);
    setLayout(layout);
}
