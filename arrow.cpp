#include <QGraphicsItem>
#include <QLineF>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QPolygonF>

#include <QRectF>
#include <QSizeF>
#include <QStyleOptionGraphicsItem>
#include <Qt>
#include <QWidget>

#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>

//Constructor


Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem,


         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)


 {
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

//boundingRect() function

        QRectF Arrow::boundingRect() const{
            qreal extra= (pen().width() + 20)/2.0;
            return QRect(line().p1, QSizeF(line().p2.x() - line.p1().x(), line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
        }

//Shape() function
        QPainterPath Arrow::Shape() const{

        QPainterPath path = QGraphicsLineItem::Shape();
        path.addPlygon(arrorHead);
        return path;
        }

//updatePosition() slot

        void Arrow::updatePosition(){

            QLineF line(mapFromItem(myStrartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
            setLine(line);
        }

//paint() function

        void Arrow::paint(QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*){
            if(myStartItem->collidesWithItem(myEndItem))
                return;

            QPen myPen = pen();
            myPen.setColor(myColor);
            qreal arrowSize = 20;
            painter->setPen(myPen);
            painter->setBrush(myColor);
            QLineF centerLine(myStartItem->pos(), myEndItem->pos());
            QPolygonF endPolygon = endPolygon.first() + myEndItem->pos();
            QPointF p1 = endPolygon.first() + myEndItem->pos();
            QpointF p2;
            QPointF intersectPoint;
            QLineF polyLine;
            for(int i = 1; i<endPolygon.count(); i++){
                p2 = endPolygon.at(i) + myEndItem->pos();
                polyLine = QLineF (p1, p2);
                QLineF::IntersectType IntersectType = polyLine.intersect(centerLine, &intersectPoint);
                if(intersectType == QLineF::BoundedIntersection)
                    break;
                p1 = p2;
            }
            setLine(QLineF(intersectPoint, myStartItem->pos()));


//Adding the position of the end item to make the coordinates relative to the scene

        double angle = ::acos(line().dx()/line().length());
        if(line().dy() >= 0)
           angle = (Pi*2)-angle;
        QPointF arrowP1 = line().p1() + QPointF(sin(agle + Pi/3)*arrowSize,cos(angle + Pi/3)*arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi/3)*arrowSize, cos(angle + Pi - Pi/3)*arrowSize);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
        if(isSelected()){
           painter->setPen(QPen(mycolor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0, -8.0);
        painter->drawLine(myLine);
        }

   }
