#include "model.h"
#include "trap.h"
#include "diamond.h"
#include <iostream>

/*********************************************************
 * the purpose of the model is to maintain all components that make up the flowchart
 * this includes shapes and lines
 * continuing down this line of thought, the View is where the user interacts with the program
 * when the user manipulates the view, it passes the action onto the controller
 * the controller updates the model
 * then the model tells the view to update
 * and the cycle continues
 * to reiterate: to add a shape to the view, it is not directly added to the view, but it is added to the model and the model changes the view
 * Functions provided by the model (CMD or Commands) - yes I came up with that myself, yes, I'm proud of it
 * Create - add items to the view
 * Manipulate - change items in the view
 * Delete - remove items from the view
*/
model::model()
{
}

void model::create()
{
    std::cout<<"Add element to scene"<<std::endl;
    QColor color(QColor(Qt::red));
    qreal x = 700;
    qreal y = 700;
    items[0] = new Diamond(color, x, y);
    items[0]->setPos(QPointF(100, 100));
    addItem(items[0]);
}

void model::updateScene()
{
    std::cout<<"update scene"<<std::endl;
}
