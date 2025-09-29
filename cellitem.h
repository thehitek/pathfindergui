#ifndef CELLITEM_H
#define CELLITEM_H
#include <QMetaType>

class CellItem
{
public:
    CellItem(bool isObstacle, int row, int column);

    bool obstacle() const;

private:
    bool m_obstacle;
    int m_row;
    int m_column;
};

Q_DECLARE_METATYPE(CellItem)

#endif // CELLITEM_H
