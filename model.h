#ifndef MODEL_H
#define MODEL_H

#include "square.h"

#include <QGraphicsItem>
#include <QtWidgets>
#include <QList>

class model : public QGraphicsScene
{

public:
    model();

    QList<QGraphicsItem *> listActiveItems;
    enum DesiredAction {Action_CreateShape, Action_CreateLineStart, Action_CreateLineEnd, Action_MoveObject, Action_Drag};

    void create(QListWidgetItem *item);
    void label();
    void createRect(QColor color, qreal x, qreal y);
    void updateScene();
    void theSaveList();
    void openNewApplication();
    void itemHere(QMouseEvent *event);
    void setAction(DesiredAction action);
    void createOpenShape(qreal x, qreal y, QString shapeName);

public Q_SLOTS:
    void shapeSelection();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    DesiredAction currentAction;
};

#endif // MODEL_H
