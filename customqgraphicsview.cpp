#include "customqgraphicsview.h"


CustomQGraphicsView::CustomQGraphicsView(QWidget *parent)
    : QGraphicsView(parent) {}


void CustomQGraphicsView::wheelEvent(QWheelEvent *event) {
    const QPoint angleDelta = event->angleDelta();

    // расчет масштаба
    const double scaleFactor = 1.05;

    if (angleDelta.y() > 0) {
        scale(
            scaleFactor,
            scaleFactor
        );
    } else if (angleDelta.y() < 0) {
        scale(
            1.0 / scaleFactor,
            1.0 / scaleFactor
        );
    }

    event->accept();
}
