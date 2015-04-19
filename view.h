#ifndef VIEW_H
#define VIEW_H


#include <QFrame>
#include <QGraphicsView>
#include "model.h"
#include "square.h"
#include "mainwindow.h"
#include <QListWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
class QListWidget;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
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
    void zoomOut(int level = 1);

private Q_SLOTS:
    void print();
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void togglePointerMode();
    void setScrollHandDrag();
    void setRubberBandDragAndInteractive();
    void rotateLeft();
    void rotateRight();

    void myClose();
    void editColor();
    void addLabel();
    void openFile();
    void newChart(QGridLayout *topLayout);

private:
    GraphicsView *graphicsView;
    QMenuBar *menu_bar;
    QMenu *menu;
    QMenu *menu2;
    QMenu *menu3;
    //QFile *file;
    QAction *exitAction;
    QAction *newAction;
    QAction *printAction;
    QAction *helpAction;
    QLabel *label;
    QLabel *label2;
    QLabel *colorLabel;
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
