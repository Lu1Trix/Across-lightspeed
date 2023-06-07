#include "sprites.h"

Sprites::Sprites(const char* texto, int x_size, int y_size)
{
    pixmap = new QPixmap(texto);
    currentsprite = new QPixmap;
    character_x_size = x_size;
    character_y_size = y_size;
}

Sprites::~Sprites()
{
    delete pixmap;
    delete currentsprite;
}

void Sprites::changecurrentpixmap(int x, int y)
{
    *currentsprite = pixmap->copy(x*character_x_size, y*character_y_size,
                                  character_x_size,   character_y_size);
    cargarnuevosprite();
}

void Sprites::set_ampliar(int ampliar)
{
    this->ampliar = ampliar;
    cargarnuevosprite();
}


void Sprites::cargarnuevosprite()
{
    setPixmap(currentsprite->scaled(currentsprite->width()*ampliar,
                                    currentsprite->height()*ampliar));
}

void Sprites::moveUp()
{

    static int anim_count = 0;
    changecurrentpixmap(1, 0);

    anim_count++;
    int sprite_y = (anim_count / 5) % 3;
    changecurrentpixmap(sprite_y, 0);

}

void Sprites::turbo()
{
    static int anim_count = 0;
    changecurrentpixmap(0, 1);


    anim_count++;
    int sprite_y = (anim_count / 6) % 2 + 1;
    changecurrentpixmap(sprite_y, 1);

}

void Sprites::uytieso()
{
    changecurrentpixmap(0,0);
}












