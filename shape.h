#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsPolygonItem>
#include <QMenu>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPolygonF>
#include <QPixmap>
#include <QGraphicsSceneContextMenuEvent>
#include <QVariant>
#include <QList>
#include "arrow.h"


class shape : public QGraphicsPolygonItem
{
public:
    enum{Type = UserType + 15};
    enum DiagramType {Step, Conditional, StartEnd, Io};

    shape(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void removeArrow(Arrow *arrow);
    void removeArrow();
    DiagramType diagramType() const
        {return myDiagramType;}
    QPolygonF polygon() const
        {return myPolygon;}
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const
        {return Type;}

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrrow*> arrows;

};

#endif // SHAPE_H
