#include "model.h"
#include "trap.h"
#include "diamond.h"
#include "parallelogram.h"
#include "oval.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QFile>
#include <QString>


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
    currentAction = Action_MoveObject;
}

void model::create(QListWidgetItem *thing)
{
    std::cout<<"Add element to scene"<<std::endl;
    QColor color(QColor(Qt::red));
    qreal x = 700;
    qreal y = 700;
   QGraphicsItem *item;
    if(thing->text() == "square")
    {
         item = new Square(color, x, y);
    }
    else if(thing->text() == "oval")
    {
         item = new Oval(color, x, y);
    }
    else if(thing->text() == "diamond")
    {
         item = new Diamond(color, x, y);
    }
    else
    {
         item = new Trap(color, x, y);
    }
    item->setPos(QPointF(100, 100));
    addItem(item);
}
void model::theSaveList()
{

    listActiveItems = items();
    QFile file("flowchart.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for(int i=0; i<listActiveItems.size(); i++)
    {
        //std::cout<<listActiveItems[i]->type()<<std::endl;


        if(listActiveItems[i]->type() == 0)
            out<<"Shape: "<<"Square\n";
        else if(listActiveItems[i]->type() == 1)
            out<<"Shape: "<<"Oval\n";
        else if(listActiveItems[i]->type() == 2)
            out<<"Shape: "<<"Diamond\n";
        else
            out<<"Shape: "<<"Trapezoid\n";


        out<<"Coordinates: ";
        out<<"( "<<listActiveItems[i]->pos().x()<<", "<<listActiveItems[i]->pos().y()<<")";
        out<<"\n";
    }
    file.close();
}

void model::label()
{
    std::cout<<"Add label to scene"<<std::endl;
    QColor color(QColor(Qt::red));
    qreal x = 700;
    qreal y = 700;
    QGraphicsItem *item = new Square(color, x, y);
    item->setPos(QPointF(100, 100));
    addItem(item);
}

void model::createRect(QColor color, qreal x, qreal y)
{
    std::cout<<"Add rectangle to scene"<<std::endl;

    QGraphicsItem *item = new Square(color, x, y);
    item->setPos(QPointF(100, 100));
    addItem(item);
}

void model::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    std::cout<<"button pressed"<<std::endl;
    if (mouseEvent->button() != Qt::LeftButton) {
        std::cout << "not left key pressed" << std::endl;
        return;
    }
    std::cout << "left key pressed" << std::endl;
    std::cout << "(" << mouseEvent->scenePos().x() << "," << mouseEvent->scenePos().y() << ")" << std::endl;
    if(currentAction == Action_CreateLineStart)
    {
        QTransform trans;
        Shape *it = qgraphicsitem_cast<Shape *>(itemAt(mouseEvent->scenePos(), trans));
        lineBeginItem = it;
        if(it != NULL)
        {
            it->test();
            currentAction = Action_CreateLineEnd;
        }
        else
        {
            std::cout<<"no item here"<<std::endl;
        }
    }
    else if(currentAction == Action_CreateLineEnd)
    {
        QTransform trans;
        Shape *it = qgraphicsitem_cast<Shape *>(itemAt(mouseEvent->scenePos(), trans));
        lineEndItem = it;
        if(it != NULL)
        {
            it->test();
            currentAction = Action_CreateLineEnd;
        }
        else
        {
            std::cout<<"no item here"<<std::endl;
        }
        if(lineBeginItem != NULL && lineEndItem != NULL)
        {
            std::cout<<"Create arrow"<<std::endl;
            Arrow *arrow = new Arrow(lineBeginItem, lineEndItem);
            lineBeginItem->addArrow(arrow);
            lineEndItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
        else
        {
            std::cout<<"cannot create arrow without 2 shapes"<<std::endl;
        }
        currentAction = Action_MoveObject;
    }
    std::cout <<"Action " << currentAction<<std::endl;
    QGraphicsScene::mousePressEvent(mouseEvent);
    return;
}

void model::setAction(DesiredAction action)
{
    std::cout<<"action set to " << action <<std::endl;
    currentAction = action;
}

void model::updateScene()
{
    std::cout<<"update scene"<<std::endl;
}

