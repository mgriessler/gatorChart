#ifndef VIEW_H
#define VIEW_H


#include <QFrame>
#include <QGraphicsView>
#include "model.h"
#include "square.h"
#include "mainwindow.h"
#include <QListWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
class QListWidget;
QT_END_NAMESPACE

class View;
class model;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
    //void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

#endif

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, model *Mod, QWidget *parent = 0);

    QGraphicsView *view() const;
    model *Model;



    void keyPressEvent(QKeyEvent *event);

public Q_SLOTS:
    void zoomIn(int level = 1);
    void itemSel(QListWidgetItem *item);
    void save();
    void zoomOut(int level = 1);
    void open();

private Q_SLOTS:
    void print();
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void dragMode();
    void selectMode();
    void rotateLeft();
    void rotateRight();

    void myClose();
    void edit();
    void openFile();
    void addConnector();


private:
    GraphicsView *graphicsView;
    QMenuBar *menu_bar;
    QMenu *menu;
    QMenu *menu2;
    QMenu *menu3;
    QMenu *menu4;
    QAction *exitAction;
    QAction *newAction;
    QAction *printAction;
    QAction *helpAction;
    QAction *saveAction;
    QAction *openAction;
    QLabel *label;
    QLabel *label2;
    QLabel *colorLabel;
     QComboBox *combo;


    QToolButton *saveButton;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *antialiasButton;
    QToolButton *resetButton;
    QToolButton *addConnectorButton;
    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;
    QListWidget *shapesList;
};
#endif // VIEW_H
