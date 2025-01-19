#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
#include <QThread>


class Cell;

class PathFinder : public QObject
{
    Q_OBJECT
public:

    explicit PathFinder(QObject *parent = nullptr);
    ~PathFinder();
    Q_INVOKABLE void find(const QVector<QVector<Cell*>>& grid, Cell* start, Cell* end);

signals:

private slots:
    void _find(const QVector<QVector<Cell*>>& grid, Cell* start, Cell* end);

private:
    // Функция для проверки, находится ли ячейка в пределах сетки
    bool isValid(int row, int col, const QVector<QVector<Cell*>>& grid);

    // Функция для поиска в глубину (DFS)
    bool BFS(const QVector<QVector<Cell*>>& grid, int startRow, int startCol);

    void reconstructPath(Cell* endCell);

    Cell* m_endCell = nullptr;

    QThread m_workerThread;
    //const QVector<QVector<Cell*>>& m_grid;

};

#endif // PATHFINDER_H
