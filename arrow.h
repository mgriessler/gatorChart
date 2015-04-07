#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>

#include "diagramitem.h"

class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;

class Arrow : public QGraphicsLineItem
{
public:

    enum  { Type = UserType + 4 };

    Arrow(shape *startItem, shape *endItem,

      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const


         { return Type; }


    QRectF boundingRect() const;

    QPainterPath Shape() const;


    void setColor(const QColor &color)


       { myColor = color; }


    shape *startItem() const


         { return myStartItem; }


    shape *endItem() const


        { return myEndItem; }


    void updatePosition();



protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,

               QWidget *widget = 0);




private:


    shape *myStartItem;


    shape *myEndItem;


    QColor myColor;


    QPolygonF arrowHead;


};

    Arrow(DiagramItem *startItem, DiagramItem *endItem,
      QGraphicsItem *parent = 0);

    int type() const Q_DECL_OVERRIDE { return Type; }

    //boundingRect() and shape()check for collisions and selections
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    //setcolor sets item's color
    void setColor(const QColor &color) { myColor = color; }
    DiagramItem *startItem() const { return myStartItem; }
    DiagramItem *endItem() const { return myEndItem; }

    //updatePosition()causes the arrow to recalculate the position of the arrow
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
    DiagramItem *myStartItem;
    DiagramItem *myEndItem;
    QColor myColor;
    QPolygonF arrowHead;
};


#endif // ARROW_H
