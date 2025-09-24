#include "bfs.h"

BFS::BFS(DDArray<bool> &cellAvailability,
         IntPair cellFrom,
         IntPair cellTo)
    : m_cellAvailability(cellAvailability),
    m_cellFrom(cellFrom),
    m_cellTo(cellTo)
{
    m_w = m_cellAvailability.size();
    m_h = m_cellAvailability.first().size();

    QList<int> filler0;
    filler0.fill(-1, m_h);
    m_shortestDistTo.fill(filler0, m_w);
    m_shortestDistTo[cellFrom.first][cellFrom.second] = 0;

    QList<IntPair> filler1;
    filler1.fill(IntPair(-1, -1), m_h);
    m_shortestPathTo.fill(filler1, m_w);
}

void BFS::calculate()
{
    m_queue.clear();
    m_queue.push_back(m_cellFrom);

    if (!m_cellAvailability[m_cellFrom.first][m_cellFrom.second] ||
        !m_cellAvailability[m_cellTo.first][m_cellTo.second])
        return;

    while (!m_queue.empty()) {
        auto [x, y] = m_queue.front();
        m_queue.pop_front();

        // просматриваем всех соседей
        QList<IntPair> directions = {{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
        for (auto [dx, dy] : directions) {
            // считаем координаты соседа
            int nx = x + dx;
            int ny = y + dy;

            // ловим выход за границы
            if (nx < 0 || nx >= m_w || ny < 0 || ny >= m_h)
                continue;

            // и проверяем, что сосед свободен и не был посещен ранее
            if (m_cellAvailability[nx][ny] && m_shortestDistTo[nx][ny] == -1){
                m_shortestDistTo[nx][ny] = m_shortestDistTo[x][y] + 1;
                m_queue.push_back(IntPair(nx, ny));
                m_shortestPathTo[nx][ny] = IntPair(x, y);
            }
        }
    }
}

QList<IntPair> BFS::getPath()
{
    QList<IntPair> path;

    for (int i = 0; i < m_h * m_w; i++) {
        if (m_cellFrom.first == m_cellTo.first && m_cellFrom.second == m_cellTo.second) {
            path.append(m_cellFrom);
            break;
        }

        if (m_cellTo.first == -1 && m_cellTo.second == -1)
            return QList<IntPair>();

        path.append(m_cellTo);
        m_cellTo = m_shortestPathTo[m_cellTo.first][m_cellTo.second];
    }

    return path;
}
