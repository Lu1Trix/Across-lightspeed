#ifndef SELECTOR_H
#define SELECTOR_H

#include "selectormundos.h"
#include "sprites.h"
#include <QMainWindow>
#include <QImage>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {class Selector;}
QT_END_NAMESPACE

class Selector : public QMainWindow
{
    Q_OBJECT

public:
    Selector(QWidget *parent = nullptr);
    ~Selector();
    int NaveSeleccionada;

private:
    Ui::Selector *ui;
    QGraphicsScene *scene;
    QSound* Musica;
    selectormundos* PantallaGame;
    void keyPressEvent(QKeyEvent *ev);

};

#endif // SELECTOR_H
