#include "pathfinder.h"
#include <QThread>
#include <QQueue>
#include "../UI/blocks/field/cell.h"


PathFinder::PathFinder(QObject *parent)
{
    this->moveToThread(&m_workerThread);
    m_workerThread.start();
}

PathFinder::~PathFinder()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void PathFinder::find(const QVector<QVector<Cell *> > &grid, Cell *start, Cell *end)
{
    QMetaObject::invokeMethod(this,
                              "_find",
                              Qt::QueuedConnection,
                              Q_ARG(const QVector<QVector<Cell*>> , grid),
                              Q_ARG(Cell*, start),
                              Q_ARG(Cell*, end));
}

void PathFinder::_find(const QVector<QVector<Cell *> > &grid, Cell *start, Cell *end)
{
    if (!start || !end || start == end) {
        emit FieldController::getInstance().dontFindPath();
        return;
    }

    m_endCell = end;
    bool result = BFS(grid, start->row, start->column);
    if(!result) {
        emit FieldController::getInstance().dontFindPath();
        return;
    }
}

bool PathFinder::isValid(int row, int col, const QVector<QVector<Cell*>>& grid)
{
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size();
}

bool PathFinder::BFS(const QVector<QVector<Cell*>>& grid, int startRow, int startCol)
{
    if (!isValid(startRow, startCol, grid)) {
        return false;
    }

    QQueue<QPair<int, int>> queue;

    queue.enqueue(qMakePair(startRow, startCol));
    grid[startRow][startCol]->visited = true;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!queue.isEmpty()) {
        QPair<int, int> current = queue.dequeue();
        int currentRow = current.first;
        int currentCol = current.second;

        Cell* currentCell = grid[currentRow][currentCol];

        if (currentCell == m_endCell) {
            reconstructPath(currentCell);
            return true;
        }
        // Добавляем все соседние ячейки в очередь
        for (const auto& dir : directions) {
            int newRow = currentRow + dir[0];
            int newCol = currentCol + dir[1];

            if (isValid(newRow, newCol, grid)) {
                Cell* neighborCell = grid[newRow][newCol];

                if (!neighborCell->isWall && !neighborCell->visited) {
                    neighborCell->visited = true;
                    neighborCell->parent = currentCell;
                    queue.enqueue(qMakePair(newRow, newCol));
                }
            }
        }
    }
    return false;
}

void PathFinder::reconstructPath(Cell *endCell)
{
    QVector<Cell*> path;
    Cell* current = endCell;

    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }

    std::reverse(path.begin(), path.end());
    emit FieldController::getInstance().foundPath(path);
}
