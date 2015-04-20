#include "arrow.h"

#include <math.h>
#include <QPen>
#include <QPainter>
#include <iostream>

const qreal Pi = 3.14;

Arrow::Arrow(Shape *startItem, Shape *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    startShape = startItem;
    endShape = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    lineColor = Qt::green;
    setPen(QPen(lineColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}


void Arrow::updatePosition()
{
    QLineF line(mapFromItem(startShape, 0, 0), mapFromItem(endShape, 0, 0));
    setLine(line);
}


void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    if (startShape->collidesWithItem(endShape))
        return;

    QPen p = pen();
    p.setColor(lineColor);
    qreal arrowSize = 20;
    painter->setPen(p);
    painter->setBrush(lineColor);

    QLineF centerLine(startShape->scenePos(), endShape->scenePos());
    QPointF p1 = endShape->scenePos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    p2 = endShape->scenePos();
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
    p1 = p2;

    std::cout << "IntersectionPoint (" << intersectPoint.x() << "," << intersectPoint.y() << ")" << std::endl;
    std::cout << "startShape->scenePos (" << startShape->scenePos().x() << "," << startShape->scenePos().y() << ")" << std::endl;
    setLine(QLineF(endShape->scenePos(), startShape->scenePos()));
    //setLine(QLineF(intersectPoint, startShape->scenePos()));

    //draw arrow
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
}
