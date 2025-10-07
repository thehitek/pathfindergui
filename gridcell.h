#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>

class GridCell : public QGraphicsRectItem
{
public:
    explicit GridCell(int xPos, int yPos, bool obstacle = false, int sizeInPixels = 30);

    bool isObstacle() const;

    int xPos() const;
    int yPos() const;

private:
    int m_xPos;
    int m_yPos;
    int m_sizeInPixels;

    bool m_obstacleState;
};


#endif // GRIDCELL_H
