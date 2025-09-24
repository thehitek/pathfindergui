#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include "bfs.h"


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

private slots:
    void onGenerateButtonClicked();
    void onSceneSelectionChanged();

private:
    void initConnections();

    Ui::MainWindow* ui;
    QGraphicsScene* m_scene = nullptr;

    std::optional<IntPair> m_cellFrom = std::nullopt;
    std::optional<IntPair> m_cellTo = std::nullopt;
};
#endif // MAINWINDOW_H
