
#ifndef INICIO_H
#define INICIO_H

#include "selector.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QSound>


QT_BEGIN_NAMESPACE
namespace Ui { class inicio; }
QT_END_NAMESPACE

class inicio : public QMainWindow

{
    Q_OBJECT

public:
    inicio(QWidget *parent = nullptr);
    ~inicio();

private:
    Ui::inicio *ui;
    Selector* PantallaSelector;
    Sprites *Inicio;
    QGraphicsScene *scene;
    void keyPressEvent(QKeyEvent *ev);
    Game* PantallaGame;
    QSound* Musica;
    QSound* Musica2;
    selectormundos* PantallaSMundos;


};

#endif // INICIO_H
