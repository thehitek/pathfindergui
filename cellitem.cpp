#include "cellitem.h"

CellItem::CellItem(bool isObstacle, int row, int column)
    : m_obstacle(isObstacle), m_row(row), m_column(column)
{

}

bool CellItem::obstacle() const
{
    return m_obstacle;
}
