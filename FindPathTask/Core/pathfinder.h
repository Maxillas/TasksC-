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

private slots:
    void _find(const QVector<QVector<Cell*>>& grid, Cell* start, Cell* end);

private:
    bool isValid(int row, int col, const QVector<QVector<Cell*>>& grid);
    bool BFS(const QVector<QVector<Cell*>>& grid, int startRow, int startCol);
    void reconstructPath(Cell* endCell);

    Cell* m_endCell = nullptr;
    QThread m_workerThread;
};

#endif // PATHFINDER_H
