#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Create a scene (area to display shit)
    QGraphicsScene * scene = new QGraphicsScene();

    //Create Rectangle
    QGraphicsPixmapItem * player = new QGraphicsPixmapItem();
    player->setPixmap(QPixmap(":/img/astolfo.png").scaled(50,50));


    scene->addItem(player);

    //Create a view (window)
    QGraphicsView * view = new QGraphicsView(scene);
    view->show();


    // MainWindow w;
    // w.show();
    return a.exec();
}
