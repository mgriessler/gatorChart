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
    enum DesiredAction {Action_CreateShape, Action_CreateLine, Action_MoveObject};

    void create();
    void label();
    void createRect(QColor color, qreal x, qreal y);
    void updateScene();
    void itemHere(QMouseEvent *event);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    QGraphicsItem *items[10];
    DesiredAction act;
};

#endif // MODEL_H
