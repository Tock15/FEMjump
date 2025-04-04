#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToLevelSelect();
    void switchToMainMenu();
    void switchToGame();
    void switchToSettings();

private:
    Ui::MainWindow *ui;
    QString loadStyle(const QString& path);
    SettingsManager *settingsManager;
};

#endif // MAINWINDOW_H
