#include "shape.h"
#include <QMenu>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPainterPath>
#include <QPointF>
#include <QPixmap>
#include <Qt>
#include <QPainter>
#include <QPen>
#include <QGraphicsSceneContextMenuEvent>
#include <QVariant>




//Constructor

    /*shape::shape(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent,  QGraphicsScene  *scene) : QGraphicsPolygonItem(parent, scene)
    {
        myDiagramType = diagramType;
        myContextMenu = contextMenu;

        QPainterPath path;
        switch (myDiagramType)
            switch(myDiagramType){
                case StartEnd:
                    path.moveTo(200, 50);
                    path.arcTo(150, 0, 50, 50, 0, 90);
                    path.arcTo(50, 0, 50, 50, 90, 90);
                    path.arcTo(50, 50, 50, 50, 180, 90);
                    path.arcTo(150, 50, 50, 50, 270, 90);
                    path.lineTo(200, 25);
                    myPolygon = path.toFillPolygon();
                    break;
                case Conditional:
                    myPolygon << QPointF(-100, 0) << QPointF(0, 100) << QPointF(100, 0) << QPointF(0, -100) << QPointF(-100, 0);
                    break;
                case Step:
                    myPolygon << QPointF(-100, -100) << QPointF(100, -100) << QPointF(100, 100) << QPointF(-100, 100) << QPointF(-100, -100);
                    break;
                default:
                    myPolygon << QPointF(-120, -80) << QPointF(-70, 80) << QPointF(120, 80) << QPointF(70, -80) << QPointF(-120, -80);
                    break;

            }
    setPolygon(myPolygon);
    setFlag(QGraphicItem::ItemIsMovable, true);
    setFlag(QGraphicItem::ItemIsSelectable, true);
    setFlag(QGraphicItem::ItemSendsGeometryChanges, true);
    }

    //removeArrow() function

    void shape::removeArrow(Arrow *arrow)
    {
        int index = arrows.indexOf(arrow);

        if(index != -1)
            arrows.removeAt(index);
    }

    //addArrow() function

    void shape::addArrow(Arrow *arrow)
    {
        arrows.append(arrow);
    }

    //image() function

    QPixmap shape::image() const
    {
        QPixmap pixmap(250, 250);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(QPen(Qt::black, 8));
        painter.translate(125, 125);
        painter.drawPolyline(myPolygon);

        return pixmap;
    }

    //contextMenuEvent() function

    void shape::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    {
        scene()->clearSelection();
        setSelected(true);
        myContextMenu->exec(event->screenPos());
    }

    //implementation of itemChange()

    QVariant shape::itemChange(GraphicsItemChange change, const QVariant &value)
    {
        if(change == QGraphicsItem::ItemPositionChange){
            foreach(Arrow *arrow, arrows){
                arrow->updatePosition();
            }
        }
        return value;
    }
*/
