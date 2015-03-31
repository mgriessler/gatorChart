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
    void updateScene();
    QGraphicsScene scene;

private:
    QGraphicsItem *items[10];
};

#endif // MODEL_H
