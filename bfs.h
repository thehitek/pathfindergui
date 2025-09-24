#ifndef BFS_H
#define BFS_H

#include <QQueue>
#include <QPair>

template<typename T>
using DDArray = QList<QList<T>>; /* Double Dimension Array */

typedef QPair<int, int> IntPair;

class BFS
{
public:
    BFS(DDArray<bool> &cellAvailability, IntPair cellFrom, IntPair cellTo);

    void calculate();
    QList<IntPair> getPath();

private:
    QQueue<IntPair> m_queue;

    DDArray<bool> m_cellAvailability;
    IntPair m_cellFrom, m_cellTo;

    DDArray<int> m_shortestDistTo;
    DDArray<IntPair> m_shortestPathTo;

    qsizetype m_w, m_h;
};

#endif // BFS_H
