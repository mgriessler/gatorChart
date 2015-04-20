
#include "trap.h"

#include <QtWidgets>

Trap ::Trap (const QColor &color, int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->dispText = "Trap";
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}
int Trap::type() const
{
    return 3;
}
QRectF Trap ::boundingRect() const
{
    //window location
    return QRectF(0, 0, 110, 70);
    //return QRectF(0, 0, 110, 70);
}

QPainterPath Trap ::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    path.addRect(0, 0, 130, 80);
    return path;
}

void Trap ::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    //painter->drawRect(QRect(1, 1, 100, 60));
    //commented out
    //painter->setBrush(b);

    painter->setPen(QPen(Qt::black, 1));


    //added by me (Dennis

    QBrush fillbrush;
    fillbrush.setColor(Qt::blue);
    fillbrush.setStyle(Qt::SolidPattern);


    //Make trapezoid
    QPolygon poly;
    poly << QPoint(20,35);      //A             A->B->C->D
    poly << QPoint(90,35);      //B
    poly << QPoint(110,1);      //C
    poly << QPoint(1,1);        //D

    painter->drawPolygon(poly);

    QPainterPath p;
    p.addRegion(poly);
    painter->fillPath(p,fillbrush);


    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->drawText(20,20, dispText);
    painter->restore();

}

void Trap ::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Trap ::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Trap ::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
