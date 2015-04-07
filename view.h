#ifndef VIEW_H
#define VIEW_H


#include <QFrame>
#include <QGraphicsView>
#include "model.h"
#include "square.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
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
    void mousePressEvent(QMouseEvent *event);
public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void resetView();
    void setResetButtonEnabled();
    void setupMatrix();
    void togglePointerMode();
    void toggleAntialiasing();
    void rotateLeft();
    void rotateRight();

    void addSquare();

    void editColor();
    void addLabel();


private:
    GraphicsView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *addSquareButton;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *antialiasButton;
    QToolButton *resetButton;
    QToolButton *addConnectorButton;
    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;
};
#endif // VIEW_H
