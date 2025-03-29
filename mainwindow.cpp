#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    stackedWidget(new QStackedWidget(this)),
    mainMenu(new MainMenu(stackedWidget)),
    levelSelect(new LevelSelect(stackedWidget)) {

    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(levelSelect);

    setCentralWidget(stackedWidget);
    setMinimumSize(1024, 720);
    resize(1024, 720);
    connect(mainMenu, &MainMenu::openLevelSelect, this, &MainWindow::switchToLevelSelect);
    connect(levelSelect, &LevelSelect::backToMainMenu, this, &MainWindow::switchToMainMenu);
}

MainWindow::~MainWindow() {
    delete stackedWidget;
}

void MainWindow::switchToLevelSelect() {
    stackedWidget->setCurrentWidget(levelSelect);
}

void MainWindow::switchToMainMenu() {
    stackedWidget->setCurrentWidget(mainMenu);
}
