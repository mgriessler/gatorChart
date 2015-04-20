#include "diamond.h"

#include <QtWidgets>

Diamond::Diamond(const QColor &color, int x, int y)
{

    this -> x = x;
    this -> y = y;
    this -> color = color;
    this->dispText = "Diamond";
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);

}
int Diamond::type() const
{
    return 2;
}
QRectF Diamond ::boundingRect() const
{
    //window location
    return QRectF(0, 0, 110, 110);
    
}


QPainterPath Diamond::shape() const
{
     QPainterPath path;
     path.addRect(14, 14, 82, 42);
     path.addRect(0, 0, 130, 80);
     return path;
}


void Diamond::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
     painter->setBrush(fillColor);

     painter->setPen(QPen(Qt::black, 1));

     QBrush fillbrush;
     fillbrush.setColor(fillColor);
     fillbrush.setStyle(Qt::SolidPattern);

    QPolygon poly;
    poly << QPoint(50,0);
    poly << QPoint(100,50);
    poly << QPoint(50,100);
    poly << QPoint(0,50);

    painter->drawPolygon(poly);

    QPainterPath p;
    p.addRegion(poly);
    painter->fillPath(p,fillbrush);

    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->drawText(10,50, dispText);
    painter->restore();
}

void Diamond::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mousePressEvent(event);
     update();
}


void Diamond::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

     if (event->modifiers() & Qt::ShiftModifier) {
         stuff << event->pos();
         update();
         return;
     }
     QGraphicsItem::mouseMoveEvent(event);
 }


 void Diamond::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseReleaseEvent(event);
     update();
}
