#ifndef CHARACTER_H
#define CHARACTER_H

#include "QPainter"
#include "QGraphicsItem"

class Character : public QGraphicsItem
{
public:
    Character(int size, int X, int Y);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    qreal getSquare_size() const;
    void setSquare_size(qreal newSquare_size);

    QPixmap picture() const;
    void setPicture(const QPixmap &newPicture);

private:
    QPixmap m_picture;
    qreal square_size;
};

#endif // CHARACTER_H
