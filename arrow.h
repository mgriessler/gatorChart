#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>

#include "shape.h"
#include <string>

class QGraphicsItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
class Shape;

class Arrow : public QGraphicsLineItem
{
public:

    enum  { Type = UserType + 4 };

    Arrow(Shape *startItem, Shape *endItem,
      QGraphicsItem *parent = 0);

    int type() const Q_DECL_OVERRIDE { return Type; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    //setcolor sets item's color
    void setColor(const QColor &color) { lineColor = color; }
    Shape *startItem() const { return startShape; }
    Shape *endItem() const { return endShape; }

    //updatePosition()causes the arrow to recalculate the position of the arrow
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
    Shape *startShape;
    Shape *endShape;
    QColor lineColor;
    QPolygonF arrowHead;
};


#endif // ARROW_H
