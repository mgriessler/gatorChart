#include "view.h"
#include <string>
#include<fstream>

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <qmath.h>

//Dennis
#include <QLayout>
#include <QtGui>
#include<QtCore>
#include <QBoxLayout>
#include<QLabel>
#include <QMenu>
#include <QApplication>
#include<QTextStream>
#include<QFile>
#include <QTextEdit>


//Michelle
#include <QListWidget>

//matt
#include <iostream>

//Val
#include <QPrinter>
#include <QPrintDialog>


/*
 * This file represents what you see in the application
*/

//handles scrolling
#ifndef QT_NO_WHEELEVENT
void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            view->zoomIn(6);
        else
            view->zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}
#endif

//constructor, sets up the screen
View::View(const QString &name, model *Mod, QWidget *parent) : QFrame(parent)
{
    //DEFINITIONS
    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);
    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);

    //EDITOR
    Model = Mod;
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, true);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView->setSceneRect(0,0,700,700);

    //Text Color Template
    /*To make the text of a label colored, do this: setText(colorTemplate.arg("color", "text"))
     *with the appropriate color and text */
    QString colorTemplate = tr("<font color='%1'>%2</font>");


    //TOOLBAR
    QLabel *pointerMode = new QLabel(colorTemplate.arg("blue", "Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);
    deleteButton = new QToolButton;
    deleteButton->setText(tr("Delete"));
    deleteButton->setCheckable(true);
    deleteButton->setChecked(false);
    addConnectorButton = new QToolButton;
    addConnectorButton->setText(tr("Connector"));
    addConnectorButton->setCheckable(true);
    addConnectorButton->setChecked(false);
    zoomInButton = new QToolButton;
    zoomInButton->setAutoRepeat(true);
    zoomInButton->setAutoRepeatInterval(33);
    zoomInButton->setAutoRepeatDelay(0);
    zoomInButton->setText(tr("+"));
    zoomInButton->setIconSize(iconSize);
    zoomOutButton = new QToolButton;
    zoomOutButton->setAutoRepeat(true);
    zoomOutButton->setAutoRepeatInterval(33);
    zoomOutButton->setAutoRepeatDelay(0);
    zoomOutButton->setText(tr("-"));
    zoomOutButton->setIconSize(iconSize);



    QButtonGroup *pointerModeGroup = new QButtonGroup;
    pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);
    pointerModeGroup->addButton(deleteButton);
    pointerModeGroup->addButton(addConnectorButton);


    //List of shapes to choose from
    shapesList = new QListWidget();
    QListWidgetItem *square = new QListWidgetItem();
    QListWidgetItem *diamond = new QListWidgetItem();
    QListWidgetItem *trapezoid = new QListWidgetItem();
    QListWidgetItem *oval = new QListWidgetItem();
    QListWidgetItem *parallelogram = new QListWidgetItem();

    square->setText("square");
    diamond->setText("diamond");
    trapezoid->setText("trapezoid");
    oval->setText("oval");
    parallelogram->setText("parallelogram");


    shapesList->insertItem(2, square);
    shapesList->insertItem(3, diamond);
    shapesList->insertItem(4, trapezoid);
    shapesList->insertItem(5, oval);
    shapesList->insertItem(6, parallelogram);

    QLabel *shapesListLabel = new QLabel(tr("<b>Insert Shape</b>"));




    //COLUMN 1. This is the Insert Shapes Column
    QGridLayout *col1 = new QGridLayout;
    col1->addWidget(shapesListLabel, 0, 0, 1, 1);
    col1->addWidget(shapesList, 1, 0, 1, 1);

    //TOOL BAR
    QLabel *zoomLabel = new QLabel(tr("Zoom"));
    QHBoxLayout *toolBar = new QHBoxLayout;
    toolBar->addWidget(pointerMode);
    toolBar->setAlignment(pointerMode, Qt::AlignRight);
    toolBar->addWidget(selectModeButton);
    toolBar->addWidget(dragModeButton);
    toolBar->addWidget(deleteButton);
    toolBar->addWidget(addConnectorButton);
    toolBar->setAlignment(addConnectorButton, Qt::AlignLeft);
    toolBar->addWidget(zoomLabel);
    toolBar->setAlignment(zoomLabel, Qt::AlignRight);
    toolBar->addWidget(zoomInButton);
    toolBar->addWidget(zoomOutButton);
    toolBar->setAlignment(zoomOutButton, Qt::AlignLeft);
    //
    toolBar->addWidget(saveButton);

    QToolButton *rotateLeftIcon = new QToolButton;
    rotateLeftIcon->setIcon(QPixmap(":/rotateleft.png"));
    rotateLeftIcon->setIconSize(iconSize);
    QToolButton *rotateRightIcon = new QToolButton;
    rotateRightIcon->setIcon(QPixmap(":/rotateright.png"));
    rotateRightIcon->setIconSize(iconSize);
    rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setMinimum(-360);
    rotateSlider->setMaximum(360);
    rotateSlider->setValue(0);
    rotateSlider->setTickPosition(QSlider::TicksBelow);

    // Rotate slider layout
    QHBoxLayout *rotateSliderLayout = new QHBoxLayout;
    rotateSliderLayout->addWidget(rotateLeftIcon);
    rotateSliderLayout->addWidget(rotateSlider);
    rotateSliderLayout->addWidget(rotateRightIcon);

    resetButton = new QToolButton;
    resetButton->setText(tr("0"));
    resetButton->setEnabled(false);

    // Label layout
    //QHBoxLayout *labelLayout = new QHBoxLayout;
    //TopLayout is the final layout
    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(graphicsView, 1, 1);
    topLayout->addLayout(toolBar, 0, 1, 1, 2);
    topLayout->addLayout(col1, 1, 0, 1, 1);
    setLayout(topLayout);



    //Dennis
    QGridLayout *myLayout = new QGridLayout;

    label = new QLabel(tr("<b>Properties</b>"));
    label->setAlignment(Qt::AlignBottom);
    label->setAlignment(Qt::AlignCenter);

    colorLabel = new QLabel(tr("Edit Color"));
    colorLabel->setAlignment(Qt::AlignBottom);

    //QToolButton *color = new QToolButton;
    //color->setText(tr("Edit Color"));

    combo = new QComboBox;
    combo->addItem("blue");
    combo->addItem("red");
    combo->addItem("green");
    combo->addItem("gray");
    combo->addItem("yellow");





    QToolButton *text = new QToolButton;
    text->setText(tr("Edit"));
    //Adding widgets to myLayout
    myLayout->addWidget(label,0,1);
    myLayout->addWidget(text, 3, 1);
    myLayout->addWidget(colorLabel, 1, 1);
    myLayout->addWidget(combo,2,1);

    in = new QLineEdit;
    myLayout->addWidget(in,4,1);

    QToolButton *text2 = new QToolButton;
    text2->setText("Add Label");
    myLayout->addWidget(text2,5,1);



    //menubar
    menu_bar = new QMenuBar();
    menu = menu_bar->addMenu("File");
    //File menu Actions
    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(myClose()));
    menu->addAction(exitAction);

    newAction = new QAction(tr("New"), this);
    //connect(newAction, SIGNAL(triggered()), this, SLOT(newChart(topLayout)));
    connect(newAction, SIGNAL(triggered()), this, SLOT(resetView()));
    menu->addAction(newAction);

    openAction = new QAction(tr("Open"),this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    menu->addAction(openAction);


    //Print Menu Actions
    menu2 = menu_bar->addMenu("Print");
    printAction = new QAction(tr("Print"), this);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
    menu2->addAction(printAction);

    //Help Menu Actions
    menu3 = menu_bar->addMenu("Help");
    helpAction = new QAction(tr("Tutorial"), this);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(openFile()));
    menu3->addAction(helpAction);

    //Save Menu Actions
    menu4 = menu_bar->addMenu("Save");
    saveAction = new QAction(tr("Save"),this);
    connect(saveAction, SIGNAL(triggered()),this,SLOT(save()));
    menu4->addAction(saveAction);

    topLayout->addWidget(menu_bar, 0, 0, 1, 1);


    //add to topLayout
    topLayout->addLayout(myLayout,1,3);



    //connect stuff
    //connect(color, SIGNAL(clicked()), this, SLOT(editColor()));
    connect(text, SIGNAL(clicked()), this, SLOT(edit()));
    connect(text2, SIGNAL(clicked()), this, SLOT(addLabel()));


    connect(shapesList, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(itemSel(QListWidgetItem*)));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(selectModeButton, SIGNAL(clicked(bool)), this, SLOT(selectMode()));
    connect(dragModeButton, SIGNAL(clicked(bool)), this, SLOT(dragMode()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteMode()));
    connect(addConnectorButton, SIGNAL(clicked(bool)), this, SLOT(addConnector()));
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

    setupMatrix();
}

