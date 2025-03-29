#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "levelselect.h"
#include "mainmenu.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToGame();
    void switchToSettings();
    void switchToLevelSelect();
    void switchToMainMenu();

private:
    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;
    LevelSelect *levelSelect;
};

#endif
