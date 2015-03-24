#include "square.h"
#include <iostream>
#include <QtWidgets>

Square::Square(const QColor &color, int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF Square::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}

QPainterPath Square::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawRect(QRect(14, 14, 79, 39));
    painter->setBrush(b);

    painter->setPen(QPen(Qt::gray, 1));
    painter->drawLine(15, 54, 94, 54);
    painter->drawLine(94, 53, 94, 15);
    painter->setPen(QPen(Qt::black, 0));

}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    std::cout <<"Start (" << this->pos().x() << ", " << this->pos().y() << ") ";
    update();
}

void Square::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
    QPointF p = this->pos();
    int gridSize = 40;
    std::cout << " End (" << p.x() << ", " << p.y() << ") " << fmod(p.x() , gridSize) << std::endl;
    /*if(fmod(p.x(), gridSize) != 0)
        p.setX(p.x() + fmod(p.x(), gridSize));
    if(fmod(p.y(), gridSize) != 0)
        p.setX(p.y() + fmod(p.y(), gridSize));
    p.setX(p.x() + 60);
    p.setY(p.y() + 60);
    this->setPos(p);*/
    update();
}
