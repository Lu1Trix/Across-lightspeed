#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>
#include "sprites.h"


class Juego : public QGraphicsScene
{
    Q_OBJECT
public:
    Juego();
    ~Juego();
    void keyPressEvent(QKeyEvent *event);

private:
    Sprites *character, *ch;

};

#endif // JUEGO_H
