#include <QRandomGenerator>

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

    m_cells.clear();

    QList<CellItem *> filler;
    filler.fill(nullptr, m_rows);
    m_cells.fill(filler, m_columns);
}

void GridModel::createNewBoard()
{
    auto randomizer = QRandomGenerator::global();

    for (int i = 0; i < m_columns; i++){
        for (int j = 0; j < m_rows; j++){
            int randomPercent = randomizer->bounded(0, 100);
            bool isObstacle = randomPercent < m_obstacleSpawnRate;

            if (m_cells[i][j] != nullptr) delete m_cells[i][j];

            m_cells[i][j] = new CellItem(isObstacle, i, j);
        }
    }
}
