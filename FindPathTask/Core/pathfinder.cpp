#include "pathfinder.h"
#include <QThread>
#include <QQueue>
#include "../UI/blocks/field/cell.h"


PathFinder::PathFinder(QObject *parent)
{

}

void PathFinder::find(const QVector<QVector<Cell *> > &grid, Cell *start, Cell *end)
{
    m_endCell = end;
    BFS(grid, start->row, start->column);
}

bool PathFinder::isValid(int row, int col, const QVector<QVector<Cell*>>& grid)
{
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size();
}

bool PathFinder::BFS(const QVector<QVector<Cell*>>& grid, int startRow, int startCol)
{
    // Проверка, что начальная ячейка находится в пределах сетки
    if (!isValid(startRow, startCol, grid)) {
        return false;
    }

    // Очередь для BFS
    QQueue<QPair<int, int>> queue;

    // Начальная ячейка
    queue.enqueue(qMakePair(startRow, startCol));
    grid[startRow][startCol]->visited = true;

    // Направления для перемещения (вверх, вниз, влево, вправо)
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Пока очередь не пуста
    while (!queue.isEmpty()) {
        // Извлекаем текущую ячейку из очереди
        QPair<int, int> current = queue.dequeue();
        int currentRow = current.first;
        int currentCol = current.second;

        Cell* currentCell = grid[currentRow][currentCol];

        // Если текущая ячейка - это целевая ячейка
        if (currentCell == m_endCell) {
            qDebug() << "FIND!";
            QVector<Cell*> path;
            Cell* current = currentCell;

            while (current != nullptr) {
                current->setCellText("P");
                path.push_back(current);
                current = current->parent;
            }

            // Разворачиваем путь, чтобы получить его от начала до конца
            std::reverse(path.begin(), path.end());

            // Визуализация пути
            for (Cell* cell : path) {
                cell->setCellText("P"); // Помечаем ячейки пути
                qDebug() << "Path cell: " << cell->row << ", " << cell->column;
            }


            return true; // Завершаем поиск
        }

        // Помечаем ячейку как посещенную и выводим информацию
        //currentCell->setCellText("V");
        qDebug() << "visited = " << currentRow << ", " << currentCol;

        // Добавляем все соседние ячейки в очередь
        for (const auto& dir : directions) {
            int newRow = currentRow + dir[0];
            int newCol = currentCol + dir[1];

            // Проверяем, что соседняя ячейка находится в пределах сетки
            if (isValid(newRow, newCol, grid)) {
                Cell* neighborCell = grid[newRow][newCol];

                // Если соседняя ячейка не стена и не посещена
                if (!neighborCell->isWall && !neighborCell->visited) {
                    neighborCell->visited = true;
                    neighborCell->parent = currentCell; // Сохраняем родителя для восстановления пути
                    queue.enqueue(qMakePair(newRow, newCol));
                }
            }
        }

    }
   // qDebug() << "Path not found!";
    return false;
}
