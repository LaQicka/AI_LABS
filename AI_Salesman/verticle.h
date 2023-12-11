#ifndef VERTICLE_H
#define VERTICLE_H

#include "QGraphicsItem"

class Verticle : public QGraphicsItem
{
public:
    Verticle();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // VERTICLE_H
