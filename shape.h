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
    QColor color;
    void test();
    void test2();
    void addArrow(Arrow *arrow);
    void setDispText(QString text);
    void editColor(Shape *x, QColor);
    //void popUpCombo();
    void setColor(int n);

private:
    QList<Arrow *> arrows;

protected:
    QString dispText;

};

#endif // SHAPE_H
