#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class GridCell : public QGraphicsRectItem
{

public:
    GridCell(int xPos, int yPos, bool obstacle = false, int sizeInPixels = 30);
    bool isObstacle();

private:
    int m_xPos;
    int m_yPos;
    bool m_obstacleState;
    int m_sizeInPixels;
};

#endif // GRIDCELL_H
