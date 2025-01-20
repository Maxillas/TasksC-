#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include <QObject>

#include "pathfinder.h"

//#include "../UI/blocks/field/cell.h"

class Cell;

class FieldController : public QObject
{
    Q_OBJECT
public:
    FieldController(const FieldController&) = delete;
    FieldController& operator=(const FieldController&) = delete;

    static FieldController& getInstance() {
        static FieldController instance;
        return instance;
    }
    void setWidth(const uint16_t& newWidth);
    uint16_t getWidth() const;

    void setHeight(const uint16_t& newHeight);
    uint16_t getHeight() const;

    void initiateGrid(uint16_t height, uint16_t width);
    void addItemInGrid(int row, int col, Cell* cell);
    void setWall(int row, int col, bool isWall);


    void setStartCell(Cell* startCell);
    Cell* getStartCell();


    bool isSearchStarted();
    bool isSearchEnded();

    void findPath();
    void clean();
    void cleanGrid();

    void onCellClicked(Cell* clickedCell);

    void onMouseMove(Cell* selectedCell);

signals:
    void generateField(uint16_t width, uint16_t height);
    void dontFindPath();
    void foundPath(QVector<Cell*> path);


private:
    explicit FieldController(QObject *parent = nullptr);

    uint16_t m_height;
    uint16_t m_width;

    Cell* m_startCell = nullptr;
    Cell* m_endCell = nullptr;

    bool m_isSearchStarted;
    bool m_isSearchEnded;

    QVector<QVector<Cell*>> m_grid;

    PathFinder* m_pathfinder = nullptr;

};

#endif // FIELD_CONTROLLER_H
