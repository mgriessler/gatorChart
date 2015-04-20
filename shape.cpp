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

