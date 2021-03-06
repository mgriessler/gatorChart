#ifndef SQUARE_H
#define SQUARE_H

#include <QColor>
#include <string>
#include <QtWidgets>
#include <QGraphicsItem>
#include "shape.h"
#include "view.h"

class View;

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
class QListWidget;
QT_END_NAMESPACE




class Square : public Shape //, public QObject
{
    //Q_OBJECT
public:

    Square(const QColor &color, int x, int y);
    Square(const QColor &color, int x, int y, QString text);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    //void editColor(Square *x, QColor);
    //void popUpCombo();
    //void setColor(int n);

    int type() const Q_DECL_OVERRIDE;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    int x;
    int y;
    int colorIndex;

    //QWidget *w;
    //QHBoxLayout *t;
    //QComboBox *combo1;
    //QToolButton *b;
    QVector<QPointF> stuff;



public Q_SLOTS:
    //void setColor2(int);
    //void setColor();
};

#endif // SQUARE_H
