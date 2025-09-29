#ifndef CELLITEM_H
#define CELLITEM_H

#include <QObject>
#include <QMetaType>

class CellItem : public QObject
{
    Q_OBJECT
public:
    explicit CellItem(bool isObstacle, int row, int column, QObject *parent = nullptr);

    bool obstacle() const;
    int row() const;
    int column() const;

private:
    bool m_obstacle;
    int m_row;
    int m_column;
};

Q_DECLARE_METATYPE(CellItem)

#endif // CELLITEM_H
