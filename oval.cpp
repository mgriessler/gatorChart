#include "oval.h"

#include <QTWidgets>
#include <iostream>

Oval::Oval(const QColor &color, int x,int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->dispText = "Oval";
    setZValue((x + y) % 2);
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF Oval::boundingRect() const
{

    return QRectF(0,0,90,40);

}
int Oval::type() const
{
    return 1;
}
QPainterPath Oval::shape() const
{
    QPainterPath path;
    path.addRect(0,0,90,40);
    return path;
}

void Oval::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = color;
    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->setPen(QPen(Qt::black, 0));


    painter->drawEllipse(0,0,90,40);

    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->drawText(20,20, dispText);
    painter->restore();

}
void Oval::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Oval::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Oval::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
