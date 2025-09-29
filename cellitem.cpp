#include "cellitem.h"

CellItem::CellItem(bool isObstacle, int row, int column, QObject *parent)
    : m_obstacle(isObstacle), m_row(row), m_column(column), QObject(parent)
{

}

bool CellItem::obstacle() const
{
    return m_obstacle;
}

int CellItem::row() const
{
    return m_row;
}

int CellItem::column() const
{
    return m_column;
}
