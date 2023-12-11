#include "verticle.h"
#include "QBrush"
#include "QPainter"

Verticle::Verticle()
{

}

QRectF Verticle::boundingRect() const
{
    return QRectF(0,0,8,8);
}

void Verticle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF item = boundingRect();
    QBrush brush(Qt::red);

    painter->fillRect(item,brush);
    painter->drawRect(item);
}
