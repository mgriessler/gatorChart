#ifndef MODEL_H
#define MODEL_H

#include "square.h"

#include <QGraphicsItem>
#include <QtWidgets>

class model : public QGraphicsScene
{

public:
    model();

    QGraphicsScene scene;
    enum DesiredAction {Action_CreateShape, Action_CreateLineStart, Action_CreateLineEnd, Action_MoveObject, Action_Drag};

    void create(QListWidgetItem *item);
    void label();
    void createRect(QColor color, qreal x, qreal y);
    void updateScene();
    void itemHere(QMouseEvent *event);
    void setAction(DesiredAction action);

public Q_SLOTS:
    void shapeSelection();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    QGraphicsItem *items[10];
    DesiredAction currentAction;
};

#endif // MODEL_H
