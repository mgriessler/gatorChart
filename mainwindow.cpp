#include "mainwindow.h"
#include "view.h"
#include "square.h"

#include <QtWidgets>
#include <QHBoxLayout>
#include <QTextEdit>

/*********
 * Here the view is initialized
 *
*/
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    Model = new model;

    View *view = new View("Flow view", Model);
    view->view()->setScene(Model);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Gator Chart"));
}


