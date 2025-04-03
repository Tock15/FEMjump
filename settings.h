#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
signals:
    void backToMainMenu();
private:
    Ui::Settings *ui;
    QJsonObject recordobj;
};

#endif // SETTINGS_H
