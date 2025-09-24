#include "gridcell.h"
#include <QPen>

GridCell::GridCell(int xPos, int yPos, bool obstacle, int sizeInPixels)
    :   m_xPos(xPos),
        m_yPos(yPos),
        m_obstacleState(obstacle),
        m_sizeInPixels(sizeInPixels),
        QGraphicsRectItem(nullptr) {

    setRect(QRectF(0, 0, m_sizeInPixels, m_sizeInPixels));
    setPos(QPointF(m_xPos * m_sizeInPixels, m_yPos * m_sizeInPixels));

    setPen(QPen(Qt::black, 1));

    if (m_obstacleState){
        setBrush(QBrush(Qt::red));
    } else {
        setBrush(Qt::NoBrush);
    }
}


bool GridCell::isObstacle() { return m_obstacleState; }
