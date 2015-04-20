#include "parallelogram.h"
#include <QtWidgets>

Parallel::Parallel(const QColor &color, int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    dispText = "Parallel";
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

Parallel::Parallel(const QColor &color, int x, int y, QString text)
{
    this->x = x;
    this->y = y;
    this->color = color;
    dispText = text;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF Parallel::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}
QPainterPath Parallel::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 130, 80);
    return path;
}

void Parallel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    
    //painter->drawRect(QRect(1, 1, 100, 60));
    //commented out
    //painter->setBrush(b);

    painter->setPen(QPen(Qt::black, 1));


    //added by me (Dennis

    QBrush fillbrush;
    fillbrush.setColor(fillColor);
    fillbrush.setStyle(Qt::SolidPattern);


    //Make trapezoid
    QPolygon poly;
    poly << QPoint(20,35);      //A             A->B->C->D
    poly << QPoint(110,35);     //B
    poly << QPoint(90,1);       //C
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

void Parallel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Parallel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

int Parallel::type() const
{
    return 4;
}

void Parallel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}


