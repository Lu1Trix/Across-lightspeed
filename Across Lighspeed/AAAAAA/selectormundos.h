#ifndef SELECTORMUNDOS_H
#define SELECTORMUNDOS_H

#include <QMainWindow>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>
#include <game.h>


QT_BEGIN_NAMESPACE
namespace Ui {class selectormundos;}
QT_END_NAMESPACE

class selectormundos : public QMainWindow
{
    Q_OBJECT

public:
    selectormundos(QSound *Sonidos, int NaveUsada, QWidget *parent = nullptr);
    ~selectormundos();

private:
    Ui::selectormundos *ui;
    QGraphicsScene *scene;
    Game* PantallaGame;
    int Mundo;
    int Nave;
    QSound* Musica;
    void keyPressEvent(QKeyEvent *ev);

};

#endif // SELECTORMUNDOS_H
