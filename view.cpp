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
#include<QFile>

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

    QToolButton *addSquareButton = new QToolButton;
    addSquareButton->setText(tr("Square"));

    //COLUMN 1
    QGridLayout *col1 = new QGridLayout;
    QLabel *placeHolder1 = new QLabel(tr("This is"));
    QLabel *placeHolder2 = new QLabel(tr("just a"));
    QLabel *placeHolder3 = new QLabel(tr("place"));
    QLabel *placeHolder4 = new QLabel(tr("holder"));
    col1->addWidget(placeHolder1, 1, 0, 1, 1);
    col1->addWidget(placeHolder2, 2, 0, 1, 1);
    col1->addWidget(placeHolder3, 3, 0, 1, 1);
    col1->addWidget(placeHolder4, 4, 0, 1, 1);

    //TOOL BAR
    QLabel *zoomLabel = new QLabel(tr("Zoom"));
    QHBoxLayout *toolBar = new QHBoxLayout;
    toolBar->addWidget(pointerMode);
    toolBar->setAlignment(pointerMode, Qt::AlignRight);
    toolBar->addWidget(selectModeButton);
    toolBar->addWidget(dragModeButton);
    toolBar->addWidget(addConnectorButton);
    toolBar->setAlignment(addConnectorButton, Qt::AlignLeft);
    toolBar->addWidget(zoomLabel);
    toolBar->setAlignment(zoomLabel, Qt::AlignRight);
    toolBar->addWidget(zoomInButton);
    toolBar->addWidget(zoomOutButton);
    toolBar->setAlignment(zoomOutButton, Qt::AlignLeft);
    toolBar->addWidget(addSquareButton);
    toolBar->setAlignment(addSquareButton, Qt::AlignRight);

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
    QHBoxLayout *labelLayout = new QHBoxLayout;
    QToolButton *selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    QToolButton *dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);

  //  labelLayout->addStretch();
  //  labelLayout->addWidget(label2);
  //  labelLayout->addStretch();
  //  labelLayout->addWidget(addSquareButton);

    QGridLayout *topLayout = new QGridLayout;
    //topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addLayout(col1, 1, 0, 1, 1);
    topLayout->addWidget(graphicsView, 1, 1);
    topLayout->addLayout(toolBar, 0, 1, 1, 2);
    setLayout(topLayout);

    //Michelle
    QListWidget *shapesList = new QListWidget();
    QListWidgetItem *square = new QListWidgetItem();
    QListWidgetItem *diamond = new QListWidgetItem();
    QListWidgetItem *trapezoid = new QListWidgetItem();
    QListWidgetItem *oval = new QListWidgetItem();

    square->setText("square");
    diamond->setText("diamond");
    trapezoid->setText("trapezoid");
    oval->setText("oval");

    shapesList->insertItem(0,square);
    shapesList->insertItem(1,diamond);
    shapesList->insertItem(2,trapezoid);
    shapesList->insertItem(3, oval);

    QGridLayout *listLayout = new QGridLayout();
    QLabel *listLabel = new QLabel(tr("Shapes List"));

    //listLayout->addWidget(listLabel,0,1);
    topLayout->addLayout(listLayout,1,3);

    //Dennis
    QGridLayout *myLayout = new QGridLayout;

    label = new QLabel(tr("<b>Properties</b>"));
    label->setAlignment(Qt::AlignBottom);

    colorLabel = new QLabel(tr("Edit Color"));
    colorLabel->setAlignment(Qt::AlignBottom);

    //QToolButton *color = new QToolButton;
    //color->setText(tr("Edit Color"));

    QComboBox *combo = new QComboBox;
    combo->addItem("red");
    combo->addItem("green");
    combo->addItem("blue");




    QToolButton *text = new QToolButton;
    text->setText(tr("Add Label"));
    //Adding widgets to myLayout
    myLayout->addWidget(label,0,1);
     myLayout->addWidget(text, 3, 1);
    myLayout->addWidget(colorLabel, 1, 1);
    myLayout->addWidget(combo,2,1);


    //menubar
    menu_bar = new QMenuBar();
    menu = menu_bar->addMenu("File");
    //File menu Actions
    exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(myClose()));
    menu->addAction(exitAction);

    newAction = new QAction(tr("New"), this);
    connect(newAction, SIGNAL(triggered()), this, SLOT(myClose()));
    menu->addAction(newAction);

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

    topLayout->addWidget(menu_bar,0,0);


    //add to topLayout
    topLayout->addLayout(myLayout,1,3);






    //connect stuff
    //connect(color, SIGNAL(clicked()), this, SLOT(editColor()));
    connect(text, SIGNAL(clicked()), this, SLOT(addLabel()));


    connect(addSquareButton, SIGNAL(clicked()), this, SLOT(addSquare()));

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(selectModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(dragModeButton, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
    connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

    setupMatrix();
}

void View::keyPressEvent(QKeyEvent * event)
{
    std::cout<<"key: "<<event->key()<<std::endl;
}

void View::mousePressEvent(QMouseEvent *event)
{
    std::cout<<"pressed mouse"<<std::endl;
    Model->itemHere(event);
}

void View::addSquare()
{
    Model->create();
    //do nothing for now
}

void View::myClose()
{
    QApplication::exit();
}


void View::addLabel()
{
    Model->label();

}

void View::openFile()
{

    //QFile file1("test.txt");
    //file1.open(QIODevice::ReadOnly);

}

void View::editColor()
{

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

void View::togglePointerMode()
{
    graphicsView->setDragMode(selectModeButton->isChecked()
                              ? QGraphicsView::RubberBandDrag
                              : QGraphicsView::ScrollHandDrag);
    graphicsView->setInteractive(selectModeButton->isChecked());
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
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
    std::cout<<"hola"<<std::endl;
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
}
