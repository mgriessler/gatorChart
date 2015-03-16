#include "dimond.h"

Dimond::Dimond(const QColor &color, int x, int y)
{

    this -> x = x;
    this -> y = y;
    this -> color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);

}

QPolygonF Parallo::boundingParallo() const
{
//0,0,110,70 ???
return QPolygonF(0, 0, 110, 70);
}


QPainterPath Dimond::shape() const
{
     QPainterPath path;
     painter->drawLine(50, 0, 0, 50);
     painter->drawLine(0, 50, 50, 100);
     painter->drawLine(50, 100, 100, 50);
     painter->drawLine(100, 50, 50, 0);
     return path;
}


void Dimond::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);

     QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
     if (option->state & QStyle::State_MouseOver)
         fillColor = fillColor.light(125);


     QPen oldPen = painter->pen();
     QPen pen = oldPen;
     int width = 0;
     if (option->state & QStyle::State_Selected)
         width += 2;


     pen.setWidth(width);
     QBrush b = painter->brush();
     painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));


     painter->drawDimond(QRect(14, 14, 79, 39));
     painter->setBrush(b);


     painter->setPen(QPen(Qt::gray, 1));
     painter->drawLine(15, 54, 94, 54);
     painter->drawLine(94, 53, 94, 15);
     painter->setPen(QPen(Qt::black, 0));


void Dimond::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mousePressEvent(event);
     update();
}


void Dimond::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
     if (event->modifiers() & Qt::ShiftModifier) {
         stuff << event->pos();
         update();
         return;
     }
     QGraphicsItem::mouseMoveEvent(event);
 }


 void Square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseReleaseEvent(event);
     update();
}
