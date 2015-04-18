#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "model.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QGraphicsScene *scene;


private:
    model *Model;
    void setupMatrix();
    void populateScene();

};

#endif // MAINWINDOW_H
