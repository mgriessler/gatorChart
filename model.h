#ifndef MODEL_H
#define MODEL_H

#include "square.h"

#include <QGraphicsItem>
#include <QtWidgets>
#include <QList>
#include "shape.h"
#include "arrow.h"

class model : public QGraphicsScene
{

public:
    model();

    QList<QGraphicsItem *> listActiveItems;
    enum DesiredAction {Action_CreateShape, Action_CreateLineStart, Action_CreateLineEnd, Action_MoveObject, Action_Drag, Action_Delete};

    void create(QListWidgetItem *item);
    void label();
    void createRect(QColor color, qreal x, qreal y);
    void updateScene();
    void theSaveList();
    void openNewApplication();

    void setAction(DesiredAction action);

    void setColor(int c);

    void setDispText(QString text);

    void createOpenShape(qreal x, qreal y, QString shapeName);
    void createOpenShape(qreal x, qreal y, QString shapeName, QString text);


public Q_SLOTS:
    void shapeSelection();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    DesiredAction currentAction;
    Shape *lineBeginItem;
    Shape *lineEndItem;
};

#endif // MODEL_H
