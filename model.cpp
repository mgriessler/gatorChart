#include "model.h"
#include "trap.h"
#include "diamond.h"
#include "parallelogram.h"
#include "oval.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>

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
    act = Action_MoveObject;
}

void model::create(QListWidgetItem *thing)
{
    std::cout<<"Add element to scene"<<std::endl;
    QColor color(QColor(Qt::red));
    qreal x = 700;
    qreal y = 700;
   QGraphicsItem *item;\
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

void model::itemHere(QMouseEvent *event)
{
    QTransform trans;
    if (QGraphicsItem *item = itemAt(QPointF(100,100), trans)) {
            std::cout << "You clicked on item" << item << std::endl;
    } else {
            std::cout << "You didn't click on an item." << std::endl;
    }
}

void model::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        std::cout << "not left key pressed" << std::endl;
        return;
    }
    else
    {
        std::cout << "left key pressed" << std::endl;
    }
    std::cout << "(" << mouseEvent->scenePos().x() << "," << mouseEvent->scenePos().y() << ")" << std::endl;
    /*
    DiagramItem *item;
    switch (myMode) {
        case InsertItem:
            item = new DiagramItem(myItemType, myItemMenu);
            item->setBrush(myItemColor);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
//! [6] //! [7]
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
//! [7] //! [8]
        case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                    this, SLOT(editorLostFocus(DiagramTextItem*)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);
//! [8] //! [9]
    default:
        ;
    }*/
    QGraphicsScene::mousePressEvent(mouseEvent);
    return;
}


void model::updateScene()
{
    std::cout<<"update scene"<<std::endl;
}
