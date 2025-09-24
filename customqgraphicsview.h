#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QWheelEvent>

class CustomQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomQGraphicsView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // CUSTOMQGRAPHICSVIEW_H