/*
void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::cout<<"View Press "<< event->button() << std::endl;
    if (event->button() == Qt::LeftButton) {
        setDragMode(QGraphicsView::RubberBandDrag);
        setInteractive(true);
    }
    else if (event->button() == Qt::RightButton) {
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
    }
    QGraphicsView::mousePressEvent(event);
}


void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setDragMode(QGraphicsView::RubberBandDrag);
        setInteractive(true);
    }
    else if (event->button() == Qt::RightButton) {
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
    }
    QGraphicsView::mouseReleaseEvent(event);
}
*/
void View::itemSel(QListWidgetItem *item)
{
    Model->create(item);
    return;
}
void View::save()
{
    Model->theSaveList();
    std::cout<<"You are saving"<<std::endl;
    return;
}
void View::open()
{
    std::cout<<"You are opening a new file"<<std::endl;
    Model->openNewApplication();
    return;
}

void View::keyPressEvent(QKeyEvent * event)
{
    std::cout<<"key: "<<event->key()<<std::endl;
}

void View::myClose()
{
    QApplication::exit();
}


void View::edit()
{
    std::cout<<"View Edit"<<std::endl;
    Model->setColor(combo->currentIndex());
}

void View::addLabel()
{
    std::cout<<in->displayText().toStdString()<<std::endl;
    Model->setDispText(in->displayText());
}

