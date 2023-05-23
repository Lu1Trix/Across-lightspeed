
#ifndef SPRITES_H
#define SPRITES_H

#include <QGraphicsPixmapItem>

#define character_x_size 64
#define character_y_size 32


class Sprites :public QObject, public QGraphicsPixmapItem
{
public:
    Sprites();
    ~Sprites();
    void changecurrentpixmap(int x, int y);
    void set_ampliar(int ampliar);
    void moveUp();
    void turbo();

private:
    int ampliar;
    QPixmap *pixmap, *currentsprite;
    void cargarnuevosprite();


};

#endif // SPRITES_H
