#include "character.h"

Character::Character(int size, int X, int Y)
{
    square_size = size;
    setPos(X, Y);
}

QRectF Character::boundingRect() const
{
    return QRectF(-square_size / 2, -square_size / 2, square_size, square_size);
}

qreal Character::getSquare_size() const
{
    return square_size;
}

void Character::setSquare_size(qreal newSquare_size)
{
    square_size = newSquare_size;
}

QPixmap Character::picture() const
{
    return m_picture;
}

void Character::setPicture(const QPixmap &newPicture)
{
    m_picture = newPicture;
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),m_picture,m_picture.rect());
}