void View::openFile()
{
    QWidget *w = new QWidget;
    w->setWindowTitle("Tutorial");
    //QFile file("C:\\Users\\Dennis\\Desktop\\COP3503\\tutorial.txt");
    QFile file("tutorial.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readAll();
    QTextBrowser *content = new QTextBrowser;
    content->setText(line);
    QHBoxLayout *t = new QHBoxLayout;
    w->setLayout(t);
    t->addWidget(content);
    w->show();
}





QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    zoomSlider->setValue(250);
    rotateSlider->setValue(0);
    setupMatrix();

    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));
    Model->clear();

    resetButton->setEnabled(false);
}

void View::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotateSlider->value());

    graphicsView->setMatrix(matrix);
    setResetButtonEnabled();
}

void View::selectMode()
{
    std::cout<<"Select button"<<std::endl;
    Model->setAction(model::Action_MoveObject);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::deleteMode()
{
    std::cout<<"Delete button"<<std::endl;
    Model->setAction(model::Action_Delete);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setInteractive(true);
}

void View::addConnector()
{
    std::cout<<"Connector Button"<<std::endl;
    Model->setAction(model::Action_CreateLineStart);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setInteractive(true);
}

void View::dragMode()
{
    std::cout<<"Drag button"<<std::endl;
    Model->setAction(model::Action_Drag);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(true);
}

void View::zoomIn(int level)
{
    zoomSlider->setValue(zoomSlider->value() + level);
}

void View::zoomOut(int level)
{
    zoomSlider->setValue(zoomSlider->value() - level);
}

void View::rotateLeft()
{
    rotateSlider->setValue(rotateSlider->value() - 10);
}

void View::rotateRight()
{
    rotateSlider->setValue(rotateSlider->value() + 10);
}

void View::print()
{
    std::cout<<"printing"<<std::endl;
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
}
