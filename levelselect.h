#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LevelSelect : public QWidget {
    Q_OBJECT
public:
    explicit LevelSelect(QWidget *parent = nullptr);

signals:
    void backToMainMenu();
};

#endif
