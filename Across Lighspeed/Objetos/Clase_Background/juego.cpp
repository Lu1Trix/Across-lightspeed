
#include "juego.h"

Juego::Juego()
{
    character = new Sprites;
    addItem(character);
    character->setPos(0,0);
    character->changecurrentpixmap(0,0);
    character->set_ampliar(3);

}

Juego::~Juego()
{
    delete character;
}

void Juego::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_W){
        character->moveUp();
    }

    if(event->key()==Qt::Key_Shift){
        character->turbo();
    }

}
