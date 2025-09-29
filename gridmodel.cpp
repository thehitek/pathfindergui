#include "gridmodel.h"

GridModel::GridModel(QObject *parent) : QAbstractTableModel(parent)
{
    qRegisterMetaType<CellItem>("CellItem");
}

int GridModel::rowCount(const QModelIndex &parent) const
{
    return m_rows;
}

int GridModel::columnCount(const QModelIndex &parent) const
{
    return m_columns;
}

QVariant GridModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return QVariant::fromValue(m_cells[index.column()][index.row()]);
    }
    return QVariant();
}

int GridModel::cellSize() const
{
    return m_cellSize;
}

void GridModel::setCellSize(int newCellSize)
{
    m_cellSize = newCellSize;
}

int GridModel::obstacleSpawnRate() const
{
    return m_obstacleSpawnRate;
}

void GridModel::setObstacleSpawnRate(int newObstacleSpawnRate)
{
    m_obstacleSpawnRate = newObstacleSpawnRate;
}

void GridModel::setRowsAndColumns(int rows, int columns)
{
    m_rows = rows;
    m_columns = columns;
}
