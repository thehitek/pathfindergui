#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "cellitem.h"

class GridModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    GridModel(QObject* parent = nullptr);

    // Реализация интерфейса модели данных таблицы
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int cellSize() const;
    void setCellSize(int newCellSize);

    int obstacleSpawnRate() const;
    void setObstacleSpawnRate(int newObstacleSpawnRate);
    void setRowsAndColumns(int rows, int columns);

private:
    QList<QList<CellItem>> m_cells;

    int m_rows;
    int m_columns;
    int m_cellSize;
    int m_obstacleSpawnRate;
};

#endif // GRIDMODEL_H
