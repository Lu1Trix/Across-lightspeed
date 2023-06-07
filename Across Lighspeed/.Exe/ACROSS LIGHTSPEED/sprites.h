
#ifndef SPRITES_H
#define SPRITES_H

#include <QGraphicsPixmapItem>
#include <dos.h>



class Sprites : public QObject, public QGraphicsPixmapItem
{
public:
    Sprites(const char* texto, int x_size, int y_size);
    ~Sprites();
    void changecurrentpixmap(int x, int y);
    void set_ampliar(int ampliar);
    void moveUp();
    void turbo();
    void uytieso();

private:
    int ampliar;
    QPixmap *pixmap, *currentsprite;
    void cargarnuevosprite();
    int character_x_size;
    int character_y_size;


};

#endif // SPRITES_H
