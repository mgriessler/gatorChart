#include "square.h"
#include "view.h"
#include <iostream>
#include <QtWidgets>

Square::Square(const QColor &color, int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->dispText = "Square";
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);


}

/*
void Square::popUpCombo()
{

    w = new QWidget;
    w->setWindowTitle("Select Color");
    t = new QHBoxLayout;
    w->setLayout(t);
    combo1 = new QComboBox;
    combo1->addItem("blue");
    combo1->addItem("red");
    combo1->addItem("green");
    combo1->addItem("gray");
    combo1->addItem("yellow");
    t->addWidget(combo1);
    w->show();

    b = new QToolButton;
    b->setText("OK");
    t->addWidget(b);

    //connect(b, SIGNAL(triggered()), this, SLOT(openFile()));
    //connect(b, SIGNAL(clicked()), this, SLOT(setColor()));

}*/

QRectF Square::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}
int Square::type() const
{
    return 0;
}
QPainterPath Square::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = color;

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(14, 14, 79, 39));
    painter->setBrush(b);

    painter->setPen(QPen(Qt::gray, 1));
    painter->drawLine(15, 54, 94, 54);
    painter->drawLine(94, 53, 94, 15);
    painter->setPen(QPen(Qt::black, 0));

    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    painter->drawText(20,40, dispText);
    painter->restore();
}



void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->button() == Qt::RightButton) {
        std::cout << "you right-clicked on Square" << std::endl;

        //popUpCombo();
        //setColor(0);
        return;
    }

    QGraphicsItem::mousePressEvent(event);
    //std::cout <<"Start (" << this->pos().x() << ", " << this->pos().y() << ") ";
    update();
}

void Square::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
