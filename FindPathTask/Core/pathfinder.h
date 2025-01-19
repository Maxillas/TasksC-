#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>


class Cell;

class PathFinder : public QObject
{
    Q_OBJECT
public:

    explicit PathFinder(QObject *parent = nullptr);
    void find(const QVector<QVector<Cell*>>& grid, Cell* start, Cell* end);


signals:


private:

    // Функция для проверки, находится ли ячейка в пределах сетки
    bool isValid(int row, int col, const QVector<QVector<Cell*>>& grid);

    // Функция для поиска в глубину (DFS)
    bool BFS(const QVector<QVector<Cell*>>& grid, int startRow, int startCol);

    Cell* m_endCell = nullptr;
    //const QVector<QVector<Cell*>>& m_grid;

};

#endif // PATHFINDER_H
