#include "shape.h"
#include <iostream>

Shape::Shape()
{    
}

void Shape::test()
{
    std::cout<<"test"<<std::endl;
}

void Shape::test2()
{
    std::cout<<"test2"<<std::endl;
}

void Shape::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

void Shape::setDispText(QString text)
{
    dispText = text;
}

void Shape::editColor(Shape *x, QColor c)
{
   std::cout<<"set color 2"<<std::endl;
   x->color = c;
}


void Shape::setColor(int n)
{
    std::cout<<"set color"<<std::endl;
    if (n == 0)
    {
        color = QColor(Qt::blue);
    }
    else if (n == 1)
    {
        color = QColor(Qt::red);
    }
    else if(n == 2)
    {
        color = QColor(Qt::green);
    }
    else if (n == 3)
    {
        color = QColor(Qt::gray);
    }
    else if (n == 4)
    {
        color = QColor(Qt::yellow);
    }

    editColor(this, color);
    update();
}



