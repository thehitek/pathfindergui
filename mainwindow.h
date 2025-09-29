#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>

#include "bfs.h"
#include "gridmodel.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initConnections();
    void readSettings();

    Ui::MainWindow* ui = nullptr;
    GridModel *m_gridModel = nullptr;
};


#endif // MAINWINDOW_H
