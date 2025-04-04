#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include "mainmenu.h"
#include "levelselect.h"
#include "settings.h"
#include "game.h"
#include <QTextStream>
QString MainWindow::loadStyle(const QString& path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return "";
    QTextStream in(&file);
    return in.readAll();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    settingsManager(new SettingsManager(this))
    {
    ui->setupUi(this);

    // set uniform size
    setMinimumSize(1280, 720);
    resize(1280, 720);
    ui->stackedWidget->setFixedSize(1280, 720);

    // add all classes
    settingsManager->load();
    MainMenu *mainMenu = new MainMenu(this);
    LevelSelect *levelSelect = new LevelSelect(this);
    Game *game = new Game(settingsManager, this);
    Settings *settings = new Settings(settingsManager, game, this);
    game->setJumpSoundVolume(settingsManager->audioVolume() / 100.0f);
    // add the pages to the stacked widget
    ui->stackedWidget->addWidget(mainMenu);
    ui->stackedWidget->addWidget(levelSelect);
    ui->stackedWidget->addWidget(settings);
    ui->stackedWidget->addWidget(game);

    // connect signal to slots very useful
    connect(game, &Game::switchToLevel, this, &MainWindow::switchToLevelSelect);
    connect(mainMenu, &MainMenu::openLevelSelect, this, &MainWindow::switchToLevelSelect);
    connect(mainMenu, &MainMenu::openSettings, this, &MainWindow::switchToSettings);
    connect(levelSelect, &LevelSelect::backToMainMenu, this, &MainWindow::switchToMainMenu);
    connect(levelSelect, &LevelSelect::goToLevel1, this, &MainWindow::switchToGame);
    connect(levelSelect, &LevelSelect::goToLevel2, this, &MainWindow::switchToGame);
    connect(levelSelect, &LevelSelect::goToEndless, this, &MainWindow::switchToGame);
    connect(levelSelect, &LevelSelect::goToLevel1, game, &Game::loadLevel1);
    connect(levelSelect, &LevelSelect::goToLevel2, game, &Game::loadLevel2);
    connect(levelSelect, &LevelSelect::goToEndless, game, &Game::loadLevelendless);
    connect(settings, &Settings::backToMainMenu, this, &MainWindow::switchToMainMenu);
    connect(settings, &Settings::themeToggle, this, [=](bool darkMode) {
        QString style = loadStyle(darkMode ? ":/themes/dark.qss" : ":/themes/light.qss");
        qApp->setStyleSheet(style);
    });
    QString theme = settingsManager->theme();
    qApp->setStyleSheet(loadStyle(theme == "dark" ? ":/themes/dark.qss" : ":/themes/light.qss"));





    // make page main menu :3
    ui->stackedWidget->setCurrentWidget(mainMenu);
}

MainWindow::~MainWindow() {
    if (settingsManager) {
        settingsManager->save();
    }
    delete ui;
}

void MainWindow::switchToLevelSelect() {
   // go to level select
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<LevelSelect*>());

}

void MainWindow::switchToMainMenu() {
    // go to main menu
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<MainMenu*>());
}

void MainWindow::switchToSettings() {
    // go to game
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<Settings*>());
}
void MainWindow::switchToGame() {
    // go to settings
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->findChild<Game*>());
}
