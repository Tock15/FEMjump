#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MainMenu : public QWidget {
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

signals:
    void openLevelSelect();
};

#endif // MAINMENU_H
