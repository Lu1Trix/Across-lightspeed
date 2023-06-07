
#ifndef INICIO_H
#define INICIO_H

#include "selector.h"
#include "game.h"
#include "selectormundos.h"
#include <QMainWindow>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class inicio : public QMainWindow

{
    Q_OBJECT

public:
    inicio(QWidget *parent = nullptr);
    ~inicio();

private:
    Ui::MainWindow *ui;
    Selector* PantallaSelector;
    Sprites *Inicio;
    QGraphicsScene *scene;
    void keyPressEvent(QKeyEvent *ev);
    Game* PantallaGame;
    selectormundos* PantallaSMundos;

};

#endif // INICIO_H
