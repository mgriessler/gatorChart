#ifndef MODEL_H
#define MODEL_H

#include "square.h"

#include <QGraphicsItem>
#include <QtWidgets>

class model : public QGraphicsScene
{

public:
    model();
    void create();
    void createRect(QColor color, qreal x, qreal y);
    void updateScene();
    QGraphicsScene scene;
    void itemHere(QMouseEvent *event);


private:
    QGraphicsItem *items[10];
};

#endif // MODEL_H
