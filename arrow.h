#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainterPath>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPolygonF>


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
