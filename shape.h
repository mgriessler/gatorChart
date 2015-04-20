#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>
#include "arrow.h"
#include <QList>
class Arrow;

class Shape : public QGraphicsItem
{
public:
    Shape();
    void test();
    void test2();
    void addArrow(Arrow *arrow);
    void setDispText(QString text);

private:
    QList<Arrow *> arrows;

protected:
    QString dispText;

};

#endif // SHAPE_H
